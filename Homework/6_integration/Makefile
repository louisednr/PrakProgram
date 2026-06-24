CXXFLAGS += -std=c++23 -I. -Wall -Wextra -Werror 
LDLIBS += -lstdc++ -lm


all: Out.txt error_plot.svg comparison.svg

Out.txt: main compare.py Makefile
	@echo "--- Running C++ Integration Tests ---" > $@
	./main >> $@
	@echo "" >> $@
	@echo "--- Running Python/SciPy Benchmarks ---" >> $@
	python3 compare.py >> $@

# plot
# AI genereated 
error_plot.svg: erf_error.txt
	gnuplot -e "\
		set terminal svg background 'white'; \
		set output '$@'; \
		set xlabel 'Target Accuracy (acc)'; \
		set ylabel 'Actual Absolute Error'; \
		set logscale xy; \
		set format x '%.0e'; \
		set title 'Erf(1) Integration Error vs Target Accuracy'; \
		plot 'erf_error.txt' using 1:2 with linespoints title 'Actual Error', x title 'Ideal Line (Error = acc)' lc rgb 'gray' dt 2 \
	"
# end AI generated

comparison.svg: Out.txt compare.py
	python3 compare.py

main: main.cc
	$(CXX) $(CXXFLAGS) main.cc -o main

clean:
	$(RM) Out.txt erf_error.txt error_plot.svg comparison.svg main