CXX = g++
CXXFLAGS = -std=c++23 -Wall


all: main decay.svg 


main: main.cc lsfit.hpp matrix.hpp qr.hpp
	$(CXX) $(CXXFLAGS) main.cc -o main


data.txt fit_results.txt: main
	./main

# AI generated ----
decay.svg: data.txt fit_results.txt Makefile
	echo '\
		set terminal svg background "white"; \
		set output "$@"; \
		set title "Radioactive Decay of ThX (Rutherford & Soddy, 1902)"; \
		set xlabel "Time (days)"; \
		set ylabel "Activity (relative units)"; \
		set grid; \
		set key top right; \
		stats "fit_results.txt" using 1 nooutput; a = STATS_min; \
		stats "fit_results.txt" using 2 nooutput; l = STATS_min; \
		stats "fit_results.txt" using 3 nooutput; da = STATS_min; \
		stats "fit_results.txt" using 4 nooutput; dl = STATS_min; \
		f(x) = a * exp(-l * x); \
		f_upper(x) = (a + da) * exp((-l - dl) * x); \
		f_lower(x) = (a - da) * exp((-l + dl) * x); \
		plot \
			"data.txt" using 1:2:3 with errorbars lt 6 lc rgb "black" title "Data", \
			f(x) with lines lw 2 lc rgb "#77000000" title "Best Fit", \
			f_upper(x) with lines dt 2 lc rgb "blue" title "Fit + {/Symbol d}c", \
			f_lower(x) with lines dt 2 lc rgb "#05963a" title "Fit - {/Symbol d}c"; \
		' | gnuplot

# end AI generated ------


clean:
	rm -f main decay.svg data.txt fit_results.txt out.txt



