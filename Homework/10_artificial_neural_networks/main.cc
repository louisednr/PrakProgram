#include "matrix.hpp"
#include "ann.hpp"

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>


// --- for tests ---
double target_function(double x) {
    return std::cos(5.0 * x - 1.0) * std::exp(-x * x);
}

// gaussian wavelet activation function
double gaussian_wavelet(double x) {
    return x * std::exp(-x * x);
}

int main() {
    // training data (N sampled points on [-1, 1])
    int N = 20; 
    pp::vector<double> x_train(N);
    pp::vector<double> y_train(N);

    std::cout << "--- Part A ---- \n\n";

    std::cout << "Generating " << N << " training points on [-1, 1]...\n";
    for (int i = 0; i < N; ++i) {
        // points between -1 and 1
        double x = -1.0 + 2.0 * i / (N - 1);
        x_train[i] = x;
        y_train[i] = target_function(x);
    }

    // initiate the ann
    int hidden_neurons = 10;
    pp::ann network(hidden_neurons, gaussian_wavelet);

    // trainning 
    std::cout << "Training the network (Newton minimization) ...\n";
    network.train(x_train, y_train);
    std::cout << "Training done\n\n";

    // testing
    std::ofstream out("data.txt");

    // Write a clean header comment for tracking columns
    out << "  x    |   target g(x)  |   ann Fp(x)  |   abs error \n";

    int test_points = 100;
    for (int i = 0; i < test_points; ++i) {
        double x = -1.0 + 2.0 * i / (test_points - 1);
        double target_y = target_function(x);
        double network_y = network.response(x);
        double error = std::abs(network_y - target_y);

        out << std::setw(12) << std::fixed << std::setprecision(6) << x
            << std::setw(18) << target_y
            << std::setw(18) << network_y
            << std::setw(18) << error << "\n";
    }
    out.close();
    std::cerr << " data saved to 'data.txt'.\n";


    std::cout << "--- Part B ---- \n\n";

    int test_points_b = 100;
    std::ofstream out_b("derivatives_data.txt");
    out_b << "# x | Fp(x) | Fp'(x) | Fp''(x) | Fp_int(x) | g'(x)_true | g''(x)_true\n";

    for (int i = 0; i < test_points_b; ++i) {
        double x = -1.0 + 2.0 * i / (test_points_b - 1);
        

        double exp_term = std::exp(-x * x);
        double cos_term = std::cos(5.0 * x - 1.0);
        double sin_term = std::sin(5.0 * x - 1.0);

        double true_g_prime = -5.0 * sin_term * exp_term - 2.0 * x * cos_term * exp_term;
        double true_g_double_prime = (-25.0 + 4.0 * x * x - 2.0) * cos_term * exp_term + 20.0 * x * sin_term * exp_term;

        out_b << std::setw(12) << std::fixed << std::setprecision(6) << x << " "
              << std::setw(14) << network.response(x) << " "
              << std::setw(14) << network.derivative(x) << " "
              << std::setw(14) << network.derivative2(x) << " "
              << std::setw(14) << network.antiderivative(x) << " "
              << std::setw(14) << true_g_prime << " "
              << std::setw(14) << true_g_double_prime << "\n";
    }
    out_b.close();
    std::cerr << " derivatives data saved to 'derivatives_data.txt'.\n";

    return 0;
}