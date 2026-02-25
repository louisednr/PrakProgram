CXXFLAGS += -Wall -std=c++23
LDLIBS += -lstdc++ -lm

all: fig1.svg fig2.svg fig3.svg

# Rule for erf plot
fig1.svg: fig1.gpi erf.data table.data
	gnuplot $<

# Rule for gamma plot
fig2.svg: fig2.gpi gamma.data gamma_table.data
	gnuplot $<

# Rule for lngamma plot
fig3.svg: fig3.gpi lngamma.data
	gnuplot $<


# Generate Erf data
erf.data: main
	./$< -mode erf -xmin 0 -xmax 3.5 -dx 0.02 > $@

# Generate Gamma data
gamma.data: main
	./$< -mode gamma -xmin -5 -xmax 5 -dx 0.0001 > $@



lngamma.data: main
	./$< -mode lngamma -xmin 0 -xmax 6 -dx 0.01 > $@


main: main.cc
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDLIBS)

clean:
	rm -f main erf.data gamma.data lngamma.data *.svg log.*