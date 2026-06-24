
#pragma once

#include <cmath>
#include <vector>
#include <iostream>
#include "matrix.hpp"
#include "qr.hpp"

namespace pp {

    // A) numerical gradient 
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
            
            x_perturbed[i] = x[i]; // reset
        }
        return g;
    }


    // B) numerical gradient (central difference)
    template <typename F>
    vector<double> gradient_central(F phi, const vector<double>& x) {
        int n = x.size();
        vector<double> g(n);
        vector<double> x_perturbed = x;

        for (int i = 0; i < n; ++i) {
            double abs_xi = std::abs(x[i]);
            // Optimal step size is eps^(1/3) which is 2^(-17)
            double dxi = (1.0 + abs_xi) * std::pow(2.0, -17.0);

            x_perturbed[i] = x[i] + dxi;
            double phi_plus = phi(x_perturbed);

            x_perturbed[i] = x[i] - dxi;
            double phi_minus = phi(x_perturbed);

            g[i] = (phi_plus - phi_minus) / (2.0 * dxi);
            x_perturbed[i] = x[i]; // reset
        }
        return g;
    }

    // A) Numerical Hessian matrix
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

        // enforce mathematical symmetry: H_ij = (H_ij + H_ji) / 2
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                double avg = (H(i, j) + H(j, i)) / 2.0;
                H(i, j) = avg;
                H(j, i) = avg;
            }
        }
        return H;
    }

    // B) Numerical Hessian matrix (central difference)
    template <typename F>
    matrix<double> hessian_central(F phi, const vector<double>& x) {
        int n = x.size();
        matrix<double> H(n, n);
        vector<double> x_perturbed = x;

        for (int j = 0; j < n; ++j) {
            double abs_xj = std::abs(x[j]);
            double dxj = (1.0 + abs_xj) * std::pow(2.0, -17.0); 

            x_perturbed[j] = x[j] + dxj;
            vector<double> g_plus = gradient_central(phi, x_perturbed);

            
            x_perturbed[j] = x[j] - dxj;
            vector<double> g_minus = gradient_central(phi, x_perturbed);
            
            
            vector<double> dg = g_plus - g_minus; 
            for (int i = 0; i < n; ++i) {
                H(i, j) = dg[i] / (2.0 * dxj); 
            }

            x_perturbed[j] = x[j]; // reset
        }

       
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

    // Newton minimization method (central difference)
    template <typename F>
    vector<double> minimize_newton_central(F phi, const vector<double>& x_start, double acc = 1e-3, int max_iter = 1000) {
        vector<double> x = x_start;
        int steps_taken = 0;

        for (int iter = 0; iter < max_iter; ++iter) {
            double phi_x = phi(x);
            vector<double> g = gradient_central(phi, x);

            if (g.norm() < acc) { 
                break;
            }
            steps_taken++;

            matrix<double> H = hessian_central(phi, x);

            for (int i = 0; i < H.size1(); ++i) {
                H(i, i) += 1e-6; // Regularization
            }

            qr<double> qr_solver(H);
            vector<double> minus_g = -g;
            vector<double> dx = qr_solver.solve(minus_g);

            double lambda = 1.0;
            vector<double> z;

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