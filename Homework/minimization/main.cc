#include "matrix.hpp"
#include "qr.hpp"
#include "minimization.hpp"

#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <fstream>



// --- for tests ---

// Rosenbrock's valley function: f(x, y) = (1 - x)^2 + 100 * (y - x^2)^2
double rosenbrock(const pp::vector<double>& v) {
    double x = v[0];
    double y = v[1];
    return (1.0 - x) * (1.0 - x) + 100.0 * (y - x * x) * (y - x * x);
}

// Himmelblau's function: f(x, y) = (x^2 + y - 11)^2 + (x + y^2 - 7)^2
double himmelblau(const pp::vector<double>& v) {
    double x = v[0];
    double y = v[1];
    return (x * x + y - 11.0) * (x * x + y - 11.0) + (x + y * y - 7.0) * (x + y * y - 7.0);
}

// Breit-Wigner function  
double breit_wigner(double E, double m, double Gamma, double A) {
    double mass_term = (E - m) * (E - m);
    double width_term = (Gamma * Gamma) / 4.0;
    return A / (mass_term + width_term);
}

int main() {
    std::cout << std::scientific << std::setprecision(6);
    std::cout << "--- Part A ---\n\n";

    // --- Test 1: Rosenbrock minimum ---

    std::cout << "--- Minimizing Rosenbrock's valley function ---\n";
    pp::vector<double> ros_start = {0, 0};
    std::cout << "Starting guess: " << ros_start << "\n";
    
    pp::vector<double> ros_min = pp::minimize_newton(rosenbrock, ros_start);
    std::cout << "Calculated minimum location: " << ros_min << "\n";
    std::cout << "Function value at minimum:   " << rosenbrock(ros_min) << "\n\n";
    std::cout << "Expected min at: (1,1)" << "\n";

    
    // Test 2: Himmelblau minimum
    std::cout << "--- Minimizing Himmelblau's function ---\n";
    std::vector<pp::vector<double>> himmel_guesses = {
        { 2.0,  2.0},
        {-3.0,  3.0},
        {-3.5, -3.5},
        { 3.5, -3.5}
    };

    for (size_t i = 0; i < himmel_guesses.size(); ++i) {
        std::cout << "Basin Hunt " << i + 1 << " starting from: " << himmel_guesses[i] << "\n";
        pp::vector<double> him_min = pp::minimize_newton(himmelblau, himmel_guesses[i]);
        std::cout << "  -> Found Minimum Location: " << him_min << "\n";
        std::cout << "  -> Function Value here:    " << himmelblau(him_min) << "\n";
        
    }
    std::cout << "According to wiki has minimums at (3.0, 2.0), (-2.8, 3.1), (-3.8, -3.3) and (3.6, -1.8)" << "\n";

    std::cout << "--- Part B ---\n\n";

    // Read the (well formatted) data table from the standard input
    std::vector<double> energy;
    std::vector<double> signal;
    std::vector<double> error;
    
    double x, y, z;
    while (std::cin >> x >> y >> z) {
        energy.push_back(x);
        signal.push_back(y);
        error.push_back(z);
    }

    std::cerr << "Successfully loaded " << energy.size() << " data points from stdin.\n";

    auto deviation_D = [&energy, &signal, &error](const pp::vector<double>& v) {
        double m     = v[0];
        double Gamma = v[1];
        double A     = v[2];

        double sum_squares = 0.0;
        for (size_t i = 0; i < energy.size(); ++i) {
            double F = breit_wigner(energy[i], m, Gamma, A);
            double residual = (F - signal[i]) / error[i];
            sum_squares += residual * residual;
        }
        return sum_squares;
    };


    pp::vector<double> p_start = {126.0, 3.0, 15.0}; 
    
   
    pp::vector<double> p_fit = pp::minimize_newton(deviation_D, p_start, 1e-4);

    double fitted_mass  = p_fit[0];
    double fitted_width = p_fit[1];
    double fitted_scale = p_fit[2];

    std::cerr << "\n=== Fit Results ===\n";
    std::cerr << "Calculated Higgs mass (m):     " << fitted_mass << " GeV/c^2\n";
    std::cerr << "Experimental width (Gamma):   " << fitted_width << " GeV\n";
    std::cerr << "Fitted scale factor (A):       " << fitted_scale << "\n";
    std::cerr << "Final residual variance value: " << deviation_D(p_fit) << "\n";

    // --- Generate fit curve for plotting ---
    std::ofstream fit_file("fit.dat");
    if (fit_file.is_open()) {
        for (double E = 100.0; E <= 160.0; E += 0.2) {
            // Using your helper function with your variable: p_fit
            double F = breit_wigner(E, p_fit[0], p_fit[1], p_fit[2]);
            fit_file << E << " " << F << "\n";
        }
        fit_file.close();
    }

    return 0;
}