CXXFLAGS += -std=c++23 -I. -Wall -Wextra -Werror 
LDLIBS += -lstdc++ -lm


all: main Out.txt times.svg



Out.txt: main Makefile
	@echo "Running QR decomposition tests..." > $@
	./main >> $@




 

out.times.data : main 
	> $@
	for N in $$(seq 30 20 630); do \
		./$< -timing $$N >> $@ ; \
	done

times.svg: out.times.data Makefile
	echo '\
		set terminal svg ;\
		set output "$@" ;\
		set title "Operations count for QR-decomposition";\
		set xlabel "Matrix dimensions" ;\
		set ylabel "Real time in (s)" ;\
		set grid;\
		set key top left Left reverse; \
		a = 0.5; b = 0.5; c = 0.5; d = 0.5; \
		f(x) = a*x*x*x + b*x*x + c*x + d ;\
		fit f(x) "$<" using 1:2 via a,b,c,d ;\
		plot \
			"$<" using 1:2 with points lt 7 title "qr time dependance" \
			, f(x) with lines title "fitting to cubic equation O(N^3)" ;\
		' | tee log.times | gnuplot



main.o : matrix.hpp qr.hpp
main : main.o

clean:
	$(RM) [Oo]ut* main.o log.times fit.log times.svg
test:
	echo $(findstring clang++,$(CXX)) 
	echo $(CXX)
	echo $(CXXFLAGS)