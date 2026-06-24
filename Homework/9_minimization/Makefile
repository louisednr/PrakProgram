CXXFLAGS += -std=c++23 -I. -Wall -Wextra -Werror 
LDLIBS += -lstdc++ -lm


HIGGS_PLOT = plot_higgs.svg


all: out.txt fit.dat $(HIGGS_PLOT)


main: main.cc matrix.hpp qr.hpp
	$(CXX) $(CXXFLAGS) main.cc -o main


out.txt fit.dat: main higgs_data.txt
	@echo "Running Newton minimizer on Higgs dataset..."
	./main < higgs_data.txt > out.txt 2> higgs_log.txt
	@cat higgs_log.txt

# Beginning of AI generated plotting
$(HIGGS_PLOT): out.txt fit.dat higgs_data.txt
	@echo "Plotting resonance fit track..."
	gnuplot -e "set terminal svg background 'white'; \
	            set output '$(HIGGS_PLOT)'; \
	            set title 'Higgs Boson Discovery Resonance Peak'; \
	            set xlabel 'Energy E (GeV)'; set ylabel 'Signal \\sigma(E)'; \
	            set grid; \
	            plot 'higgs_data.txt' u 1:2:3 w yerrorbars pt 7 ps 0.6 lc rgb 'red' title 'Experimental Data', \
	                 'fit.dat' u 1:2 w l lw 2.5 lc rgb 'blue' title 'Breit-Wigner Fit'"
# End of of AI generated plotting

clean:
	$(RM) [Oo]ut* main.o higgs_log.txt *.svg *.dat