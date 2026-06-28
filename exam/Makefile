CXXFLAGS += -std=c++23 -I. -Wall -Wextra -Werror 
LDLIBS += -lstdc++ -lm


all: main berrut_plots.svg runge_comparison.svg out.txt

main: main.cc berrut.hpp spline.hpp
	$(CXX) $(CXXFLAGS) main.cc -o main

data_nodes.txt res_berrut.txt runge_nodes.txt runge_comparison.txt: main
	./main > out.txt

berrut_plots.svg: data_nodes.txt res_berrut.txt
	echo '\
		set terminal svg size 800,900 font "Helvetica,13";\
		set output "$@"; \
		set multiplot layout 3,1 title "Berrut B1 rational interpolation properties"; \
		set grid; \
		set ylabel "cos(x) and B1(x)"; \
		plot "data_nodes.txt" with points pt 7 lc "blue" title "data", \
		     "res_berrut.txt" using 1:2 with lines lc "red" lw 2 title "berrut B1"; \
		set ylabel "B1 Derivative"; \
		plot "res_berrut.txt" using 1:3 with lines lc "orange" lw 2 title "analytical derivative"; \
		set ylabel "Integral [0 to x]"; \
		set xlabel "x"; \
		plot "res_berrut.txt" using 1:4 with lines lc "green" lw 2 title "Gauss-Legendre antiderivative"; \
		unset multiplot; \
	' | gnuplot

runge_comparison.svg: runge_nodes.txt runge_comparison.txt
	echo '\
		set terminal svg size 800,500 font "Helvetica,15";\
		set output "$@"; \
		set title "Recreating Figure 1.3: Runge phenomenon comparison"; \
		set xrange [-6:6]; \
		set yrange [-0.4:2]; \
		set grid; \
		set xlabel "x"; set ylabel "y"; \
		plot "runge_comparison.txt" using 1:3 with lines lt 1 lc rgb "black" lw 1.5 title "polynomial", \
		     "runge_comparison.txt" using 1:4 with lines dt 2 lc rgb "red" lw 2 title "rational B1", \
		     "runge_comparison.txt" using 1:5 with lines dt 3 lc rgb "blue" lw 1.5 title "quadratic spline", \
		     "runge_nodes.txt" using 1:2 with points pt 7 ps 1.5 lc rgb "black" title "data"; \
	' | gnuplot

clean:
	$(RM) [Oo]ut* main.o *.txt *.svg 