CXX = g++ -std=c++23
CXXFLAGS += -Wall -Wextra -Werror 
LDLIBS += -lstdc++ -lm

all: Out.txt
		cat $<


objects = main.o sfuns.o

Out.txt: main
#		./main > Out.txt
		./$< > $@ 
# avoid typing the names twice, so don't mispell.

main : main.o sfuns.o
	$(CC) -o main main.o sfuns.o $(LDLIBS)

sfuns.o : sfuns.h sfuns.cc
	$(CXX) $(CXXFLAGS) -o sfuns.o -c sfuns.cc
main.o : sfuns.h main.cc
	$(CXX) $(CXXFLAGS) -o main.o -c main.cc


clean: 
	$(RM) Out.txt $(objects)
