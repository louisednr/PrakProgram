# Homework: "Eigenvalue Decomposition (EVD)"

This project implements the **Jacobi eigenvalue algorithm** to perform matrix diagonalization and applies it to solve the radial Schrödinger equation for the Hydrogen atom.

## Features
- **Jacobi Algorithm**: Implemented with cyclic sweeps, featuring $O(n)$ in-place `timesJ` and `Jtimes` rotations.
- **EVD Verification**: Confirms $A = VDV^T$ and eigenvector orthogonality ($V^TV = I$) for random symmetric matrices.
- **Quantum Simulation**: Solves the s-wave radial Schrödinger equation on a discrete grid using the three-point finite difference formula.
- **Physical Analysis**: Includes automated plotting for energy convergence ($\epsilon_0$ vs. $r_{max}$ and $\Delta r$) and wavefunction comparison (Numerical vs. Analytical 1s-4s).
- **Scaling Analysis**: Benchmarks the routine to verify the $O(N^3)$ time complexity of the Jacobi process.

## Prerequisites
- **Compiler**: A C++ compiler supporting **C++23**.
- **Tools**: `make` for automation and `gnuplot` for generating SVG visualizations.

## Quick Start
To compile the project, run all physical simulations, verify matrix decomposition, and generate all performance and physics plots, use:
```bash
make