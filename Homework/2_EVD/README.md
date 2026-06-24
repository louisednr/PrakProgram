# Homework: EVD (Eigenvalue decomposition)

This project implements the **Jacobi eigenvalue algorithm** to perform matrix diagonalization and applies it to solve the radial Schrödinger equation for the Hydrogen atom.

## Features
- **Part A Jacobi Algorithm**: Implemented with cyclic sweeps. Confirmed $A = VDV^T$ and eigenvector orthogonality ($V^TV = I$) for a random symmetric matrix.

- **Part B Hydrogen atom, s-wave radial Schrödinger equation on a grid**: Solves the s-wave radial Schrödinger equation on a discrete grid using the three-point finite difference formula. Investigates convergence of energies with respect to rmax and Δr in `rmax_convergence.svg` and `dr_convergence.svg`. Plots 4 lowest eigen-functions and compare with analytical results in `wavefunction.svg`.
- **Scaling Analysis**: Benchmarks the routine to verify the $O(N^3)$ time complexity of the Jacobi process, shown in `scaling_plot.svg`.

## Prerequisites
- **Compiler**: A C++ compiler supporting **C++23**.
- **Tools**: `make` for automation and `gnuplot` for generating SVG visualizations.

## Quick Start
To compile the project, run all physical simulations, verify matrix decomposition, and generate all performance and physics plots, use:
```bash
make
```

To remove the compiled executable, all intermediate data files (`.txt`), and the generated plots (`.svg`), use the following command:

```bash
clean
```