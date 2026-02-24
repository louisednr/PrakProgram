CXX = g++ -std=c++23
CXXFLAGS += -Wall -Wextra -Werror 
LDLIBS += -lstdc++ -lm

all: Out.txt
		cat $<


Out.txt: main
#		./main > Out.txt
		./$< > $@ 


main: main.o
	$(CXX) $(CXXFLAGS) $^ -o $@



main.o: vec.h main.cc



clean: 
	$(RM) Out.txt main