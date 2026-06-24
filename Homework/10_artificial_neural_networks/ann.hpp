
#pragma once

#include <vector>
#include <cmath>
#include <functional>
#include "matrix.hpp"
#include "minimization.hpp"

namespace pp {

    struct ann {
        int n; // number of hidden neurons
        std::function<double(double)> f; // activation function
        pp::vector<double> p; // network parameters

        // Constructor
        ann(int num_neurons, std::function<double(double)> activation_func) 
            : n(num_neurons), f(activation_func) {
            // all hidden neurons have 3 parameters: ai, bi, wi
            p = pp::vector<double>(3 * n);
        }

        // return the response of the network to the input signal
        // calculation
        double response(double x, const pp::vector<double>& current_p) const {
            double sum = 0.0;
            for (int i = 0; i < n; ++i) {
                double ai = current_p[3 * i + 0];
                double bi = current_p[3 * i + 1];
                double wi = current_p[3 * i + 2];
                
                if (std::abs(bi) < 1e-9) {bi = (bi >= 0) ? 1e-9 : -1e-9;}
                //if (std::abs(bi) < 0.20) { bi = (bi >= 0) ? 0.20 : -0.20; }

            

                sum += f((x - ai) / bi) * wi;
            }
            return sum;
        }


        double response(double x) const {
            return response(x, p);
        }

        // update for derivative
        double derivative(double x) const {
            double sum = 0.0;
            for (int i = 0; i < n; ++i) {
                double ai = p[3 * i + 0];
                double bi = p[3 * i + 1];
                double wi = p[3 * i + 2];
                
                // avoid division by zero
                if (std::abs(bi) < 1e-9) bi = (bi >= 0) ? 1e-9 : -1e-9;
                

               
                double u = (x - ai) / bi;
                // f'(u) = (1 - 2*u^2) * exp(-u^2)
                double df_du = (1.0 - 2.0 * u * u) * std::exp(-u * u);
                
                // d/dx [f((x-a)/b)] = (1/b) * f'(u)
                sum += (1.0 / bi) * df_du * wi;
            }
            return sum;
        }

        // second derivative
        double derivative2(double x) const {
            double sum = 0.0;
            for (int i = 0; i < n; ++i) {
                double ai = p[3 * i + 0];
                double bi = p[3 * i + 1];
                double wi = p[3 * i + 2];
                
                if (std::abs(bi) < 1e-9) bi = (bi >= 0) ? 1e-9 : -1e-9;

           

                double u = (x - ai) / bi;
                // f''(u) = 2*u * (2*u^2 - 3) * exp(-u^2)
                double d2f_du2 = 2.0 * u * (2.0 * u * u - 3.0) * std::exp(-u * u);
                
                // d^2/dx^2 [f((x-a)/b)] = (1/b^2) * f''(u)
                sum += (1.0 / (bi * bi)) * d2f_du2 * wi;
            }
            return sum;
        }

        // Anti-derivative
        double antiderivative(double x) const {
            double sum = 0.0;
            for (int i = 0; i < n; ++i) {
                double ai = p[3 * i + 0];
                double bi = p[3 * i + 1];
                double wi = p[3 * i + 2];
                
                if (std::abs(bi) < 1e-9) bi = (bi >= 0) ? 1e-9 : -1e-9;

                double u = (x - ai) / bi;
                // Int f(u)du = -0.5 * exp(-u^2)
                double int_f = -0.5 * std::exp(-u * u);
                
                // Int f((x-a)/b) dx = b * Int f(u) du
                sum += bi * int_f * wi;
            }
            return sum;
        }

        // const function 
        struct CostFunction {
            const ann& network;
            const pp::vector<double>& x_data;
            const pp::vector<double>& y_data;

            CostFunction(const ann& net, const pp::vector<double>& x, const pp::vector<double>& y)
                : network(net), x_data(x), y_data(y) {}

            
            double operator()(const pp::vector<double>& params) const {
                double sum_sq_errors = 0.0;
                for (int k = 0; k < x_data.size(); ++k) {
                    double error = network.response(x_data[k], params) - y_data[k];
                    sum_sq_errors += error * error;
                }
                return sum_sq_errors;
            }
        };

    // train the network to interpolate the given table {x,y}
    void train(const pp::vector<double>& x_data, const pp::vector<double>& y_data) {
        
        // initialize parameters destributed

        
        
        for (int i = 0; i < n; ++i) {
            p[3 * i + 0] = -1.0 + 2.0 * i / (n - 1);
            p[3 * i + 1] = 0.45;
            p[3 * i + 2] = 0.4;
        }


        // costfunc instance
        CostFunction cost_obj(*this, x_data, y_data);
        
        
        p = pp::minimize_newton(cost_obj, p, 1e-4);
        }
    };

}