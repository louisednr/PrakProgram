CXX = g++ -std=c++23
CXXFLAGS += -Wall -Wextra -Werror 
LDLIBS += -lstdc++ -lm

all: Out.txt
		cat $<


objects = main.o approx.o

Out.txt: main
		./$< > $@ 


main : main.o approx.o
	$(CC) -o main main.o approx.o $(LDLIBS)

approx.o : approx.h approx.cc
	$(CXX) $(CXXFLAGS) -o approx.o -c approx.cc
main.o : approx.h main.cc
	$(CXX) $(CXXFLAGS) -o main.o -c main.cc


clean: 
	$(RM) Out.txt $(objects)
