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
 *  @file SpinPolarizedLDOS.h
 *  @brief Property container for spin-polarized local density of states
 *    (spin-polarized LDOS).
 *
 *  @author Kristofer Björnson
 */

#ifndef COM_DAFER45_TBTK_SPIN_POLARIZED_LDOS
#define COM_DAFER45_TBTK_SPIN_POLARIZED_LDOS

#include "TBTK/Property/AbstractProperty.h"
#include "TBTK/SpinMatrix.h"

#include <complex>

namespace TBTK{
namespace Property{

/** @brief Property container for spin-polarized local density of states
 *    (spin-polarized LDOS). */
class SpinPolarizedLDOS : public AbstractProperty<SpinMatrix>{
public:
	/** Constructs a SpinPolarizedDOS on the Ranges format. [See
	 *  AbstractProperty for detailed information about the Ranges format.]
	 *
	 *  @param dimensions Number of dimensions for the grid.
	 *  @param ranges The upper limits (exclusive) for the corresponding
	 *  dimensions.
	 *
	 *  @param lowerBound Lower bound for the energy.
	 *  @param upperBound Upper bound for the energy.
	 *  @param resolution Number of points to use for the energy. */
	SpinPolarizedLDOS(
		int dimensions,
		const int *ranges,
		double lowerBound,
		double upperBound,
		int resolution
	);

	/** Constructs a SpinPolarizedDOS on the Ranges format and initializes
	 *  it with data. [See AbstractProperty for detailed information about
	 *  the Ranges format and the raw data format.]
	 *
	 *  @param dimensions Number of dimensions for the grid.
	 *  @param ranges The upper limits (exclusive) for the corresponding
	 *  dimensions.
	 *
	 *  @param lowerBound Lower bound for the energy.
	 *  @param upperBound Upper bound for the energy.
	 *  @param resolution Number of points to use for the energy.
	 *  @param data Raw data to initialize the SpinPolarizedLDOS with. */
	SpinPolarizedLDOS(
		int dimensions,
		const int *ranges,
		double lowerBound,
		double upperBound,
		int resolution,
		const SpinMatrix *data
	);

	/** Constructs a SpinPolarizedDOS on the Custom format. [See
	 *  AbstractProperty for detailed information about the Custom format.]
	 *
	 *  @param indexTree IndexTree containing the @link Index Indices
	 *  @endlink for which the SpinPolarizedLDOS is contained.
	 *
	 *  @param lowerBound Lower bound for the energy.
	 *  @param upperBound Upper bound for the energy.
	 *  @param resolution Number of points to use for the energy. */
	SpinPolarizedLDOS(
		const IndexTree &indexTree,
		double lowerBound,
		double upperBound,
		int resolution
	);

	/** Constructs a SpinPolarizedDOS on the Custom format and initialize
	 *  it with data. [See AbstractProperty for detailed information about
	 *  the Custom format and the raw data format.]
	 *
	 *  @param indexTree IndexTree containing the @link Index Indices
	 *  @endlink for which the SpinPolarizedLDOS is contained.
	 *
	 *  @param lowerBound Lower bound for the energy.
	 *  @param upperBound Upper bound for the energy.
	 *  @param resolution Number of points to use for the energy.
	 *  @param data Raw data to initialize the SpinPolarizedLDOS with. */
	SpinPolarizedLDOS(
		const IndexTree &indexTree,
		double lowerBound,
		double upperBound,
		int resolution,
		const SpinMatrix *data
	);

	/** Copy constructor. */
//	SpinPolarizedLDOS(const SpinPolarizedLDOS &spinPolarizedLDOS);

	/** Move constructor. */
//	SpinPolarizedLDOS(SpinPolarizedLDOS &&spinPolarizedLDOS);

	/** Constructor. Construct the SpinPolarizedLDOS from a serialization
	 *  string.
	 *
	 *  @param serialization Serialization string from which to construct
	 *  the SpinPolarizedLDOS.
	 *
	 *  @param mode Mode with which the string has been serialized. */
	SpinPolarizedLDOS(const std::string &serialization, Mode mode);

	/** Destructor. */
//	~SpinPolarizedLDOS();

	/** Get lower bound for the energy.
	 *
	 *  @return Lower bound for the energy. */
	double getLowerBound() const;

	/** Get upper bound for the energy.
	 *
	 *  @return Upper bound for the energy. */
	double getUpperBound() const;

	/** Get the energy resolution (number of points used for the energy
	 *  axis).
	 *
	 *  @return The energy resolution. */
	int getResolution() const;

	/** Assignment operator. */
//	SpinPolarizedLDOS& operator=(const SpinPolarizedLDOS &rhs);

	/** Move assignment operator. */
//	SpinPolarizedLDOS& operator=(SpinPolarizedLDOS &&rhs);

	/** Overrides AbstractProperty::serialize(). */
	std::string serialize(Mode mode) const;
private:
	/** Lower bound for the energy. */
	double lowerBound;

	/** Upper bound for the energy. */
	double upperBound;

	/** Energy resolution. (Number of energy intervals) */
	int resolution;
};

inline double SpinPolarizedLDOS::getLowerBound() const{
	return lowerBound;
}

inline double SpinPolarizedLDOS::getUpperBound() const{
	return upperBound;
}

inline int SpinPolarizedLDOS::getResolution() const{
	return resolution;
}

};	//End namespace Property
};	//End namespace TBTK

#endif
