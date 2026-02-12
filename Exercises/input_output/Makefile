CXX = g++ -std=c++23
CXXFLAGS += -Wall -Wextra -Werror 
LDLIBS += -lstdc++ -lm

all: Out.txt
		cat $<


objects = main.o 

Out.txt: main
		./$< > $@ 


main : main.o 
	$(CC) -o main main.o  $(LDLIBS)


#approx.o : approx.h approx.cc
#$(CXX) $(CXXFLAGS) -o approx.o -c approx.cc

#approx.h 
main.o : main.cc 
	$(CXX) $(CXXFLAGS) -o main.o -c main.cc


clean: 
	$(RM) out.txt $(objects)
