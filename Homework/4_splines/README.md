# Homework: Linear and Quadratic Splines

This project implements **Linear** and **Quadratic** spline interpolation methods in C++. 

## Features
- **Part A Linear spline**: 
    - piecewise linear interpolation.
    - analytically antiderivative
    - PIndicative plots to prove that your linear spline and your integrator work as intended are in `lin_plot.svg`
- **Part B Quadratic Spline**: Quadratic spline with derivative and definite integral (anti-derivative) using OOP style. Plots shown in `quad_plot.svg` and comparision to table in `out.txt`

## Prerequisites
- **Compiler**: A C++ compiler supporting C++23 (e.g., GCC 12+ or Clang).
- **Tools**: `make` for automated building and `gnuplot` for generating verification plots.

## Quick Start
To compile the code, run the verification tests, and generate the SVG plots (`plot_linear.svg` and `plot_quad.svg`), run the following command in your terminal:

```bash
make
```

To remove the compiled executable, all intermediate data files (`.txt`), and the generated plots (`.svg`), use the following command:

```bash
make clean