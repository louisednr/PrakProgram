# Homework: Least Squares Fit

This project implements a **General Least Squares** solver using QR decomposition. It features a physics application: analyzing the radioactive decay of Thorium X (Ra-224) using historical data from Rutherford and Soddy (1902).

## Features
- **Least Squares Solver**: Computes best-fit coefficients and the **covariance matrix** using QR decomposition.
- **Uncertainty Estimation**: Extracts parameter errors ($\delta a$, $\delta \lambda$) from the diagonal of the covariance matrix.
- **Data Linearization**: Fits the exponential model $y = ae^{-\lambda t}$ by transforming it to the linear form $\ln(y) = \ln(a) - \lambda t$.
- **Automated Plotting**: Integrated `gnuplot` support to generate `decay.svg`, displaying the raw data, best-fit curve, and confidence intervals.

## Prerequisites
- **Compiler**: A C++ compiler supporting C++23 (e.g., GCC 12+).
- **Tools**: `make` for building and `gnuplot` for generating the decay plot.

## Quick Start
To compile the code, perform the fit, and generate the SVG plot, run:
```bash
make