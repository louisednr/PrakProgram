# Homework: Ordinary least-squares fit

This project implements a **Ordinary least-squares** fit using own QR decomposition. Then analyzes the radioactive decay of Thorium X (Ra-224) using historical data from Rutherford and Soddy (1902).

## Features
- **Part A Least-squares fit**: Computes best-fit coefficients and using QR decomposition. Fit expoentnial law to given radioactive decay data. 
- **Part B Uncertainty Estimation**: Modifies LSF so covariance matrix is returned. Comparison to modern data is printes in `out.txt`.
- **Part C plotting** Evaluation of the quality of the uncertainties of the fit coefficients, by plotting `decay.svg`.

## Prerequisites
- **Compiler**: A C++ compiler supporting C++23 (e.g., GCC 12+).
- **Tools**: `make` for building and `gnuplot` for generating the decay plot.

## Quick Start
To compile the code, perform the fit, and generate the SVG plot, run:

```bash
make
```

To remove the compiled executable, all intermediate data files (`.txt`), and the generated plots (`.svg`), use the following command:

```bash
clean
```