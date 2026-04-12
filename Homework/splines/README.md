# Homework: Linear and Quadratic Splines

This project implements **Linear** and **Quadratic** spline interpolation methods in C++. It features mathematical verification using trigonometric functions and debug tests using polynomial tables to ensure the analytical derivatives and integrals are calculated correctly.

## Features
- **Linear Spline**: 
    - Piecewise linear interpolation $s_i(x) = y_i + p_i(x-x_i)$.
    - Analytical definite integral (antiderivative) representing the accumulated area under the spline.
- **Quadratic Spline**: 
    - Piecewise quadratic interpolation $q_i(x) = y_i + b_i(x-x_i) + c_i(x-x_i)^2$.
    - Continuous first derivative $s'(x)$ across all nodes.
    - Analytical antiderivative (piecewise cubic) calculated via $\int_{x_i}^z q_i(t)dt$.
- **Binary Search**: Efficient $O(\log n)$ interval location using the bisection method.
- **Verification Suite**: 
    - Automated tests against constant, linear, and quadratic tables.
    - Comparison of spline derivatives and integrals against known analytical functions.

## Prerequisites
- **Compiler**: A C++ compiler supporting C++23 (e.g., GCC 12+ or Clang).
- **Tools**: `make` for automated building and `gnuplot` for generating verification plots.

## Quick Start
To compile the code, run the verification tests, and generate the SVG plots (`plot_linear.svg` and `plot_quad.svg`), run the following command in your terminal:

```bash
make


To remove the compiled executable, all intermediate data files (`.txt`), and the generated plots (`.svg`), use the following command:

```bash
make clean