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
 *  @file TriclinicPrimitive.h
 *  @brief Triclinic primitive Bravais lattices.
 *
 *  @author Kristofer Björnson
 */

#ifndef COM_DAFER45_TBTK_TRICLINIC_PRIMITIVE
#define COM_DAFER45_TBTK_TRICLINIC_PRIMITIVE

#include "BravaisLattice.h"

namespace TBTK{
namespace Lattices{

/** Triclinic primitive Bravais lattice.
 *
 *  Dimensions:		3
 *  side1Length:	arbitrary
 *  side2Length:	arbitrary
 *  side3Length:	arbitrary
 *  angle12:		arbitrary
 *  angle13:		arbitrary
 *  angle23:		arbitrary */
class TriclinicPrimitive : public BravaisLattice{
public:
	/** Constructor. */
	TriclinicPrimitive(
		double side1Length,
		double side2Length,
		double side3Length,
		double angle12,
		double angle13,
		double angle23
	);

	/** Destructor. */
	~TriclinicPrimitive();
};

};	//End of namespace Lattices
};	//End of namespace TBTK

#endif