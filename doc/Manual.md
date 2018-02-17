Manual {#manual}
======

- @subpage Introduction
- @subpage Overview
- @subpage UnitHandler
- @subpage Model
- @subpage Solve
- @subpage ExtractProperties

@page Introduction Introduction

# Origin and scope {#OriginAndScope}
TBTK (Tight-Binding ToolKit) originated as a toolkit for solving tight-binding models.
However, the scope of the code has expanded beyond the area implied by its name, and is today best described as a library for building applications that solves second-quantized Hamiltonians with discrete indices  

<center>\f$H = \sum_{\mathbf{i}\mathbf{j}}a_{\mathbf{i}\mathbf{j}}c_{\mathbf{i}}^{\dagger}c_{\mathbf{j}} + \sum_{\mathbf{i}\mathbf{j}\mathbf{k}\mathbf{l}}V_{\mathbf{i}\mathbf{j}\mathbf{k}\mathbf{l}}c_{\mathbf{i}}^{\dagger}c_{\mathbf{j}}^{\dagger}c_{\mathbf{k}}c_{\mathbf{l}}\f$.</center>

# Algorithms and data structures {#AlgorithmsAndDataStructures}

When writing software it is natural to think in terms of algorithms.
This is particularly true in scientific computation, where the objective most of the time is to carry out a set of well defined operations on an input state to arrive at a final answer.
Algorithm centered thinking is manifested in the imperative programing paradigm and is probably the best way to learn the basics of programming and to implement simple tasks.
However, while algorithms are of great importance, much of the success of todays computer software can be attributed to the development of powerful data structures.

Anyone who has writen software that is more than a few hundred lines of code knows that a major challange is to organize the code in such a way that the complexity do not scale up with the size of the project.
Otherwise, when e.g. coming back to a project after a few months, it may be difficult to make modifications to the code since you do not remember if or how it will affects other parts of the code.
The reason for this can largly be traced back to the lack of proper attention paid to data structures.
In particular, well designed data structures enables abstraction and encapsulation and is a core component of the object oriented programming paradigm.

Abstraction is the process of dividing code into logical units that aids the thinking process by allowing the programmer to think on a higher level.
Effective abstraction allows the programmer to forget about low level details and focus on the overarching problem at hands.
For some analogies, mathemtics and physics are rife with abstractions: derivatives are defined through limits but differential equations are written using derivative symbols, matrices are rectangles of numbers but we carry out much of the algebra manipulating letters representing whole matrices rather than individual matrix elements, etc.
Much of mathematics is ultimately just addition, subtraction, multiplication, and division of real numbers, but through abstraction problems of much greater complexity can be tackled than if everything was formulated with those four symbols alone.
Similarly programming is nothing but loops, conditional execution, assignment of values, function calls etc., but further abstraction allows the programmers mind to be freed from low level details to focus on the higher level aspects of much more complex problems.

While abstraction means dividing code into logical units that allows the programmer to think on a higher level, encapsulation means making those units largly independent of each other.
Different parts of a program should of course interact with each other, but low level details of a specific component should to an as large degree as posible be invisible to other components.
Instead of allowing (and requiring) other components of a code to manipulate its low level details, components should strive to present themself to other components through an easy to use interface.
The interface is provided through a so called application programming interface (API).
The API is essentially a contract between a component and the outside world, where the component specifies a promisse to solve a particular problem given a particular input.
Encapsulation makes it possible to update a piece of code without remembering what other parts of the code is doing, as long as the update respects the contract specified in the API, and is key to solving the scalability issue.
Developers mainly experienced with imperative programming likely recognize some of these concepts as being emboddied in the idea of dividing code into functions.
Object oriented programming greatly extends this powerful technique.

Scientific computing is often computationally intensive and much thought therefore goes into the development of different algorithms for solving the same problem.
Different algorithms may have their own strengths and weaknesses making them the preffered choice under different circumstances.
Often such algorithms are implemented in completely different software packages with little reuse of code, even though the code for the main algorithm may be a small part of the actual code.
This is a likely result when data structures are an afterthought and results in both replicated work and less reliable code since code that is reused in multiple projects is much more extensively tested.
A key to handling situations like this is called polymorphis and is a principle whereby different components essentially provides identical or partly identical contracts to the outside world, even though they internally may work very differently.
This allows for components to be used interchangeably with little changes to the rest of the code base.

TBTK is first and foremost a collection of data structures intended to enable the implementation of algorithms for solving quantum mechanical problems, but also implements several different algorithms for solving specific problems.

# c++11: Performance vs. ease of use {#cpp11PerformanceVsEaseOfUse}

Scientific computations are often very demanding and high performance is therefore often a high priority.
However, while low level programming languages offer high performance, they also have a reputation of being relatively difficult to work with.
A comparatively good understanding of the low level details of how a computer works is usually required to write a program in languages such as c/c++ and FORTRAN compared to e.g. MATLAB and python.
However, while c++ provides the ability to work on a very low level, it also provides the tools necessary to abstract away much of these details.
A well writen library can alleviate many of these issues, such as for example putting little requirement on the user to manage memory (the main source of errors for many new c/c++ programmers).
Great progress in this direction was taken with the establishment of the c++11 standard.
The language of choice for TBTK has therefore been c++11, and much effort has gone into developing data structures that is as simple as possible to use.
Great care has also been taken to avoid having the program crash without giving error messages that provide information that helps the user to resolve the problem.

@page Overview Overview

# Model, Solvers, and PropertyExtractors {#ModelSolversAndPropertyExtractors}
It is useful to think of a typical scientific numerical study as involving three relatively separate decissions:
- What is the model?
- What method to use?
- What properties to calculate?

When writing code, the answer to these three questions essentially determines the input, algorithm, and output, respectively.
To succesfully cary out studies of complex problems, it is important that it is easy to set up the model and to extract the properties, and that the underlying algorithm that performs the work is efficient.
However, the simultaneous requirement on the algorithm to be efficient and that the calculation is easy to set up easily run countrary to each other.
Efficiency often require low level optimization in the algorithm, which e.g. can put strict requirment of how the input and output is represented in memory.
If this means the user is required to setup the input and extract the output on a format that requires deep knowledge about the internal workings of the algorithm, two important problems arise.
First, if details about the algorithm is required to be kept in mind at all levels of the code it hinders the user from thinking about the problem on a higher level where numeric nuisance has been abstracted  away.
Second, if the specific requirements of an algorithm determines the structure of the whole program, the whole code has to be rewritten if the choice is made to try another algorithm.

To get around these problems TBTK is designed to encourage a workflow where the three stages of specifying input, chosing algorithm, and extracting properties are largly independent from each other.
To achieve this TBTK has a class called a Model that allows for general models to be setup.
Further, algorithms are implemented in a set of different Solvers, which takes a Model and internally converts it to the format most suitable for the algorithm.
Finally, the Solver is wrapped in a PropertyExtractor, where the different PropertyExtractors have a uniform interface.
By using the PropertyExtractors to extract properties from the Model, rather than by calling the Solvers directly, most code do not need to be changed if the Solver is changed.

# Auxiliary tasks
While the three questions above captures the essence of a typical scientific problem, auxiliary tasks such as reading/writing data from/to file, plotting, etc. are required to solve a problem.
TBTK therefore also have a large set of tools for simplifying such tasks, allowing the developer to put more mental effort into the main scientific questions.
Further, a fundamental key feature of TBTK is that it also comes with a powerful method for handling units.
While physical quantities often are expressed in terms of some specific combinations of units such as K, eV, C, etc. it is often useful to work in some for the problem at hands natural set of units.
In high-energy physics this may mean \f$ \hbar = c = 1\f$, while in condensed matter physics it can be useful to express energies in terms of Rydbergs or some arbitrary unit set by a hopping parameter.
For this TBTK provides a UnitHandler that enables the developer to specify the natural units for the given problem.
All function calls to TBTK functions should be understood to be in terms of the specified natural units.

# Implementing applications {#ImplementingApplications}
For developers interested in implementing calculations that are meant to answer specific physical questions, which is also refered to as implementing applications, TBTK comes ready with a set of native Solvers.
This manual is mainly intended to describe this use case and therefore covers the most important classes needed to achieve this.
In particular, this manual outlines how to properly setup a Model, select a Solver, and to extract properties using PropertyExtractors.

# Implementing new Solvers {#ImplementingNewSolvers}
TBTK is also intended to enable the development of new Solvers and provides many classes ment to simplify this task.
This manual does not cover all these classes and the interested developer is instead refered to the API for a more detailed description.
However, developers are still encouraged to study this manual to understand the design philosophy behind TBTK, and to also use the already existing Solvers as inspiration when writing new Solvers.
Doing so can significantly reduce the amount of overhead required to create a new Solver and makes it easier for other developers to use the new Solver in their own project.
The development of new Solvers are greatly encouraged and if you are interested in doing so but have any questions, please contact Kristofer Björnson at kristofer.bjornson@physics.uu.se.
New Solvers can either be released as stand alone packages or be pulled into the TBTK library.
In the later case the Solver will have to adhere to the main development philosophy of TBTK, but we are happy with providing help with polishing the Solver to the point that it does.

@page UnitHandler UnitHandler

# Units and constants {#UnitsAndConstants}
Most quantities of interest in physics have units, which means that the numerical value of the quantity depends on which units it is measured in.
Different sets of units are relevant in different situations, e.g. is meter (m) a relevant unit for length in macroscopic problems, while Ångström (Å) is more relevant on atomic scales.
However, computers work with unitless numbers, which means that any piece of code that relies on hard coded numerical values for physical constants implicitly force the user of the code to work in the same set of units.
This is unacceptable for a library such as TBTK which aims at allowing physicist with different preferences for units to use the library to implement their own calculations.
Simulatenously it is of value to not require the developer to specify the numerical value of every constant before development can begin.
Contrary, it is very useful if the library itself can supply such constants in whatever units the developer prefer.
To solve these issues, TBTK provides a UnitHandler that allows the user to specify what units are natural to the problem at hands, and all numbers passed to TBTK functions are assumed to be given in these natural units.

# Base units, derived units, and natural units {#BaseUnitsDerivedUnitsAndNaturalUnits}
The UnitHandler borrows its terminology from the SI standard for units.
Not by forcing the user to work in SI units, but rather through a clear division of units into base units and derived units.
To understand what this means, consider distances and times.
These are quantities that are defined independently from each other and can be measured in for example meters (m) and seconds (s).
In comparison, a velocity is a measure of distance per time and cannot be defined independently of these two quantities.
Velocity can therefore be considered to be a quantity that is derived from the more fundamental quantities distance and time.
In principle, there is no reason why a given quantity has to be considered more fundamental than any other, and it is perfectly valid to e.g. view time as a quantity derived from the more fundamental quantities distance and velocity.
However, the fact remains that for the three quantities distance, time, and velocity, only two at a time can be defined independently from each other.
Further, among all the quantities encountered in physics, only seven can be defined independently from each other.
By fixing seven such quantities, a set of seven corresponding base units can be defined.
All other units are considered derived units.

The UnitHandler defines the fundamental quantities to be temperature, time, length, energy, charge, and count (amount).
This is the first point where the UnitHandler deviates from the SI system, since the SI system do not define the units for energy and charge as base units, but instead the units for mass, current, and luminosity.
Note in particular that the UnitHandler currently only defines base units for six different quantities.
The missing quantity is due to ambiguity regarding whether angles should be considered unitfull or unitless quantities.
Units for angle may therefore be added to the UnitHandler in the future.
The decission to make the units for energy and charge base units, rather than mass and current as in the SI system, is based on a subjective perception of the former being more generally relevant in quantum mechanical calculations.

Next, the UnitHandler also deviates from the SI system by only fixing the base quantities rather than the base units.
While e.g. the SI unit for length is meter (m), the UnitHandler allows the base unit for length to be set to a range of different units such as meter (m), millimiter (mm), nanometer (nm), Ångström (Å), etc.
Similarly a range of different options are available for other quantities, such as for example Joule (J) and electronvolt (eV) for energy, and Coulomb (C) and elementary charge (e) for charge.

## Base units
By default the base units are
| Quantity    | Default base unit  |
|-------------|--------------------|
| Temperature | K (Kelvin)         |
| Time        | s (seconds)        |
| Length      | m (meter)          |
| Energy      | eV (electron Volt) |
| Charge      | C (Coulomb)        |
| Count       | pcs (pieces)       |

Further the available base units are
| Quantity    | Available base units                             |
|-------------|--------------------------------------------------|
| Temperature | kK, K, mK, uK, nK                                |
| Time        | s, ms, us, ns, ps, fs, as                        |
| Length      | m, mm, um, nm, pm, fm, am, Ao                    |
| Energy      | GeV, MeV, keV, eV, meV, ueV, J                   |
| Charge      | kC, C, mC, uC, nC, pC, fC, aC, Te, Ge, Me, ke, e |
| Count       | pcs, mol                                         |

Most of these units should be self-explanatory, with Gx, Mx, kx, mx, etc. corresponds to giga, mega, kilo, milli, etc.
Further, Ao corresponds to Ångström (Å), while pcs corresponds to pieces.
If further base units are wanted, please do not hesitate to request the addition of additional base units.

If base units other than the default base units are wanted, it is recommended to set the base units at the very start of a program.
For example at the first line in the main routine.
This avoids ambiguities that results from changing base units in the middle of execution.
To for example set the base units to mK, ps, Å, meV, C, and mol, type
```cpp
	UnitHandler::setTemperatureUnit(UnitHandler::TemeratureUnit::mK);
	UnitHandler::setTimeUnit(UnitHandler::TimeUnit::ps);
	UnitHandler::setLengthUnit(UnitHandler::LengthUnit::Ao);
	UnitHandler::setEnergyUnit(UnitHandler::EnergyUnit::meV);
	UnitHandler::setChargeUnit(UnitHandler::ChargeUnit::C);
	UnitHandler::setCountUnit(UnitHandler::CountUnit::mK);
```

@page Model Model

# The Model class {#TheModelClass}
The main class for setting up a model is the Model class.
The Model acts as a container of the Hamiltonian, temperature, chemical potential, etc.
A typical initialization of a Model looks like
```cpp
	Model model;
	model.setTemperature(300);
	model.setChemicalPotential(0);
	//Feed the model with information about the Hamiltonian
	//...
```

@page Solve Solvers

@page ExtractProperties PropertyExtractors