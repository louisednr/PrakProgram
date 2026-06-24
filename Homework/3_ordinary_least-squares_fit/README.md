# Homework: Ordinary least-squares fit

This project implements a **Ordinary least-squares** fit using own QR decomposition. Then analyzes the radioactive decay of Thorium X (Ra-224) using historical data from Rutherford and Soddy (1902).

## Features
- **Part A Least-squares fit**: Computes best-fit coefficients and using QR decomposition. Fit expoentnial law to given  radioactive decay data. Comparison to modern data 
- **Part B Uncertainty Estimation**: Modifyes LSF so covariance matrix is returned. 
- **Data Linearization**: Fits the exponential model $y = ae^{-\lambda t}$ by transforming it to the linear form $\ln(y) = \ln(a) - \lambda t$.
- **Automated Plotting**: Integrated `gnuplot` support to generate `decay.svg`, displaying the raw data, best-fit curve, and confidence intervals.

## Prerequisites
- **Compiler**: A C++ compiler supporting C++23 (e.g., GCC 12+).
- **Tools**: `make` for building and `gnuplot` for generating the decay plot.

## Quick Start
To compile the code, perform the fit, and generate the SVG plot, run:
```bash
make