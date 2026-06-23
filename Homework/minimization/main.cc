#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <fstream>
#include "matrix.hpp"
#include "qr.hpp"

namespace pp {

    // numerical gradient 
    template <typename F>
    vector<double> gradient(F phi, const vector<double>& x, double phi_x) {
        int n = x.size();
        vector<double> g(n);
        vector<double> x_perturbed = x;

        for (int i = 0; i < n; ++i) {
            double abs_xi = std::abs(x[i]);
            double dxi = (1.0 + abs_xi) * std::pow(2.0, -26.0);

            x_perturbed[i] += dxi;
            double phi_perturbed = phi(x_perturbed);
            g[i] = (phi_perturbed - phi_x) / dxi;
            
            x_perturbed[i] = x[i];
        }
        return g;
    }

    // Numerical Hessian matrix
    template <typename F>
    matrix<double> hessian(F phi, const vector<double>& x, const vector<double>& g_x) {
        int n = x.size();
        matrix<double> H(n, n);
        vector<double> x_perturbed = x;

        for (int j = 0; j < n; ++j) {
            double abs_xj = std::abs(x[j]);
            double dxj = (1.0 + abs_xj) * std::pow(2.0, -13.0); 

            x_perturbed[j] += dxj;
            double phi_perturbed_x = phi(x_perturbed);
            vector<double> g_perturbed = gradient(phi, x_perturbed, phi_perturbed_x);
            
            vector<double> dg = g_perturbed - g_x; 
            for (int i = 0; i < n; ++i) {
                H(i, j) = dg[i] / dxj; 
            }

            x_perturbed[j] = x[j];
        }

        // Enforce mathematical symmetry: H_ij = (H_ij + H_ji) / 2
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                double avg = (H(i, j) + H(j, i)) / 2.0;
                H(i, j) = avg;
                H(j, i) = avg;
            }
        }
        return H;
    }

    // Newton minimization method with numerical gradient,
    template <typename F>
    vector<double> minimize_newton(F phi, const vector<double>& x_start, double acc = 1e-3, int max_iter = 1000) {
        vector<double> x = x_start;
        int steps_taken = 0;

        for (int iter = 0; iter < max_iter; ++iter) {
            double phi_x = phi(x);
            vector<double> g = gradient(phi, x, phi_x);

            
            if (g.norm() < acc) { 
                break;
            }
            steps_taken++;

            matrix<double> H = hessian(phi, x, g);

            // Levenberg regularization
            for (int i = 0; i < H.size1(); ++i) {
                H(i, i) += 1e-6;
            }

            
            qr<double> qr_solver(H);
            vector<double> minus_g = -g;
            vector<double> dx = qr_solver.solve(minus_g);

    
            double lambda = 1.0;
            vector<double> z;

            // using Armijo condition form p. 2 in minimization pdf
            while (lambda >= 1.0 / 1024.0) { 
                z = x + dx * lambda;
                if (phi(z) < phi_x) {
                    break;
                }
                lambda /= 2.0;
            }

            
            x = (lambda >= 1.0 / 1024.0) ? z : (x + dx * (1.0 / 1024.0));
        }

        std::cout << "  Iterations to converge: " << steps_taken << "\n";
        return x;
    }

} // namespace pp

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