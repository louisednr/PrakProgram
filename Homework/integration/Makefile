CXXFLAGS += -std=c++23 -I. -Wall -Wextra -Werror 
LDLIBS += -lstdc++ -lm



all: Out.txt comparison.svg error_plot.svg

#Out.txt: main Makefile
#	@echo "Running Integration Tests..." > $@
#	./main >> Out.txt

Out.txt: main compare.py Makefile
	@echo "--- Running C++ Integration Tests ---" > $@
	./main >> $@
	@echo "" >> $@
	@echo "--- Running Python/SciPy Benchmarks ---" >> $@
	python3 compare.py >> $@

# finding rows begining with numbers and putting into data file
error_data.txt: Out.txt
	grep -E "^[0-9]" Out.txt > error_data.txt || true

# plot
# AI genereated 
error_plot.svg: error_data.txt
	gnuplot -e "\
		set terminal svg background 'white'; \
		set output '$@'; \
		set xlabel 'Target Accuracy (acc)'; \
		set ylabel 'Actual Absolute Error'; \
		set logscale xy; \
		set format x '%.0e'; \
		set title 'Erf(1) Integration Error vs Target Accuracy'; \
		plot 'error_data.txt' using 1:2 with linespoints title 'Actual Error', x title 'Ideal Line (Error = acc)' lc rgb 'gray' dt 2 \
	"
# end AI generated

comparison.svg: Out.txt compare.py
	python3 compare.py

main: main.cc
	$(CXX) $(CXXFLAGS) main.cc -o main

clean:
	$(RM) Out.txt error_data.txt error_plot.svg comparison.svg main