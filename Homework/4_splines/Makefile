CXX = g++
CXXFLAGS = -std=c++23 -Wall

all: main lin_plot.svg quad_plot.svg out.txt

main: main.cc
	$(CXX) $(CXXFLAGS) main.cc -o main

data.txt results.txt res_quad.txt: main
	./main > out.txt

lin_plot.svg: data.txt results.txt
	echo '\
		set terminal svg;\
		set output "$@"; \
		set multiplot layout 2,1 title "Linear spline & integrator check"; \
		set grid; \
		set ylabel "cos(x) and Spline"; \
		plot "data.txt" with points pt 7 lc "blue" title "Data", \
		     "results.txt" using 1:2 with lines lc "red" title "Linear spline"; \
		set ylabel "Integral [0 to x]"; \
		set xlabel "x"; \
		plot "results.txt" using 1:3 with lines lc "green" title "Antiderivative"; \
		unset multiplot; \
	' | gnuplot


quad_plot.svg: data.txt res_quad.txt
	echo '\
		set terminal svg;\
		set output "$@"; \
		set multiplot layout 3,1 title "Quadratic spline check"; \
		set grid; \
		set ylabel "s(x)"; \
		plot "data.txt" with points pt 7 lc "blue" title "Nodes", \
		     "res_quad.txt" using 1:2 with lines lc "red" title "Quad spline"; \
		set ylabel "s\047(x)"; \
		plot "res_quad.txt" using 1:3 with lines lc "orange" title "Derivative"; \
		set ylabel "Integral"; set xlabel "x"; \
		plot "res_quad.txt" using 1:4 with lines lc "green" title "Integral"; \
		unset multiplot; \
	' | gnuplot

clean:
	rm -f main data.txt results.txt lin_plot.svg res_quad.txt quad_plot.svg