/* Copyright 2016 Kristofer Björnson
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

/** @package TBTKtemp
 *  @file main.cpp
 *  @brief Partial bilayer using diagonalization
 *
 *  Basic example of diagonalization of a 2D tight-binding model with t = 1 and
 *  mu = -1. Bilayer lattice with edges. First layers size is 20x20 sites, while
 *  the second layer is 20x10.
 *
 *  @author Kristofer Björnson
 */

#include "TBTK/FileWriter.h"
#include "TBTK/Model.h"
#include "TBTK/Property/DOS.h"
#include "TBTK/Property/EigenValues.h"
#include "TBTK/PropertyExtractor/Diagonalizer.h"
#include "TBTK/Solver/Diagonalizer.h"

#include <complex>
#include <iostream>

using namespace std;
using namespace TBTK;

const complex<double> i(0, 1);

int main(int argc, char **argv){
	//Lattice size
	const int SIZE_X = 20;
	const int SIZE_Y_LAYER_BOTTOM = 20;
	const int SIZE_Y_LAYER_TOP = 10;

	//Parameters
	complex<double> mu = -1.0;
	complex<double> t = 1.0;

	//Create model and set up hopping parameters
	Model model;
	//First layer
	for(int x = 0; x < SIZE_X; x++){
		for(int y = 0; y < SIZE_Y_LAYER_BOTTOM; y++){
			for(int s = 0; s < 2; s++){
				//Add hopping amplitudes corresponding to chemical potential
				model << HoppingAmplitude(
					-mu,
					{0, x, y, s},
					{0, x, y, s}
				);

				//Add hopping parameters corresponding to t
				if(x+1 < SIZE_X){
					model << HoppingAmplitude(
						-t,
						{0, (x+1)%SIZE_X, y, s},
						{0, x, y, s}
					) + HC;
				}
				if(y+1 < SIZE_Y_LAYER_BOTTOM){
					model << HoppingAmplitude(
						-t,
						{0, x, (y+1)%SIZE_Y_LAYER_BOTTOM, s},
						{0, x, y, s}
					) + HC;
				}
			}
		}
	}
	//Second layer
	for(int x = 0; x < SIZE_X; x++){
		for(int y = 0; y < SIZE_Y_LAYER_TOP; y++){
			for(int s = 0; s < 2; s++){
				//Add hopping amplitudes corresponding to chemical potential
				model << HoppingAmplitude(
					-mu,
					{1, x, y, s},
					{1, x, y, s}
				);

				//Add hopping amplitudes between layer 0 and 1
				model << HoppingAmplitude(
					-t,
					{1, x, y, s},
					{0, x, y, s}
				) + HC;

				//Add hopping amplitudes corresponding to t
				if(x+1 < SIZE_X){
					model << HoppingAmplitude(
						-t,
						{1, (x+1)%SIZE_X, y, s},
						{1, x, y, s}
					) + HC;
				}
				if(y+1 < SIZE_Y_LAYER_TOP){
					model << HoppingAmplitude(
						-t,
						{1, x, (y+1)%SIZE_Y_LAYER_TOP, s},
						{1, x, y, s}
					) + HC;
				}
			}
		}
	}

	//Construct model
	model.construct();

	//Setup and run Solver::Diagonalizer
	Solver::Diagonalizer dSolver;
	dSolver.setModel(model);
	dSolver.run();

	//Set filename and remove any file already in the folder
	FileWriter::setFileName("TBTKResults.h5");
	FileWriter::clear();

	//Create PropertyExtractor
	PropertyExtractor::Diagonalizer pe(dSolver);

	//Setup energy window
	const double LOWER_BOUND = -5.;
	const double UPPER_BOUND = 7.;
	const int RESOLUTION = 1000;
	pe.setEnergyWindow(LOWER_BOUND, UPPER_BOUND, RESOLUTION);

	//Extract eigenvalues and write these to file
	Property::EigenValues ev = pe.getEigenValues();
	FileWriter::writeEigenValues(ev);

	//Extract DOS and write to file
	Property::DOS dos = pe.calculateDOS();
	FileWriter::writeDOS(dos);

	return 0;
}
