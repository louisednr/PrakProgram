# Exam: 18 Berrut interpolation

The task of this project is to implement the Berrut $B_1$ rational function interpolation algorithm. As detailed in the course material, global interpolating functions can be utilized for fitting smooth paths between discrete data points, as well as estimating their local derivatives and total integrals. 

To expand the scope of the exam question, this implementation includes analytical differentiation and numerical integration of the rational interpolant. The models are verified against the piecewise quadratic spline from Homework 4 and a classic Lagrange polynomial by recreating the comparison shown in Figure 1.3 of the textbook PDF.


## Features

- **Part A & B: Berrut Interpolation, Derivatives, and Integration**
  The Berrut $B_1$ rational function interpolant is implemented as a struct in `berrut.hpp`. The file `berrut_plots.svg` visualizes the three properties tested on a $\cos(x)$ distribution:
    - The Berrut $B_1$ rational function interpolation.
    - The exact analytical derivative.
    - The cumulative definite integral evaluated from the starting node $x_i[0]$ up to $x$ using a 5-point Gauss-Legendre quadrature (as described in Chapter 7).

- **Part C: Recreating Figure 1.3 (Runge's Phenomenon Comparison)**
  The plot `runge_comparison.svg` replicates the textbook benchmark over the Runge function $f(x) = \frac{1}{1+x^2}$. It displays the exact function, a higher-order Lagrange polynomial, the quadratic spline from Homework 4, and the Berrut $B_1$ rational interpolant. The visualization clearly shows how the global polynomial suffers from Runge's phenomenon (larger edge oscillations), whereas the Berrut rational function successfully suppresses them.



## Prerequisites
- **Compiler**: A C++ compiler supporting C++23 (e.g., GCC 12+ or Clang).
- **Tools**: `make` for automated building and `gnuplot` for generating verification plots.

## Quick Start
To compile the code, run the verification tests, and generate the SVG plot, run the following command in your terminal:

```bash
make
```

To remove the compiled executable, all intermediate data files (`.txt`), and the generated plots (`.svg`), use the following command:

```bash
clean
```