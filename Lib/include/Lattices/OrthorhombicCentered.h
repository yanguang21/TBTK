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
 *  @file OrthorhombicCentered.h
 *  @brief Orthorhombic centered Bravais lattices.
 *
 *  @author Kristofer Björnson
 */

#ifndef COM_DAFER45_TBTK_ORTHORHOMBIC_CENTERED
#define COM_DAFER45_TBTK_ORTHORHOMBIC_CENTERED

#include "OrthorhombicPrimitive.h"

namespace TBTK{
namespace Lattices{

/** Orthorhombic centered Bravais lattice.
 *
 *  Dimensions:		2
 *  side1Length:	arbitrary
 *  side2Length:	arbitrary
 *  angle12:		pi/2 */
class OrthorhombicCentered : public OrthorhombicPrimitive{
public:
	/** Constructor. */
	OrthorhombicCentered(
		double side1Length,
		double side2Length
	);

	/** Destructor. */
	~OrthorhombicCentered();
};

};	//End of namespace Lattices
};	//End of namespace TBTK

#endif