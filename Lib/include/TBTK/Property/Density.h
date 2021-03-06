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
 *  @file Density.h
 *  @brief Property container for density.
 *
 *  @author Kristofer Björnson
 */

#ifndef COM_DAFER45_TBTK_DENSITY
#define COM_DAFER45_TBTK_DENSITY

#include "TBTK/Property/AbstractProperty.h"
#include "TBTK/IndexTree.h"

namespace TBTK{
namespace Property{

/** @brief Property container for density. */
class Density : public AbstractProperty<double>{
public:
	/** Constructs a Density on the Ranges format. [See AbstractProperty
	 *  for detailed information about the Ranges format.]
	 *
	 *  @param dimensions Number of dimensions for the grid.
	 *  @param ranges The upper limits (exclusive) for the corresponding
	 *  dimensions. */
	Density(int dimensions, const int *ranges);

	/** Constructs a Density on the Ranges format and initializes it with
	 *  data. [See AbstractProperty for detailed information about the
	 *  Ranges format and the raw data format.]
	 *
	 *  @param dimensions Number of dimensions for the grid.
	 *  @param ranges The upper limits (exclusive) for the corresponding
	 *  dimensions.
	 *
	 *  @param data Raw data to initialize the Density with. */
	Density(int dimensions, const int *ranges, const double *data);

	/** Constructs a Density on the Custom format. [See AbstractProperty
	 *  for detailed information about the Custom format.]
	 *
	 *  @param indexTree IndexTree containing the @link Index Indices
	 *  @endlink for which the Density should be contained. */
	Density(const IndexTree &indexTree);

	/** Constructs a Density on the Custom format. [See AbstractProperty
	 *  for detailed information about the Custom format and the raw data
	 *  format.]
	 *
	 *  @param indexTree IndexTree containing the @link Index Indices
	 *  @endlink for which the Density should be contained.
	 *
	 *  @param data Raw data to initialize the Density with. */
	Density(const IndexTree &indexTree, const double *data);

	/** Copy constructor. */
//	Density(const Density &density);

	/** Move constructor. */
//	Density(Density &&density);

	/** Constructor. Constructs the Density from a serializeation string.
	 *
	 *  @param serialization Serialization string from which to construct
	 *  the Density.
	 *
	 *  @param mode Mode with which the string has been serialized. */
	Density(const std::string &serialization, Mode mode);

	/** Destructor. */
//	~Density();

	/** Assignment operator. */
//	Density& operator=(const Density &rhs);

	/** Move assignment operator. */
//	Density& operator=(Density &&rhs);

	/** Get the minimum value for the Density.
	 *
	 *  @return The minimum value.*/
	double getMin() const;

	/** Get maximum value for the Density.
	 *
	 *  @return The maximum value. */
	double getMax() const;

	/** Overrides AbstractProperty::serialize(). */
	virtual std::string serialize(Mode mode) const;
private:
};

};	//End namespace Property
};	//End namespace TBTK

#endif
