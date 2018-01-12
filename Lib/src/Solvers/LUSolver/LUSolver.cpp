/* Copyright 2017 Kristofer Björnson
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/** @file LUSolver.cpp
 *
 *  @author Kristofer Björnson
 */

#include "LUSolver/LUSolver.h"

#include "slu_zdefs.h"

using namespace std;

namespace TBTK{

LUSolver::LUSolver() : Communicator(true){
	L = nullptr;
	U = nullptr;
	rowPermutations = nullptr;
	columnPermutations = nullptr;
	statistics = nullptr;
}

LUSolver::~LUSolver(){
	if(L != nullptr)
		Destroy_SuperNode_Matrix(L);
	if(U != nullptr)
		Destroy_CompCol_Matrix(U);
	if(rowPermutations != nullptr)
		delete [] rowPermutations;
	if(columnPermutations != nullptr)
		delete [] columnPermutations;
	if(statistics != nullptr)
		StatFree(statistics);
}

void LUSolver::setMatrix(const SparseMatrix<complex<double>> &sparseMatrix){
	//Ensure the matrix is on CSC format since this is the format used by
	//SuperLU.
	SparseMatrix<complex<double>> cscMatrix = sparseMatrix;
	cscMatrix.setStorageFormat(
		SparseMatrix<complex<double>>::StorageFormat::CSC
	);

	//Extract sparse matrix information
	unsigned int numRows = cscMatrix.getNumRows();
	unsigned int numColumns = cscMatrix.getNumColumns();
	unsigned int numMatrixElements = cscMatrix.getCSCNumMatrixElements();
	const unsigned int *cscColumnPointers = cscMatrix.getCSCColumnPointers();
	const unsigned int *cscRows = cscMatrix.getCSCRows();
	const complex<double> *cscValues = cscMatrix.getCSCValues();

	//Ensure the matrix has at least on matrix element.
	TBTKAssert(
		numMatrixElements > 0,
		"LUSolver::setMatrix()",
		"Invalid matrix. The matrix has no non-zero matrix elements.",
		""
	);

	//Prepare Input for SuperLU matrix constructor.
	int *sluColumnPointers = new int[numColumns+1];
	for(unsigned int n = 0; n < numColumns+1; n++)
		sluColumnPointers[n] = cscColumnPointers[n];

	int *sluRows = new int[numMatrixElements];
	doublecomplex *sluValues = new doublecomplex[numMatrixElements];
	for(unsigned int n = 0; n < numMatrixElements; n++){
		sluRows[n] = cscRows[n];
		sluValues[n].r = real(cscValues[n]);
		sluValues[n].i = imag(cscValues[n]);
	}

	//Create matrix.
	SuperMatrix sluMatrix;
	zCreate_CompCol_Matrix(
		&sluMatrix,
		numRows,
		numColumns,
		numMatrixElements,
		sluValues,
		(int*)sluRows,
		(int*)sluColumnPointers,
		SLU_NC,
		SLU_Z,
		SLU_GE
	);

	//Allocate permutation matrices.
	if(rowPermutations != nullptr)
		delete [] rowPermutations;
	if(columnPermutations != nullptr)
		delete [] columnPermutations;
	rowPermutations = new int[numRows];
	columnPermutations = new int[numColumns];

	//Initialize SuperLU options.
	superlu_options_t sluOptions;
	set_default_options(&sluOptions);
	sluOptions.ColPerm = COLAMD;

	//Initialize SuperLU statistics.
	statistics = new SuperLUStat_t();
	StatInit(statistics);

	//Create upper and lower triangular matrices
	if(L != nullptr)
		Destroy_SuperNode_Matrix(L);
	if(U != nullptr)
		Destroy_SuperNode_Matrix(U);
	L = new SuperMatrix();
	U = new SuperMatrix();

	performLUFactorization(sluMatrix, sluOptions);

	//Clean up
	Destroy_CompCol_Matrix(&sluMatrix);
}

void LUSolver::performLUFactorization(
	SuperMatrix &matrix,
	superlu_options_t &options
){
	//LU factorization performed in accordance with the procedure used in
	//zgssv.c in SuperLU 5.2.1. See this file for further details.
	if(options.ColPerm != MY_PERMC && options.Fact == DOFACT)
		get_perm_c(options.ColPerm, &matrix, columnPermutations);

	int *etree = new int[matrix.ncol];

	//Create new matrix resulting from post multiplication by the column
	//permutation matrix, i.e. matrix*columnPermutations.
	SuperMatrix matrixCP;
	sp_preorder(
		&options,
		&matrix,
		columnPermutations,
		etree,
		&matrixCP
	);

	//Query optimization parameters.
	int panelSize = sp_ienv(1);
	int relax = sp_ienv(2);

	//Perform LU factorization.
	int lwork = 0;
	GlobalLU_t glu;
	int info;
	zgstrf(
		&options,
		&matrixCP,
		relax,
		panelSize,
		etree,
		nullptr,
		lwork,
		columnPermutations,
		rowPermutations,
		L,
		U,
		&glu,
		statistics,
		&info
	);

	//Error checking
	if(info != 0){
		if(info < 0){
			TBTKExit(
				"LUSolver::performLUFactorization()",
				"zgstrf() returned with info = " << info << ".",
				"Contact the developer, argument " << -info
				<< " to zgstrf has an invalid value."
			);
		}
		else{
			if(info <= matrixCP.ncol){
				TBTKExit(
					"LUSolver::performLUFactorization()",
					"LU factorization is exactly singular."
					<< " Element U(" << info << ", "
					<< info << ") is zero.",
					"Try adding a small perturbation to the matrix."
				);
			}
			else{
				TBTKExit(
					"LUSolver::performLUFactorization()",
					"Memory allocation error.",
					""
				);
			}
		}
	}

	SUPERLU_FREE(etree);

	Destroy_CompCol_Permuted(&matrixCP);
}

Matrix<complex<double>> LUSolver::solve(
	const Matrix<complex<double>> &b
){
	unsigned int numRows = b.getNumRows();
	unsigned int numColumns = b.getNumCols();
/*	TBTKAssert(
		b.getNumCols() == 1,
		"LUSolver::solve()",
		"Only single column right hand sides supported yet.",
		""
	);*/

	TBTKAssert(
		L != nullptr,
		"LUSolver::solve()",
		"Left hand side matrix not yet set.",
		"Use LUSolver::setMatrix() to set a matrix to use on the left"
		<< " hand side."
	);

	TBTKAssert(
		(int)numRows == U->nrow,
		"LUSolver::solve()",
		"Incompatible dimensions. 'b' must have the same number of"
		<< " rows as the matrix on the right hand side, but 'b' has '"
		<< b.getNumRows() << "' rows, while the right hand side matrix"
		<< " has '" << U->nrow << "' rows.",
		""
	);

	doublecomplex *sluBValues = new doublecomplex[numRows*numColumns];
	for(unsigned int row = 0; row < numRows; row++){
		for(unsigned int col = 0; col < numColumns; col++){
			sluBValues[col*numRows + row].r = real(b.at(row, col));
			sluBValues[col*numRows + row].i = imag(b.at(row, col));
		}
	}

	SuperMatrix sluB;
	zCreate_Dense_Matrix(
		&sluB,
		numRows,
		numColumns,
		sluBValues,
		numRows,	//Leading dimension
		SLU_DN,
		SLU_Z,
		SLU_GE
	);

	//Solve
	int info;
	zgstrs(
		NOTRANS,
		L,
		U,
		columnPermutations,
		rowPermutations,
		&sluB,
		statistics,
		&info
	);

	//Error checking
	if(info != 0){
		if(info < 0){
			TBTKExit(
				"LUSolver::solve()",
				"Argument",
				"This should never happen, contact the developer."
			);
		}
		else{
			TBTKExit(
				"LUSolver::solve()",
				"zgstrs() returned with info = " << info << ".",
				"Contact the developer, argument " << -info
				<< " to zgstrf has an invalid value."
			);
		}
	}

	//Copy results to return value
	Matrix<complex<double>> result(numRows, numColumns);
	for(unsigned int row = 0; row < numRows; row++){
		for(unsigned int col = 0; col < numColumns; col++){
			result.at(row, col) = complex<double>(
				sluBValues[col*numRows + row].r,
				sluBValues[col*numRows + row].i
			);
		}
	}

	Destroy_Dense_Matrix(&sluB);

	return result;
}

};	//End of namespace TBTK