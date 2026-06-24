# Homework: Artificial Neural Networks

Part A implements a simple artificial neural network which will be trained to interpolate a `g(x)=Cos(5*x-1)*Exp(-x*x)`, this is done using 10 nodes. Part B implements modifies the network, after training, could also return the first and second derivatives and also the anti-derivative of the approximant to the tabulated function.

## Plots
- **Part A**: `interpolation_plot.svg`
- **Part B**: `calc_plot.svg`

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
clean
```