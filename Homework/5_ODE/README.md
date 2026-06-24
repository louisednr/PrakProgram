# Homework: ODE

This project implements an embedded Runge-Kutta stepper with error estimate, and an adaptive-step-size driver for solving Ordinary Differential Equation Initial Value Problems (ODE IVP). 

## Features
- **Part A Embedded rule Runge-Kutta ODE integrator**: 
    - embedded Runge-Kutta stepper rkstepXY .
    - adaptive-step-size driver routine.
    - debug routines by solving u''=-u, this is seen in `out.txt`
    - Reproduce Lotka-Volterra system plot in `lv_plot.svg`
- **Part B Relativistic precession of planetary orbit**: Plotted in `precession_plot.svg`

## Prerequisites
- **Compiler**: A C++ compiler supporting C++23 (e.g., GCC 12+ or Clang).
- **Tools**: `make` for automated building and `gnuplot` for generating verification plots.

## Quick Start
To compile the code, run the verification tests, and generate the SVG plots, run the following command in your terminal:

```bash
make
```

To remove the compiled executable, all intermediate data files (`.txt`), and the generated plots (`.svg`), use the following command:

```bash
make clean