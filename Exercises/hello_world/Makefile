CXXFLAGS = -std=c++23 -O
LDLIBS = -lstdc++ -lm



Out.txt : main
		./main > Out.txt

main: main.o hello.o
	g++ main.o hello.o -o main

main.o : hello.hpp main.cc
		g++ -c main.cc -o main.o

hello.o: hello.hpp hello.cc
	g++ -c hello.cc -o hello.o


clean: 
	$(RM) Out.txt main

test:
	echo $(CXX)