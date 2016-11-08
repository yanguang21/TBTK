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

/** @package TBTKcalc
 *  @file ReciprocalLattice.h
 *  @brief A ReciprocalLattice allows for the creation of a momentum space Model from a UnitCells.
 *
 *  @author Kristofer Björnson
 */

#ifndef COM_DAFER45_TBTK_RECIPROCAL_LATTICE
#define COM_DAFER45_TBTK_RECIPROCAL_LATTICE

#include "UnitCell.h"
#include "Model.h"

#include <vector>
#include <initializer_list>

namespace TBTK{

class ReciprocalLattice{
public:
	/** Constructor. */
	ReciprocalLattice(UnitCell *unitCell);

	/** Destructor. */
	~ReciprocalLattice();

	/** Genearates a Model for give momentum. */
	Model* generateModel(std::initializer_list<double> momentum) const;

	/** Get reciprocal lattice vectors. */
	const std::vector<std::vector<double>>& getReciprocalLatticeVectors() const;
private:
	/** Unit cell used to create reciprocal Model. */
	UnitCell *unitCell;

	/** Reciprocal lattice vectors. */
	std::vector<std::vector<double>> reciprocalLatticeVectors;
};

inline const std::vector<std::vector<double>>& ReciprocalLattice::getReciprocalLatticeVectors() const{
	return reciprocalLatticeVectors;
}

};	//End of namespace TBTK

#endif
