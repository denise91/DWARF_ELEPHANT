# DwarfElephant

<h4 align="center">A numerical simulator enabling the usage of the reduced basis method based on <a href="http://mooseframework.org/" target="blank">MOOSE</a>.</h4>

<p align="center">
<a href="LICENSE">
<img src="https://img.shields.io/badge/license-GPLv2.1-blue.svg"
alt="GitHub License">
</a>
</p>

## General
Process simulations are important for many scientific and economic questions. Many process simulations are too computationally demanding to allow the employment of inverse processes. The issue is that these inverse processes are important to incorporate, for instance, uncertainties.

DwarfElephant implements the reduced basis (RB) method within the MOOSE framework. Our implementation is primarily based on the rbOOmit package provided by [libMesh](https://libmesh.github.io). Using the RB method, we can construct surrogate models that result in fast forward solves. This, in turn, allows the usage of computationally complex inverse processes, such as uncertainty quantification and global sensitivity studies. 

The RB method is a model order reduction technique that aims at constructing low order approximations of, for instance, finite element simulations. For further information, we refer to (Hesthaven et al., 2016; Prud’homme et al., 2002).

DwarfElephant is a MOOSE-based application. Visit the [MOOSE framework](http://mooseframework.org) page for more information regarding the underlying frameworks.

## Licence
DwarfElephant is distributed under the [GNU GENERAL PUBLIC LICENSE v2.1](https://github.com/denise91/DwarfElephant/blob/master/LICENSE).


## Getting Started

### 1. Installing DwarfElephant
For the installation of DwarfElephant you need the latest installation of the MOOSE framework. 
To install  MOOSE, we refer to the [Getting Started](http://mooseframework.org/getting-started/) page of the MOOSE framework and follow the instructions. 

DwarfElephant can be cloned directly from [GitHub](https://github.com/denise91/DwarfElephant) using [Git](https://git-scm.com/). For all following instructions, we assume that you want to clone DwarfElephant into the directory  `projects`, as advised during the MOOSE installation (by default `~/projects`):  

cd ~/projects
git clone https://github.com/denise91/DwarfElephant.git
cd ~/projects/DwarfElephant
git checkout master

*Note: the "master" branch of DwarfElephant  is always the "stable" branch that is only updated after passing all tests.*

### 2. Compiling DwarfElephant
You can compile DwarfElephant with the following instructions:

cd ~/projects/DwarfElephant
make -j 4

### 3. Testing DwarfElephant
To ensure that everything is working correctly, please run the tests provided in the package. In case you want to contribute to the package, ensure that you generate a test for your implementations. In that way, we can ensure that new code developments are not interfering with your implementations.

cd ~/projects/DwarfElephant
./run_tests -j 4

If all test passed, then you successfully installed the DwarfElephant package!

## Usage
We advise running DwarfElephant from the command line. 
To run it with a single processor, use the following command:

~/projects/golem/DwarfElephant-opt -i <input-file>

and to run it with multiple processors, use:

mpiexec -n <nprocessors> ~/projects/golem/golem-opt -i <input-file>

Here, `<nprocessors>` define the number of processors used in the code execution and`<input-file>` is the path to your input file (extension `.i`).  

Detailed information about the practical usage of the software package and the structure of the inputfile can be found in the documentation (see folder  `tutorial`).

## Cite

If you use DwarfElephant please cite:

Degen, D., Veroy, K., & Wellmann, F. (2020a). Certified reduced basis method in geosciences. Computational Geosciences, 24(1), 241-259.


## Publications using DwarfElephant

* Degen, D., Veroy, K., Freymark, J., Scheck-Wenderoth, M., & Wellmann, F. (2020b). Global Sensitivity Analysis to Optimize Basin-Scale Conductive Model Calibration - Insights on the Upper Rhine Graben. https://doi.org/10.31223/osf.io/b7pgs

* Degen, D., Veroy, K., & Wellmann, F. (2020a). Certified reduced basis method in geosciences. Computational Geosciences, 24(1), 241-259.


## References

* Hesthaven, J. S., Rozza, G., Stamm, B., et al. (2016). Certified reduced basis methods for parametrized partial differential equations. SpringerBriefs in Mathematics, Springer.

* Prud’Homme, C., Rovas, D. V., Veroy, K., Machiels, L., Maday, Y., Patera, A. T., & Turinici, G. (2002). Reliable real-time solution of parametrized partial differential equations: Reduced-basis output bound methods. J. Fluids Eng., 124(1), 70-80.

