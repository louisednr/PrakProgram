# Homework: "Recursive Adaptive Integration"

This project implements an adaptive **open quadrature integrator** with a **Clenshaw–Curtis variable transformation** to resolve endpoint singularities and evaluate convergent infinite-limit integrals.

## Features
- **Part A Recursive open 4-point adaptive integrator**: This is tested on integrals suggested in exercise + implement error function. Comparision plotted in `error_plot.svg`.
- **Part B Variable transformation quadratures**: Adaptive integrator with the Clenshaw–Curtis variable transformation. Compared to python integration routine in `comparison.svg`.
- **Part C Error estimate**: Error estimation tested for diffrent target acc. SHow in `Out.txt`


## Prerequisites
- **Compiler**: A C++ compiler supporting **C++23**.
- **Tools**: `make` for automation, python3 (with scipy and matplotlib), and gnuplot for generating SVG visualizations.

## Quick Start
compile the source code, execute the adaptive integration tests, run the Python/SciPy benchmarks, and generate the comparative performance graphs, use:

```bash
make
```

To remove the compiled executable, all intermediate data files (`.txt`), and the generated plots (`.svg`), use the following command:

```bash
make clean