# Homework: Root Finding

Implements the Newton's method with simple backtracking line-search algorithm where the derivatives in the Jacobian matrix are calculated numerically using finite differences. Then investiagtes bound states of hydrogen atom with shooting method for boundary value problems.

## Features
- **Part A Newton's method with numerical Jacobian and back-tracking line-search**: Tested on 1D function, Rosenbrock's valley function and Himmelblau's function seen in `Out.txt`.
- **Part B Bound states of hydrogen atom with shooting method for boundary value problems**: Wavefunctions is plotted in `wavefunction.svg`. Investigation of the convergence of solution towards the exact result displayed in `rmin.svg`, `conv_rmax.svg` and `plot_conv.svg`.



## Prerequisites
- **Compiler**: A C++ compiler supporting C++23 (e.g., GCC 12+ or Clang).
- **Tools**: `make` for automated building and `gnuplot` for generating verification plots.

## Quick Start
To compile the code, run the verification tests, and generate the SVG plots (`wavefunction.svg`, `conv_rmax.svg`, `rmin.svg` and `plot_conv.svg`), run the following command in your terminal:

```bash
make
```

To remove the compiled executable, all intermediate data files (`.txt`), and the generated plots (`.svg`), use the following command:

```bash
clean
```