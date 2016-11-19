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

/** @file TriclinicPrimitive.cpp
 *
 *  @author Kristofer Björnson
 */

#include "TriclinicPrimitive.h"
#include "Vector3d.h"
#include "TBTKMacros.h"

#include <cmath>

using namespace std;

namespace TBTK{
namespace Lattices{

TriclinicPrimitive::TriclinicPrimitive(
	double side1Length,
	double side2Length,
	double side3Length,
	double angle12,
	double angle13,
	double angle23
){
	vector<vector<double>> latticeVectors;

	latticeVectors.push_back(vector<double>());
	latticeVectors.at(0).push_back(side1Length);
	latticeVectors.at(0).push_back(0.);
	latticeVectors.at(0).push_back(0.);

	latticeVectors.push_back(vector<double>());
	latticeVectors.at(1).push_back(side2Length*cos(angle12));
	latticeVectors.at(1).push_back(side2Length*sin(angle12));
	latticeVectors.at(1).push_back(0.);

	Vector3d comp1 = Vector3d(latticeVectors.at(0)).unit()*cos(angle13);
	Vector3d comp2 = Vector3d(latticeVectors.at(1)).unit()*cos(angle23);
	TBTKAssert(
		(comp1 + comp2).norm() < 1,
		"TriclinicPrimitive::TriclinicPrimitive()",
		"Incompatible lattice angles. It is impossible to simultaneously satisfy the given angles (angle12=" << angle12 << ", angle13=" << angle13 << ", angle23=" << angle23 << ").",
		""
	);
	Vector3d comp3 = Vector3d(latticeVectors.at(0)).unit()*Vector3d(latticeVectors.at(1)).unit()*sqrt(1 - pow((comp1+comp2).norm(), 2));

	latticeVectors.push_back((comp1+comp2+comp3).getStdVector());

	setLatticeVectors(latticeVectors);
}

TriclinicPrimitive::~TriclinicPrimitive(){
}

};	//End of namespace Lattices
};	//End of namespace TBTK
