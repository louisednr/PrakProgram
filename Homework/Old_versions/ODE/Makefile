CXX = g++
CXXFLAGS = -std=c++23 -Wall

all: main lv_plot.svg

lv_solve_data.txt: main precession_plot.svg
	./main

orbit_circ.txt orbit_ell.txt orbit_prec.txt: main
	./main




main: main.cc ODE.hpp
	$(CXX) $(CXXFLAGS) main.cc -o main


# plotting
lv_plot.svg: lv_solve_data.txt
	echo '\
		set terminal svg background "white"; \
		set output "$@"; \
		set title "Lotka-Volterra system"; \
		set xlabel "Time"; \
		set xlabel "Population"; \
		set grid; \
		set xtics 0.0, 2.5, 15.0; \
		set ytics 0, 2, 12; \
		plot "lv_solve_data.txt" using 1:2 with lines lc rgb "royalblue" lw 2 title "x" , \
		     "lv_solve_data.txt" using 1:3 with lines lc rgb "orange" lw 2 title "y"; \
	' | gnuplot

precession_plot.svg: orbit_circ.txt orbit_ell.txt orbit_prec.txt
	echo '\
		set terminal svg background "white"; \
		set output "$@"; \
		set size square; \
		set grid; \
		set title "Planetary Orbits"; \
		plot "orbit_circ.txt" using (1/$$2)*cos($$1):(1/$$2)*sin($$1) with lines title "Circular (eps=0)", \
		     "orbit_ell.txt"  using (1/$$2)*cos($$1):(1/$$2)*sin($$1) with lines title "Elliptical (eps=0)", \
		     "orbit_prec.txt" using (1/$$2)*cos($$1):(1/$$2)*sin($$1) with lines title "Precessing (eps=0.01)"; \
	' | gnuplot


clean:
	rm -f main *.txt *.svg

