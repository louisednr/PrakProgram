
#include <iostream>
#include <iomanip>
#include <cmath>
#include <functional>
#include <limits>
#include <utility> // For std::pair


int ncalls = 0;


std::pair<double, double> integrate(std::function<double(double)> f, double a, double b, 
                 double acc = 0.001, double eps = 0.001, 
                 double f2 = std::numeric_limits<double>::quiet_NaN(), 
                 double f3 = std::numeric_limits<double>::quiet_NaN()) {
    
    double h = b - a;
    
    // If the interval is smaller than machine precision, stop subdividing
    if (std::abs(h) < 1e-15) {
        return {0.0, 0.0}; 
    }
    
    if (std::isnan(f2)) { // first call, no points to reuse
        f2 = f(a + 2.0 * h / 6.0); ncalls++;
        f3 = f(a + 4.0 * h / 6.0); ncalls++;
    }
    
    double f1 = f(a + h / 6.0);       ncalls++;
    double f4 = f(a + 5.0 * h / 6.0); ncalls++;
    
    // higher order rule
    double Q = (2.0 * f1 + f2 + f3 + 2.0 * f4) / 6.0 * h;
    // lower order rule
    double q = (f1 + f2 + f3 + f4) / 4.0 * h;
    
    double err = std::abs(Q - q);
    double tol = acc + eps * std::abs(Q);
    
    //returning both result and estimated error
    if (err < tol) {
        return {Q, err};
    } else {
        auto left  = integrate(f, a, (a + b) / 2.0, acc / std::sqrt(2.0), eps, f1, f2);
        auto right = integrate(f, (a + b) / 2.0, b, acc / std::sqrt(2.0), eps, f3, f4);
        
        double total_Q = left.first + right.first;
        double total_err = std::sqrt(left.second * left.second + right.second * right.second);
        
        return {total_Q, total_err};
    }
}


double f(double x) {
    ncalls++;
    if (x <= 0) return 0; // prevents undefined log(0)
    return std::log(x) / std::sqrt(x);
}


double erf(double z, double acc = 0.001, double eps = 0.001) {
    // if z < 0
    if (z < 0) {
        return -erf(-z, acc, eps);
    }
    // if 0 ≤ z ≤ 1
    if (z >= 0 && z <= 1) {
        auto f_inner = [](double x) { return std::exp(-x * x); };
        return (2.0 / std::sqrt(M_PI)) * integrate(f_inner, 0.0, z, acc, eps).first;
    } 
    // 1 < z
    auto f_inner = [z](double t) {
        //if (t <= 0.0) return 0.0; // Avoid division by zero at the boundary
        double inner = z + (1.0 - t) / t;
        return std::exp(-inner * inner) / (t * t);
    };
    return 1.0 - (2.0 / std::sqrt(M_PI)) * integrate(f_inner, 0.0, 1.0, acc, eps).first;
}


// for exercise B:

// Clenshaw–Curtis variable 
double clenshaw_curtis(std::function<double(double)> f, double a, double b, double acc = 0.001, double eps = 0.001) {
    auto f_transformed = [f, a, b](double theta) {
        double x = (a + b) / 2.0 + (b - a) / 2.0 * std::cos(theta);
        double jacobian = std::sin(theta) * (b - a) / 2.0;
        return f(x) * jacobian;
    };
    return integrate(f_transformed, 0.0, M_PI, acc, eps).first;
}

// Infinite limits (table four from pdf)
double integrate_infinite(std::function<double(double)> f, double a, double b, double acc = 0.001, double eps = 0.001) {
    bool a_inf = std::isinf(a);
    bool b_inf = std::isinf(b);

    // (-inf, inf) ->  (-1, 1), using x = t / (1 - t^2)
    if (a_inf && b_inf) {
        auto f_inf_inf = [f](double t) {
            double t2 = t * t;
            double x = t / (1.0 - t2);
            double jacobian = (1.0 + t2) / ((1.0 - t2) * (1.0 - t2));
            return f(x) * jacobian;
        };
        return clenshaw_curtis(f_inf_inf, -1.0, 1.0, acc, eps);
    }
    
    // [a, inf) -> [0, 1], using x = a + t / (1 - t)
    if (!a_inf && b_inf) {
        auto f_a_inf = [f, a](double t) {
            if (t >= 1.0) return 0.0;
            double x = a + t / (1.0 - t);
            double jacobian = 1.0 / ((1.0 - t) * (1.0 - t));
            return f(x) * jacobian;
        };
        return clenshaw_curtis(f_a_inf, 0.0, 1.0, acc, eps);
    }

    // (-inf, b] -> [0, 1], using x = b - (1 - t) / t
    if (a_inf && !b_inf) {
        auto f_inf_b = [f, b](double t) {
            if (t <= 0.0) return 0.0;
            double x = b - (1.0 - t) / t;
            double jacobian = 1.0 / (t * t);
            return f(x) * jacobian;
        };
        return clenshaw_curtis(f_inf_b, 0.0, 1.0, acc, eps);
    }

    // Default: both limits are finite
    return clenshaw_curtis(f, a, b, acc, eps);
}


int main() {
    std::cout << std::scientific << std::setprecision(12);
    
    std::cout << "------------------------\n";
    std::cout << "--- A ---\n";
    std::cout << "------------------------\n";
    // Test 1
    std::cout << "--- Part 1: Testing integrals ---\n";

    // sqrt(x)
    ncalls = 0;
    // ---------- AI generated ----------
    double q1 = integrate([](double x){ return std::sqrt(x); }, 0.0, 1.0).first;
    std::cout << "1) sqrt(x)         | Calc: " << q1 << " | Exact: 0.66666666667 | Calls: " << ncalls << "\n";

    // Integral 2: 1/sqrt(x)
    ncalls = 0;
    // Handled singularity lightly at 0 by using a small offset or relies on open-quadrature
    double q2 = integrate([](double x){ return (x <= 0.0) ? 0.0 : 1.0 / std::sqrt(x); }, 0.0, 1.0).first;
    std::cout << "2) 1/sqrt(x)       | Calc: " << q2 << " | Exact: 2.000000000000 | Calls: " << ncalls << "\n";

    // Integral 3: sqrt(1 - x^2)
    ncalls = 0;
    double q3 = integrate([](double x){ return std::sqrt(1.0 - x * x); }, 0.0, 1.0).first;
    std::cout << "3) sqrt(1-x^2)     | Calc: " << q3 << " | Exact: " << M_PI / 2.0 << " | Calls: " << ncalls << "\n";

    // Integral 4: ln(x)/sqrt(x)
    ncalls = 0;
    double q4 = integrate([](double x){ return (x <= 0.0) ? 0.0 : std::log(x) / std::sqrt(x); }, 0.0, 1.0).first;
    std::cout << "4) ln(x)/sqrt(x)   | Calc: " << q4 << " | Exact: -4.00000000000 | Calls: " << ncalls << "\n\n";
    // ---------- end AI generet ----------


    // test 2 
    std::cout << "--- Part 2: Error Function ---\n";


    double exact_erf1 = 0.84270079294971486934;
    double calc_erf1 = erf(1.0, 1e-7, 1e-7);
    std::cout << "erf(1) (acc=1e-7): " << calc_erf1 << "\n";
    std::cout << "Exact erf(1)     : " << exact_erf1 << "\n\n";

    // data for plot
    std::cout << "--- Part 3: Data for plot ---\n";
    std::cout << "# acc \t\t actual_error\n";
    
    double acc_target = 0.1;
    for (int i = 0; i < 8; ++i) {
        double res = erf(1.0, acc_target, 0.0);
        double actual_error = std::abs(res - exact_erf1);
        std::cout << acc_target << "\t" << actual_error << "\n";
        acc_target /= 10.0;
    }

    std::cout << "------------------------"  << "\n";
    std::cout << "--- B ---\n";
    std::cout << "------------------------"  << "\n";

    std::cout << "--- Part 1: open quandrature adaptive integrator with the Clenshaw–Curtis variable transformation ---\n";
    
    // --- 1/sqrt(x) from 0 to 1 ---
    auto f1 = [](double x) { return (x <= 0.0) ? 0.0 : 1.0 / std::sqrt(x); };
    
    ncalls = 0;
    double res1_ord = integrate(f1, 0.0, 1.0, 1e-6, 1e-6).first;
    int calls1_ord = ncalls;

    ncalls = 0;
    double res1_cc = clenshaw_curtis(f1, 0.0, 1.0, 1e-6, 1e-6);
    int calls1_cc = ncalls;

    std::cout << "Integral 1:  1/sqrt(x) | Exact: 2.0\n";
    std::cout << "   Ordinary:   " << res1_ord << " | # Evaluations: " << calls1_ord << "\n";
    std::cout << "   C-Curtis:   " << res1_cc  << " | # Evaluations: " << calls1_cc  << "\n\n";


    // --- ln(x)/sqrt(x) from 0 to 1 ---
    auto f2 = [](double x) { return (x <= 0.0) ? 0.0 : std::log(x) / std::sqrt(x); };
    
    ncalls = 0;
    double res2_ord = integrate(f2, 0.0, 1.0, 1e-6, 1e-6).first;
    int calls2_ord = ncalls;

    ncalls = 0;
    double res2_cc = clenshaw_curtis(f2, 0.0, 1.0, 1e-6, 1e-6);
    int calls2_cc = ncalls;

    std::cout << "Integral 2 ln(x)/sqrt(x) | Exact: -4.0\n";
    std::cout << "   Ordinary:   " << res2_ord << " | # Evaluations: " << calls2_ord << "\n";
    std::cout << "   C-Curtis:   " << res2_cc  << " | # Evaluations: " << calls2_cc  << "\n\n";

    std::cout << "--- Part 2: Test on some (converging) infitine limit integrals ---\n";


    // --- exp(-x^2) from -inf to inf ---
    auto f_1 = [](double x) { return std::exp(-x * x); };
    
    ncalls = 0;
    double inf_limit = std::numeric_limits<double>::infinity();
    double res_inf = integrate_infinite(f_1, -inf_limit, inf_limit, 1e-6, 1e-6);
    
    std::cout << " exp(-x^2) from -inf to inf | Exact: " << std::sqrt(M_PI) << "\n";
    std::cout << "   Calculated: " << res_inf << " | Evaluations: " << ncalls << "\n\n";

    // Test Code:
    // --- x^2 * exp(-x) from 0 to inf ---
    auto f_2 = [](double x) { return (x == 0.0) ? 1.0 : x * x * std::exp(-x); };

    ncalls = 0;
    double res_inf_2 = integrate_infinite(f_2, 0.0, inf_limit, 1e-6, 1e-6);

    std::cout << "x^2 * exp(-x) from 0 to inf | Exact: 2.0\n";
    std::cout << "   Calculated: " << res_inf_2 << " | Evaluations: " << ncalls << "\n\n";

    std::cout << "------------------------\n";
    std::cout << "--- C ---\n";
    std::cout << "------------------------\n";

    // --- Exercise C verification printing ---
    std::cout << "------------------------\n";
    std::cout << "--- C ---\n";
    std::cout << "------------------------\n";
    std::cout << "Investigating Error Estimate Quality (Integral of 1/sqrt(x) from 0 to 1)\n";
    std::cout << "Target_Acc\tEstimated_Err\tActual_Err\tRatio(Est/Act)\n";

    std::cout << std::scientific << std::setprecision(3);

    // AI genrated testing below

    // ========================================================
    // Integral 1: 1/sqrt(x) from 0 to 1 [Exact = 2.0]
    // ========================================================
    std::cout << "=== Test 1: integral of 1/sqrt(x) from 0 to 1 ===\n";
    std::cout << "Target_Acc\tEstimated_Err\tActual_Err\tRatio(Est/Act)\n";
    
    auto f_c1 = [](double x) { return (x <= 0.0) ? 0.0 : 1.0 / std::sqrt(x); };
    double acc1 = 1e-2;
    for (int i = 0; i < 5; ++i) {
        auto out = integrate(f_c1, 0.0, 1.0, acc1, 0.0);
        double actual_err = std::abs(out.first - 2.0);
        std::cout << acc1 << "\t" << out.second << "\t" << actual_err 
                  << "\t" << (actual_err > 0 ? out.second / actual_err : 1.0) << "\n";
        acc1 /= 10.0;
    }
    std::cout << "\n";

    // ========================================================
    // Integral 2: ln(x)/sqrt(x) from 0 to 1 [Exact = -4.0]
    // ========================================================
    std::cout << "=== Test 2: integral of ln(x)/sqrt(x) from 0 to 1 ===\n";
    std::cout << "Target_Acc\tEstimated_Err\tActual_Err\tRatio(Est/Act)\n";
    
    auto f_c2 = [](double x) { return (x <= 0.0) ? 0.0 : std::log(x) / std::sqrt(x); };
    double acc2 = 1e-2;
    for (int i = 0; i < 5; ++i) {
        auto out = integrate(f_c2, 0.0, 1.0, acc2, 0.0);
        double actual_err = std::abs(out.first - (-4.0));
        std::cout << acc2 << "\t" << out.second << "\t" << actual_err 
                  << "\t" << (actual_err > 0 ? out.second / actual_err : 1.0) << "\n";
        acc2 /= 10.0;
    }
    std::cout << "\n";

    // ========================================================
    // Integral 3: sin(1/x) from 0.1 to 1.0 [Exact ≈ 0.380064379165]
    // ========================================================
    std::cout << "=== Test 3: integral of sin(1/x) from 0.1 to 1.0 ===\n";
    std::cout << "Target_Acc\tEstimated_Err\tActual_Err\tRatio(Est/Act)\n";
    
    auto f_c3 = [](double x) { return std::sin(1.0 / x); };
    double acc3 = 1e-2;
    for (int i = 0; i < 5; ++i) {
        auto out = integrate(f_c3, 0.1, 1.0, acc3, 0.0);
        double actual_err = std::abs(out.first - 0.380064379165);
        std::cout << acc3 << "\t" << out.second << "\t" << actual_err 
                  << "\t" << (actual_err > 0 ? out.second / actual_err : 1.0) << "\n";
        acc3 /= 10.0;
    }
    std::cout << "\n";



    return 0;
}



