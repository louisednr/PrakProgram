# Homework: Monte Carlo integration


This project implements a plain Monte Carlo multi-dimensional integration, a multidimensional Monte-Carlo integrator that uses low-discrepancy (quasi-random) sequences, and compares the simple LCG, the generator from the standard C++ library and using your quasi-random sequences.

## Features
- **Part A Plain Monte Carlo integration**: area of a unit circle calculate andlong with estimated and actual error, this is plotted in `error_plot.svg`. Volume of a three-dimensional ellipsoid is in `Out.txt`.
- **Part B Quasi-random sequences**: Comparison of the scaling of the error is shown in `quasi_plot.svg`. Comparison of simple LCG, the generator from the standard C++ library and quasi-random sequences is printed in `Out.txt`


## Prerequisites
- **Compiler**: A C++ compiler supporting C++23.
- **Tools**: `make` for building and `gnuplot` for generating the plot.

## Quick Start
To compile the project, run the tests, and generate the performance graph, use:
```bash
make