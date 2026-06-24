CXXFLAGS += -std=c++23 -I. -Wall -Wextra -Werror 
LDLIBS += -lstdc++ -lm

WAVEFUNCTION = wavefunction.svg
CONV_RMAX    = conv_rmax.svg
CONV_RMIN    = rmin.svg
PLOT_CONV    = plot_conv.svg


all: main Out.txt plots



Out.txt: main Makefile
	@echo "Running root tests..." > $@
	./main >> $@

main.o : matrix.hpp qr.hpp ODE.hpp
main : main.o

plots: main
	./main
	@echo "Generating plots ..."
	
	#  Wavefunction Comparison
	# ---- Beginning AI generated plotting ----
	gnuplot -e "set terminal svg background 'white'; \
	            set output '$(WAVEFUNCTION)'; \
	            set title 'Hydrogen Ground State Wavefunction Comparison'; \
	            set xlabel 'Radius r (Bohr)'; set ylabel 'f(r)'; \
	            set grid; \
	            plot 'wave_function.dat' u 1:3 w p pt 7 ps 0.6 title 'Exact Analytical Solution (re^{-r})', \
	                 'wave_function.dat' u 1:2 w l lw 2 title 'Numerical Shooting Method'"

	# Convergence rmax
	gnuplot -e "set terminal svg background 'white'; \
	            set output '$(CONV_RMAX)'; \
	            set title 'Energy Absolute Error Convergence vs Truncation Radius r_{max}'; \
	            set xlabel 'r_{max} (Bohr)'; set ylabel 'Absolute Energy Error |E_0 - E_{exact}|'; \
				set grid; \
	            plot 'conv_rmax.dat' u 1:2 w lp pt 7 lw 2 lc rgb 'blue' title 'Error Curve'"

	# Convergence rmin
	gnuplot -e "set terminal svg background 'white'; \
	            set output '$(CONV_RMIN)'; \
	            set title 'Energy Absolute Error Convergence vs Singularity Boundary r_{min}'; \
	            set xlabel 'r_{min} (Bohr)'; set ylabel 'Absolute Energy Error |E_0 - E_{exact}|'; \
	            set logscale x; set logscale y; set grid; \
	            plot 'conv_rmin.dat' u 1:2 w lp pt 7 lw 2 lc rgb 'red' title 'Error Curve'"

	#  Convergence acc + eps
	gnuplot -e "set terminal svg background 'white'; \
	            set output '$(PLOT_CONV)'; \
	            set title 'Energy Absolute Error Convergence vs ODE Tolerances (acc, eps)'; \
	            set xlabel 'Integrator Tolerance Threshold'; set ylabel 'Absolute Energy Error |E_0 - E_{exact}|'; \
	            set logscale x; set logscale y; set grid; \
	            plot 'conv_tol.dat' u 1:2 w lp pt 7 lw 2 lc rgb 'forest-green' title 'Error Curve'"
	# ---- End AI generated plotting ----
	# All plots generated




clean:
	$(RM) [Oo]ut* main.o *.svg *.dat
