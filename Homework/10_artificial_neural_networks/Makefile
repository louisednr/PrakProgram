CXXFLAGS += -std=c++23 -I. -Wall -Wextra -Werror 
LDLIBS += -lstdc++ -lm


all: interpolation_plot.svg calc_plot.svg Out.txt

Out.txt: main Makefile
	@echo "Running ANN tests..." > $@
	./main >> $@ 2>&1

main: main.cc matrix.hpp ann.hpp qr.hpp minimization.hpp
	$(CXX) $(CXXFLAGS) main.cc -o main

data.txt derivatives_data.txt: main
	./main

interpolation_plot.svg: data.txt
	gnuplot -e "\
		set terminal svg background 'white'; \
		set output '$@'; \
		set title 'Part A: ANN Target Function vs. Prediction'; \
		set grid; \
		set xlabel 'x'; \
		set ylabel 'y'; \
		plot 'data.txt' using 1:2 with lines title 'Target Function g(x)' lw 2 lc rgb 'purple', \
		     'data.txt' using 1:3 with points title 'ANN Interpolation' pt 7 ps 1 lc rgb '#3b9c76'"

calc_plot.svg: derivatives_data.txt
	gnuplot -e "\
		set terminal svg background 'white'; \
		set output '$@'; \
		set title 'Part B: Analytical Network Derivatives vs. True Values' font 'Sans,12 bold'; \
		set grid; \
		set xlabel 'x'; \
		set ylabel 'y'; \
		plot 'derivatives_data.txt' using 1:3 with lines title 'ANN Fp\047(x)' lw 2 lc rgb 'blue', \
		     'derivatives_data.txt' using 1:6 with lines title 'True g\047(x)' lw 1.5 lc rgb 'dark-blue' dt 2, \
		     'derivatives_data.txt' using 1:4 with lines title 'ANN Fp\047\047(x)' lw 2 lc rgb 'orange', \
		     'derivatives_data.txt' using 1:7 with lines title 'True g\047\047(x)' lw 1.5 lc rgb 'dark-orange' dt 2, \
		     'derivatives_data.txt' using 1:(\$$5) with lines title 'ANN Anti-derivative' lw 2 lc rgb 'red'"

clean:
	rm -f main data.txt interpolation_plot.svg calc_plot.svg derivatives_data.txt Out.txt