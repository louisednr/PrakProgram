CXXFLAGS += -std=c++23 -I. -Wall -Wextra -Werror 
LDLIBS += -lstdc++ -lm



all: Out.txt error_plot.svg quasi_plot.svg


Out.txt circle_errors.txt: main Makefile
	@echo "--- Running Monte Carlo Tests ---" > Out.txt
	./main >> Out.txt

# AI genereated 
error_plot.svg: circle_errors.txt
	gnuplot -e "\
		set terminal svg background 'white'; \
		set output '$@'; \
		set xlabel 'Number of Samples (N)'; \
		set ylabel 'Absolute Error'; \
		set title 'Monte Carlo Integration Error vs Sample Size'; \
		plot 'circle_errors.txt' using 1:2 with linespoints title 'Estimated Error (Sigma)', \
		     'circle_errors.txt' using 1:3 with linespoints title 'Actual Error' \
	"

# End AI generated

quasi_plot.svg: scaling_data.txt
	gnuplot -e "\
		set terminal svg background 'white'; \
		set output '$@'; \
		set xlabel 'Number of Samples (N)'; \
		set ylabel 'Actual Absolute Error'; \
		set title 'Pseudo-Random vs Quasi-Random Error Scaling'; \
		plot 'scaling_data.txt' using 1:2 with lines title 'Pseudo-Random (LCG)', \
		     'scaling_data.txt' using 1:3 with lines title 'Quasi-Random (Halton vs Lattice)' \
	"

main: main.cc
	$(CXX) $(CXXFLAGS) main.cc -o main

clean:
	$(RM) Out.txt circle_errors.txt scaling_data.txt error_plot.svg quasi_plot.svg main