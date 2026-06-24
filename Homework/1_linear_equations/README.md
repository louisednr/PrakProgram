# Homework: Linear equations

This project implements a linear algebra library in C++ for solving systems of linear equations, calculating matrix inverses, and finding determinants using QR decomposition.

## Features
- **Part A Matrix/Vector Classes**: Column storage using `std::vector`.
- **Part A QR Decomposition**: Implemented with the **Modified Gram-Schmidt** process.
- **Part A Linear Solver**: Solves $QRx = b$ using back-substitution + determinant.
- **Part B Matrix Inverse**: Computes $A^{-1}$ by solving $Ax_i = e_i$ for each unit vector $e_i$.
- **Part C Time dependance**: Includes plotting to check the $O(N^3)$ time dependance of the QR factorization. This is shown in figure `times.svg`

## Prerequisites
- **Compiler**: A C++ compiler supporting C++23.
- **Tools**: `make` for building and `gnuplot` for generating time dependance plot.

## Quick Start
To compile the project, run the tests, and generate the performance graph, use:
```bash
make
```

To remove the compiled executable, all intermediate data files (`.txt`), and the generated plots (`.svg`), use the following command:

```bash
clean
```