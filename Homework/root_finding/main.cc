#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <fstream>
#include "matrix.hpp"
#include "qr.hpp"
#include "ODE.hpp"

namespace pp {

    // Jacobian estimate adapted to c++ from example in exercise text
    template <typename F>
    matrix<double> Jacobian(F f, const vector<double>& x, const vector<double>& fx) {
        int n = x.size();
        matrix<double> J(n, n);
        vector<double> x_perturbed = x;

        for (int j = 0; j < n; ++j) {
            // from exercise: δxi = Max(|xi|,1)*2^(-26)
            double abs_xj = std::abs(x[j]);
            double dx = (abs_xj > 1.0 ? abs_xj : 1.0) * std::pow(2.0, -26.0);

       
            x_perturbed[j] += dx;
            vector<double> fx_perturbed = f(x_perturbed);

        
            vector<double> df = fx_perturbed - fx;
            for (int i = 0; i < n; ++i) {
                J(i, j) = df[i] / dx;
            }

            
            x_perturbed[j] = x[j];
        }
        return J;
    }

    // Newton's method with simple backtracking line-search algorithm and numerical jacobian
    // Adapted from python example in exercise
    template <typename F>
    vector<double> newton(F f, const vector<double>& x_start, double acc = 1e-7, double alpha_min = 1e-5, int max_iter = 1000) {
        vector<double> x = x_start;
        vector<double> fx = f(x);

        for (int iter = 0; iter < max_iter; ++iter) {
            // stop iterations if the condition is satisfied 
            if (fx.norm() < acc) {
                break;
            }

            // calculate numerical Jacobian and solve the linear system for the Newton step
            matrix<double> J = Jacobian(f, x, fx);
            qr<double> qr_solver(J);
            vector<double> minus_fx = -fx;
            vector<double> Dx = qr_solver.solve(minus_fx); // this is NEwton's step

            // checking that step size is not too small
            double dx_limit_norm2 = 0.0;
            for (int i = 0; i < x.size(); ++i) {
                double abs_xi = std::abs(x[i]);
                double dxi = (abs_xi > 1.0 ? abs_xi : 1.0) * std::pow(2.0, -26.0);
                dx_limit_norm2 += dxi * dxi;
            }
            double dx_limit_norm = std::sqrt(dx_limit_norm2);

            // stoppinginterations if step-size is smaller than the numerical delta_x size
            if (Dx.norm() < dx_limit_norm) {
                break; 
            }

            // linesearch
            double alpha = 1.0;
            vector<double> z;
            vector<double> fz;

            while (true) {
                z = x + Dx * alpha;
                fz = f(z);


                if (fz.norm() < (1.0 - alpha/2.0) * fx.norm()) {
                    break;
                }
                
                if (alpha < alpha_min) {
                    z = x + Dx * alpha_min;  // Unconditionally take the minimum step size
                    fz = f(z);               // Re-evaluate function values here
                    break; 
                }
                alpha /= 2.0;
            }

            x = z;
            fx = fz;
        }
        return x;
    }

} // namespace pp



// --- for tests ---


// 1. f(x) = x^3 - 2x - 5 = 0 (root at 2.0946 accoridng to wolframalpha)
pp::vector<double> test_1d(const pp::vector<double>& x) {
    pp::vector<double> f(1);
    f[0] = x[0]*x[0]*x[0] - 2.0*x[0] - 5.0;
    return f;
}

// 2. analytical gradient of Rosenbrock's valley function
// choose a=1 and b=100 like i wiki article
pp::vector<double> rosenbrock_grad(const pp::vector<double>& v) {
    double x = v[0];
    double y = v[1];
    pp::vector<double> grad(2);
    grad[0] = -2.0 * (1.0 - x) - 400.0 * x * (y - x*x);
    grad[1] = 200.0 * (y - x*x);
    return grad;
}

// 3. analytical gradient of Himmelblau's function
pp::vector<double> himmelblau_grad(const pp::vector<double>& v) {
    double x = v[0];
    double y = v[1];
    pp::vector<double> grad(2);
    grad[0] = 4.0 * x * (x*x + y - 11.0) + 2.0 * (x + y*y - 7.0);
    grad[1] = 2.0 * (x*x + y - 11.0) + 4.0 * y * (x + y*y - 7.0);
    return grad;
}



// Auxiliary function M(E) from exercise description
// takes guess for energy E, runs ODE and returns FE(rmax)
double auxiliary_M(double E, double rmin, double rmax, double acc, double eps) {
    // Define ODEs: y[0] = f(r), y[1] = f'(r)
    auto schrodinger_r_hand_side = [E](double r, const pp::vector<double>& y) {
        pp::vector<double> dydr(2);
        dydr[0] = y[1];                         // f'(r)
        dydr[1] = -2.0 * (E + 1.0 / r) * y[0];   // f''(r)
        return dydr;
    };

    //  boundary conditions
    pp::vector<double> y_init(2);
    y_init[0] = rmin - rmin * rmin;          // f(rmin)
    y_init[1] = 1.0 - 2.0 * rmin;            // f'(rmin)

    // integrate using ODE from ODE.hpp
    auto [r_list, y_list] = driver(schrodinger_r_hand_side, rmin, rmax, y_init, 0.01, acc, eps);

    // M(E) = FE(rmax)
    return y_list.back()[0];
}


int main() {
    std::cout << std::scientific << std::setprecision(6);

    std::cout << "--- Part A ---\n\n";



    std::cout << "--- Test 1: 1D function ---\n";
    std::cout << "f(x) = x^3 - 2x - 5 = 0 (root at 2.0946 accoridng to wolframalpha)\n";
    pp::vector<double> x1_start = {2.0};
    pp::vector<double> r1 = pp::newton(test_1d, x1_start);
    std::cout << "Starting from: " << x1_start << " -> found root: " << r1 << "\n\n";


    std::cout << "--- Test 2: Rosenbrock's valley function gradient roots ---\n";
    std::cout << "--- Extremum at (1,1), if choose a=1 and b=100 ---\n";
    pp::vector<double> ros_start = {-1.0, 1.0};
    pp::vector<double> r_ros = pp::newton(rosenbrock_grad, ros_start);
    std::cout << "Starting from: " << ros_start << " -> found extremum: " << r_ros << "\n\n";

    std::cout << "--- Test 3: Himmelblau's function gradient roots ---\n";
    std::vector<pp::vector<double>> himmel_guesses = {
        { 3.0,  1.0},
        {-3.0,  3.0},
        {-3.5, -3.5},
        { 3.5, -3.5}
    };
    std::cout << "According to wiki has minimums at (3.0, 2.0), (-2.8, 3.1), (-3.8, -3.3) and (3.6, -1.8)\n";

    for(size_t i = 0; i < himmel_guesses.size(); ++i) {
        pp::vector<double> r_him = pp::newton(himmelblau_grad, himmel_guesses[i]);
        std::cout << "Guess " << i+1 << ": " << himmel_guesses[i] 
                  << " -> found minimum: " << r_him << "\n";
    }

    std::cout << "--- Part B ---\n\n";

    // Baseline Parameters
    double rmin = 1e-4;
    double rmax = 8.0;
    double acc  = 1e-4;
    double eps  = 1e-4;

    // 1) Find the lowest root, E0, of the equation M(E)=0 rmax=8. 
    // Plot the resulting wave-function and compare with the exact result 
    // (which is E0=-½, f0(r)=re-r – check this by inserting E0 and f0(r) into the Schrodinger equation above).
    auto M_root_wrapper = [rmin, rmax, acc, eps](const pp::vector<double>& E_vec) {
        pp::vector<double> res(1);
        res[0] = auxiliary_M(E_vec[0], rmin, rmax, acc, eps);
        return res;
    };

    pp::vector<double> E_solved = pp::newton(M_root_wrapper, pp::vector<double>{-0.6}, 1e-7);
    double E0 = E_solved[0];

    auto final_r_hand_side = [E0](double r, const pp::vector<double>& y) {
        pp::vector<double> dydr(2);
        dydr[0] = y[1];
        dydr[1] = -2.0 * (E0 + 1.0 / r) * y[0];
        return dydr;
    };
    
    pp::vector<double> y_init(2);
    y_init[0] = rmin - rmin * rmin;
    y_init[1] = 1.0 - 2.0 * rmin;

    auto [r_data, y_data] = driver(final_r_hand_side, rmin, rmax, y_init, 0.01, acc, eps);
    
    std::ofstream wf_file("wave_function.dat");
    for (size_t i = 0; i < r_data.size(); ++i) {
        double r = r_data[i];
        wf_file << r << " " << y_data[i][0] << " " << (r * std::exp(-r)) << "\n";
    }
    wf_file.close();

    // 2) Investigate the convergence of your solution towards the exact result 
    // with respect to the rmax 
    std::ofstream rmax_file("conv_rmax.dat");
    for (double rmax_val : {4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0}) {
        auto wrapper = [rmin, rmax_val, acc, eps](const pp::vector<double>& E_vec) {
            return pp::vector<double>{ auxiliary_M(E_vec[0], rmin, rmax_val, acc, eps) };
        };
        double solved = pp::newton(wrapper, pp::vector<double>{-0.6}, 1e-7)[0];
        rmax_file << rmax_val << " " << std::abs(solved - (-0.5)) << "\n";
    }
    rmax_file.close();

    // 3) With respect to rmin
    std::ofstream rmin_file("conv_rmin.dat");
    for (double rmin_val : {1e-1, 5e-2, 1e-2, 5e-3, 1e-3, 5e-4, 1e-4, 5e-5, 1e-5}) {
        auto wrapper = [rmin_val, rmax, acc, eps](const pp::vector<double>& E_vec) {
            return pp::vector<double>{ auxiliary_M(E_vec[0], rmin_val, rmax, acc, eps) };
        };
        double solved = pp::newton(wrapper, pp::vector<double>{-0.6}, 1e-7)[0];
        rmin_file << rmin_val << " " << std::abs(solved - (-0.5)) << "\n";
    }
    rmin_file.close();

   
    // 4) Convergence and acc & eps
 
    std::ofstream tol_file("conv_tol.dat");
    for (double tol : {1e-2, 5e-3, 1e-3, 5e-4, 1e-4, 5e-5, 1e-5, 5e-6, 1e-6}) {
        auto wrapper = [rmin, rmax, tol](const pp::vector<double>& E_vec) {
            return pp::vector<double>{ auxiliary_M(E_vec[0], rmin, rmax, tol, tol) };
        };
        double solved = pp::newton(wrapper, pp::vector<double>{-0.6}, 1e-7)[0];
        tol_file << tol << " " << std::abs(solved - (-0.5)) << "\n";
    }
    tol_file.close();

    std::cout << "Data collection completely successfully compiled into .dat files." << std::endl;

    std::cout << "Plotted in .svg files" << std::endl;

    return 0;
}