# Homework: Root Finding

Implement the Newton's method with simple backtracking line-search algorithm where the derivatives in the Jacobian matrix are calculated numerically using finite differences as described in the Book. Then investiagtes Bound states of hydrogen atom with shooting method for boundary value problems.

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