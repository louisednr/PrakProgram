CXX = g++ -std=c++23
CXXFLAGS += -Wall -Wextra -Werror 
LDLIBS += -lstdc++ -lm

all: Out.txt
		cat $<


Out.txt: main
#		./main > Out.txt
		./$< > $@ 


main: main.o vec.o

main.o: vec.h

vec.o: vec.h

clean: 
	$(RM) Out.txt main