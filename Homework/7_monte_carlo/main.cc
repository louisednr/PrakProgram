#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>
#include <cmath>
#include <functional>
#include <utility> // for std::pair
#include <random>

//lcg struct *AI generated*
struct LCG {
    unsigned long long seed;
    unsigned long long a = 1664525;
    unsigned long long c = 1013904223;
    unsigned long long m = pow(2.0, 32.0);; // 2^32


    double operator()() {
        seed = (a * seed + c) % m;
        return static_cast<double>(seed + 1) / static_cast<double>(m + 1);
    }
};



/// From exercise description: 
//import math
// def plainmc(f,a,b,N,random_double):
//     dim = len(a)
//     V = 1
//     for i in range(dim): V *= b[i] - a[i]
//     sum1 = sum2 = 0.0
//     for _ in range(N):
//         x = [a[i] + random_double() * (b[i] - a[i]) for i in range(dim)]
//         fx = f(x); sum1 += fx; sum2 += fx * fx
//     mean = sum1 / N
//     sigma = math.sqrt(sum2 / N - mean * mean)
//     return (mean * V, sigma * V / math.sqrt(N))


template <typename RandomFunc>
std::pair<double, double> plainmc(
    std::function<double(const std::vector<double>&)> f,
    const std::vector<double>& a,
    const std::vector<double>& b,
    int N,
    RandomFunc random_double
) {
    size_t dim = a.size();
    double V = 1.0;
    
   
    for (size_t i = 0; i < dim; ++i) {
        V *= (b[i] - a[i]);
    }
    
    double sum1 = 0.0;
    double sum2 = 0.0;
    std::vector<double> x(dim); // Pre-allocating vector
    
    for (int j = 0; j < N; ++j) {
        for (size_t i = 0; i < dim; ++i) {
            x[i] = a[i] + random_double() * (b[i] - a[i]);
        }
        
        double fx = f(x);
        sum1 += fx;
        sum2 += fx * fx;
    }
    
    double mean = sum1 / N;
    double sigma = std::sqrt(sum2 / N - mean * mean);
    
    // return a std::pair
    return {mean * V, (sigma * V) / std::sqrt(N)};
}


// Generates prime numbers from p. 6 in PDF
    std::vector<int> prime_numbers(int n) {
        std::vector<int> primes;
        int candidate = 2;
        while (primes.size() < static_cast<size_t>(n)) {
            bool is_prime = true;
            for (int p : primes) {
                if (p * p > candidate) break;
                if (candidate % p == 0) { is_prime = false; break; }
            }
            if (is_prime) primes.push_back(candidate);
            candidate++;
        }
        return primes;
    }

    // sequence 1: Halton via corput function
    double corput(int n, int b) {
        double q = 0.0;
        double bk = 1.0 / b;
        while (n > 0) {
            q += (n % b) * bk;
            n /= b;
            bk /= b;
        }
        return q;
    }

    // sequence Halton 
    struct HaltonGenerator {
        std::vector<int> bases;
        int current_n = 1;
        size_t current_dim = 0;

        HaltonGenerator(int dim) : bases(prime_numbers(dim)) {}

        double operator()() {
            double val = corput(current_n, bases[current_dim]);
            current_dim++;
            if (current_dim >= bases.size()) {
                current_dim = 0;
                current_n++; 
            }
            return val;
        }
    };

    // sequence lattice 
    struct LatticeGenerator {
        std::vector<double> alphas;
        int current_n = 1;
        size_t current_dim = 0;

        LatticeGenerator(int dim) {
            std::vector<int> primes = prime_numbers(dim);
            for (int p : primes) {
                double root = std::sqrt(p);
                alphas.push_back(root - std::floor(root));
            }
        }

        double operator()() {
            double val = current_n * alphas[current_dim];
            val = val - std::floor(val);
            current_dim++;
            if (current_dim >= alphas.size()) {
                current_dim = 0;
                current_n++; 
            }
            return val;
        }
    };



int main() {
    LCG rng{166452}; // Initialise with seed

    std::cout << "------------------------\n";
    std::cout << "--- A ---\n";
    std::cout << "------------------------\n";
    
    // Test 1
    std::cout << "--- Part 1: Unit Circle Area ---\n";
    

    
    auto inside_circle = [](const std::vector<double>& pt) {
        return (pt[0] * pt[0] + pt[1] * pt[1] <= 1.0) ? 1.0 : 0.0;
    };

    std::vector<double> circle_min = {-1.0, -1.0};
    std::vector<double> circle_max = {1.0, 1.0};
    double actual_circle_area = M_PI;

    std::ofstream data_file("circle_errors.txt");
    data_file << "N\tEstimated_Error\tActual_Error\tOne_Over_SqrtN\n";

    std::cout << std::setw(8) << "N" 
              << std::setw(15) << "Estimate" 
              << std::setw(15) << "Est_Error" 
              << std::setw(15) << "Act_Error" << "\n";

    for (int N = 100; N <= 50000; N += 500) {
        auto [estimate, est_error] = plainmc(inside_circle, circle_min, circle_max, N, std::ref(rng));
        double actual_error = std::abs(estimate - actual_circle_area);
        
        data_file << N << "\t" << est_error << "\t" << actual_error << "\t" << (1.0 / std::sqrt(N)) << "\n";

        if (N == 100 || N == 10100 || N == 25100 || N == 49600) {
            std::cout << std::setw(8) << N 
                      << std::setw(15) << estimate 
                      << std::setw(15) << est_error 
                      << std::setw(15) << actual_error << "\n";
        }
    }
    data_file.close();

    // task 2
    std::cout << "--- Part 2:  three-dimensional ellipsoid volume ---\n";
    
    double a = 1.0, b = 2.0, c = 3.0;
    
    auto inside_ellipsoid = [a, b, c](const std::vector<double>& pt) {
        double val = (pt[0]*pt[0])/(a*a) + (pt[1]*pt[1])/(b*b) + (pt[2]*pt[2])/(c*c);
        return (val <= 1.0) ? 1.0 : 0.0;
    };

    std::vector<double> ell_min = {-a, -b, -c};
    std::vector<double> ell_max = {a, b, c};
    int N_ellipsoid = 200000;

    auto [ell_volume_est, ell_error] = plainmc(inside_ellipsoid, ell_min, ell_max, N_ellipsoid, std::ref(rng));
    double actual_ell_volume = (4.0 / 3.0) * M_PI * a * b * c;

    std::cout << "Samples (N):      " << N_ellipsoid << "\n";
    std::cout << "Estimated Volume: " << ell_volume_est << " +/- " << ell_error << "\n";
    std::cout << "Actual Volume:    " << actual_ell_volume << "\n";
    std::cout << "Discrepancy:      " << std::abs(ell_volume_est - actual_ell_volume) << "\n";


    std::cout << "------------------------\n";
    std::cout << "--- B ---\n";
    std::cout << "------------------------\n";

    std::cout << "--- Part 1:  Monte-Carlo integrator using quasi-random sequences ---\n";

    auto test_func = [](const std::vector<double>& pt) { return pt[0] * pt[1]; };
    std::vector<double> lower_bounds = {0.0, 0.0};
    std::vector<double> upper_bounds = {1.0, 1.0};
    double true_value = 0.25;

    std::ofstream scaling_file("scaling_data.txt");
    scaling_file << "N\tPseudo_Error\tQuasi_Error\n";

    for (int N = 100; N <= 10000; N += 100) {
        // reset generator instances for each unique N iteration test
        LCG lcg_rng{166452}; 
        HaltonGenerator halton_rng(2);
        LatticeGenerator lattice_rng(2);

        
        auto [p_est, p_err] = plainmc(test_func, lower_bounds, upper_bounds, N, std::ref(lcg_rng));
        auto [h_est, h_err] = plainmc(test_func, lower_bounds, upper_bounds, N, std::ref(halton_rng));
        auto [l_est, l_err] = plainmc(test_func, lower_bounds, upper_bounds, N, std::ref(lattice_rng));

        // error estimation for quasi-random using two different sequences absolute difference
        double quasi_error_estimate = std::abs(h_est - l_est);
        double pseudo_actual_error = std::abs(p_est - true_value);

        scaling_file << N << "\t" << pseudo_actual_error << "\t" << quasi_error_estimate << "\n";
    }
    scaling_file.close();

    std::cout << "Compared the scaling of the error with pseudo-random Monte-Carlo integrator \n";
    std::cout << "See plot quasi_plot.svg \n";


    std::cout << "--- Part 2: Singular 3D Integral Comparison ---\n";

    // define integrand
    auto singular_integrand = [](const std::vector<double>& pt) {
        double denom = 1.0 - std::cos(pt[0]) * std::cos(pt[1]) * std::cos(pt[2]);
        return 1.0 / (M_PI * M_PI * M_PI * denom);
    };

    //integration limits: 0 to pi for all 3 dimensions
    std::vector<double> sing_min = {0.0, 0.0, 0.0};
    std::vector<double> sing_max = {M_PI, M_PI, M_PI};
    int N_sing = 500000; 
    double target_exact = 1.3932039296856768591842462603255;

    // i) Simple LCG 
    LCG lcg_sing{166452};
    auto [res_lcg, err_lcg] = plainmc(singular_integrand, sing_min, sing_max, N_sing, std::ref(lcg_sing));

    // ii) Generator from the standard C++ library (mt19937)
    std::mt19937 standard_engine(12345);
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    auto rand_standard = [&]() { return dist(standard_engine); };
    auto [res_std, err_std] = plainmc(singular_integrand, sing_min, sing_max, N_sing, rand_standard);

    // iii) Quasi-random sequence (using 3D Halton generator)
    HaltonGenerator halton_sing(3);
    auto [res_quasi, err_quasi] = plainmc(singular_integrand, sing_min, sing_max, N_sing, std::ref(halton_sing));

    //comparison
    std::cout << std::fixed << std::setprecision(12);
    std::cout << "Target exact value      : " << target_exact << "\n";
    std::cout << "i)   Simple LCG         : " << res_lcg   << " (Diff: " << std::abs(res_lcg - target_exact) << ")\n";
    std::cout << "ii)  Standard library   : " << res_std   << " (Diff: " << std::abs(res_std - target_exact) << ")\n";
    std::cout << "iii) Quasi-sequence     : " << res_quasi << " (Diff: " << std::abs(res_quasi - target_exact) << ")\n";



    return 0;
}