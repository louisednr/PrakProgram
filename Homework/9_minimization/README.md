# Homework: Root Finding

Implements Newton's method with numerical gradient, numerical Hessian matrix and back-tracking linesearch. Then Fit the Breit-Wigner function to CERN data and determine the mass and the experimental width of the Higgs boson.

## Features

- **Part A**:  minimum of the Rosenbrock's valley function and the Himmelblau's function are printed to `out.txt`. 
- **Part B Higgs boson discovery**: Fit and experimental data are shown in `plot_higgs.svg`.

## Prerequisites
- **Compiler**: A C++ compiler supporting C++23 (e.g., GCC 12+ or Clang).
- **Tools**: `make` for automated building and `gnuplot` for generating verification plots.

## Quick Start
To compile the code, run the verification tests, and generate the SVG plot (`plot_higgs.svg`), run the following command in your terminal:

```bash
make
```

To remove the compiled executable, all intermediate data files (`.txt`), and the generated plots (`.svg`), use the following command:

```bash
clean
```