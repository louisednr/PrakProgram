CXXFLAGS += -std=c++23 -I. -Wall -Wextra -Werror 
LDLIBS += -lstdc++ -lm


all: main dr_convergence.svg rmax_convergence.svg wavefunction.svg scaling_plot.svg Out.txt



Out.txt: main Makefile
	@echo "Running EigenValue Decomposition Tests..." > $@
	./main >> $@



# Convergence targets
convergence: dr_convergence.svg rmax_convergence.svg

#convergence inputs --------
dr_convergence.txt: main
	> $@ 
	for dr in $$(seq 0.1 0.1 0.8); do \
		./$< -convergence -rmax 10 -dr $$dr >> $@ ; \
	done

rmax_convergence.txt: main
	> $@
	for rmax in $$(seq 2 2 20); do \
		./$< -convergence -rmax $$rmax -dr 0.2 >> $@ ; \
	done

# convergences plots ----------
dr_convergence.svg: dr_convergence.txt
	echo '\
		set terminal svg; set output "$@"; \
		set title "Convergence of E0 vs Delta r (rmax=10)"; \
		set xlabel "Delta r"; set ylabel "E0 (Hartree)"; \
		plot "$<" using 1:3 with linespoints title "Calculated E0", -0.5 with lines lt 2 title "Exact (-0.5)" \
	' | gnuplot

rmax_convergence.svg: rmax_convergence.txt
	echo '\
		set terminal svg; set output "$@"; \
		set title "Convergence of E0 vs rmax (dr=0.2)"; \
		set xlabel "rmax"; set ylabel "E0 (Hartree)"; \
		plot "$<" using 2:3 with linespoints title "Calculated E0", -0.5 with lines lt 2 title "Exact (-0.5)" \
	' | gnuplot


# wavefuntion input 
wavefunction.txt: main
	./$< -rmax 80 -dr 0.5 > $@

# wavefunction plots
wavefunction.svg: wavefunction.txt
	echo '\
		set terminal svg; \
		set output "$@"; \
		set title "Hydrogen Reduced Radial Wavefunctions f(r) (1s-4s)"; \
		set xlabel "r (a.u.)"; set ylabel "f(r)"; \
		set xrange [0:40]; \
		set yrange [-0.5:1.0]; \
		set grid; \
		f1s(x) = 2*x*exp(-x); \
		f2s(x) = (1.0/sqrt(2))*x*(1.0 - 0.5*x)*exp(-x/2.0); \
		f3s(x) = (2.0/(3.0*sqrt(3.0)))*x*(1.0 - (2.0/3.0)*x + (2.0/27.0)*x**2)*exp(-x/3.0); \
		f4s(x) = 0.25*x*(1.0 - 0.75*x + 0.125*x**2 - (1.0/192.0)*x**3)*exp(-x/4.0); \
		plot "$<" using 1:2 with points pt 7 ps 0.5 title "Num 1s", \
		     "$<" using 1:3 with points pt 7 ps 0.5 title "Num 2s", \
		     "$<" using 1:4 with points pt 7 ps 0.5 title "Num 3s", \
		     "$<" using 1:5 with points pt 7 ps 0.5 title "Num 4s", \
		     f1s(x) with lines lc "black" title "Exact 1s", \
		     f2s(x) with lines lc "black" title "Exact 2s", \
		     f3s(x) with lines lc "black" title "Exact 3s", \
		     f4s(x) with lines lc "black" title "Exact 4s"; \
	' | gnuplot


# -------- AI Generated --------

SIZES := 50 100 150 200 250 300

scaling_results.txt: main
	@echo "Starting scaling analysis..."
	@rm -f $@
	for N in $(SIZES); do \
		./main -benchmark $$N >> $@; \
	done

scaling_plot.svg: scaling_results.txt
	echo '\
		set terminal svg; set output "$@"; \
		set title "Complexity Analysis: Jacobi Diagonalization"; \
		set xlabel "Matrix Size (N)"; set ylabel "Time (seconds)"; \
		set logscale xy; \
		f(x) = k * x**3; \
		fit f(x) "$<" via k; \
		plot "$<" using 1:2 with points pt 7 title "Measured Time", \
		     f(x) with lines title "O(N^3) Fit"; \
	' | gnuplot

#-------- End AI generation --------





main.o : matrix.hpp evd.hpp
main : main.o

clean:
	$(RM) [Oo]ut* *.txt *.svg main.o 
test:
	echo $(findstring clang++,$(CXX)) 
	echo $(CXX)
	echo $(CXXFLAGS)