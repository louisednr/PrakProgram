#include<iostream>
#include<vector>
#include<fstream>
#include <cmath>


int main (int argc, char* argv[]) {

    std::vector<double> n_vals;
    std::string infile = "", outfile = "";

	// read all arguments
	for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-n" && i + 1 < argc) {
            n_vals.push_back(std::stod(argv[++i]));
        } else if (arg == "--input" && i + 1 < argc) {
            infile = argv[++i];
        } else if (arg == "--output" && i + 1 < argc) {
            outfile = argv[++i];
        }
    }


	if (!infile.empty() && !outfile.empty()) {
        std::ifstream input(infile);
        std::ofstream output(outfile);
        double x;
        if (input.is_open() && output.is_open()) {
            while (input >> x) {
                output << x << " " << std::sin(x) << " " << std::cos(x) << std::endl;
            }
        }
    } 


	else if (!n_vals.empty()) {
        for (double n : n_vals) {
            std::cout << n << " " << std::sin(n) << " " << std::cos(n) << std::endl;
        }
    } 
  
    else {
        double x;
        while (std::cin >> x) {
            std::cout << x << " " << std::sin(x) << " " << std::cos(x) << std::endl;
        }
    }

    return 0;

}



