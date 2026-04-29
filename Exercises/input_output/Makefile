CXX = g++
CXXFLAGS = -std=c++23 -Wall -Wextra -Werror 
LDLIBS = -lstdc++ -lm

# 1. 'all' should only point to run_tests
all: run_tests

# 2. Link the program
main: main.o 
	$(CXX) -o main main.o $(LDLIBS)

# 3. Compile the source
main.o: main.cc 
	$(CXX) $(CXXFLAGS) -c main.cc

# 4. Your automated test suite
run_tests: main
	@echo "--- 1: Command-line ---"
	./main -n 1 -n 2 -n 3
	
	@echo "\n--- 2: Standard input stream ---"
	echo "4 5 6" | ./main
	
	@echo "\n--- 3: File streams ---"
	echo "7 8 9" > my_input_file.txt
	./main --input my_input_file.txt --output my_output_file.txt
	@echo "Results written to my_output_file.txt:"
	cat my_output_file.txt

clean: 
	$(RM) main main.o my_input_file.txt my_output_file.txt Out.txt
