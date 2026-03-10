# Homework: "Linear Equations"


This project implements a linear algebra library in C++ for solving systems of linear equations, calculating matrix inverses, and finding determinants using QR decomposition.

## Features
- **Custom Matrix/Vector Classes**: Column-major storage using `std::vector`.
- **QR Decomposition**: Implemented with the **Modified Gram-Schmidt** process.
- **Linear Solver**: Solves $QRx = b$ using back-substitution.
- **Matrix Inverse**: Computes $A^{-1}$ by solving $Ax_i = e_i$ for each unit vector $e_i$.
- **Time dependance**: Includes plotting to check the $O(N^3)$ time dependance of the QR factorization.

## Prerequisites
- **Compiler**: A C++ compiler supporting C++23.
- **Tools**: `make` for building and `gnuplot` for generating time dependance plot.

## Quick Start
To compile the project, run the tests, and generate the performance graph, use:
```bash
make