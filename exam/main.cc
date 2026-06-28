#include "berrut.hpp"
#include "spline.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>


using namespace std;

double runge_function(double x) {
    return 1.0 / (1.0 + x * x);
}

//polynomial interpolation from PDF
double polinterp(const vector<double>& x, const vector<double>& y, double z) {
    int n = x.size();
    double s = 0;
    for (int i = 0; i < n; i++) {
        double p = 1;
        for (int k = 0; k < n; k++) {
            if (k != i) {
                p *= (z - x[k]) / (x[i] - x[k]);
            }
        }
        s += y[i] * p;
    }
    return s;
}



int main() {
    cout << "--- Part A) Testing Berrut B1 rational interpolation ---" << endl;
    cout << "Testing on cos(x)" << endl;
    
    double start = 0.0;
    double end = 9.0;
    double step = 0.5;
    int n = ((end - start) / step + 1e-9) + 1;

    vector<double> x_points(n), y_points(n);
    for (int i = 0; i < n; ++i) {
        double xi_val = start + i * step;
        x_points[i] = xi_val;
        y_points[i] = cos(xi_val);
    }

    // saving generated data point for plotting
    ofstream data_file("data_nodes.txt");
    for (size_t i = 0; i < x_points.size(); ++i) {
        data_file << x_points[i] << " " << y_points[i] << "\n";
    }
    data_file.close();

   
    BerrutB1 bb(x_points, y_points);

    // computing interpolation + derivative + integral and saving 
    ofstream res_berrut("res_berrut.txt");
    for (double x = start; x <= end + 1e-9; x += 0.05) {
        double val  = bb.eval(x);
        double der  = bb.derivative(x);
        double integ = bb.integral(x);
        
        //  x, berrut_y, derivative, integral
        res_berrut << x << " " << val << " " << der << " " << integ << "\n";
    }
    res_berrut.close();

    cout << "Interpolation data generated in 'res_berrut.txt'" << endl;

    // --- Part B) verification checks ---
    cout << "\n--- Part B) verification checks ---" << endl;
    
    // evaluating exactly at nodes yields exact yi values
    cout << "Checking exact node evaluations :" << endl;
    bool nodes_correct = true;
    for (int i = 0; i < n; ++i) {
        double val_at_node = bb.eval(x_points[i]);
        double discrepancy = abs(val_at_node - y_points[i]);
        if (discrepancy > 1e-12) {
            cout << "  Mismatch at node x = " << x_points[i] << "! Diff: " << discrepancy << endl;
            nodes_correct = false;
        }
    }
    if (nodes_correct) {
        cout << "  Passed. All exact node evaluations returned exact yi values." << endl;
    }

    // checking integration
    // for cos(x), integrating from 0 to 2*pi should close to  0
    double target_x = 2.0 * M_PI; 
    if (target_x <= end) {
        double computed_integral = bb.integral(target_x);
        double analytical_exact  = sin(target_x) - sin(start); 
        cout << "checking definite integration from x = 0 to 2*pi:" << endl;
        cout << "Gauss-Legendre integral over B1: " << computed_integral << endl;
        cout << "exact analytical integral : " << analytical_exact << endl;
        cout << "abs Error: " << abs(computed_integral - analytical_exact) << endl;
    }

    cout << "\n--- Part C) recreating Figure 1.3 (Runge Function) ---" << endl;

    // generate the 11 data points over [-5, 5] matching Figure 1.3
    double start_runge = -5.0;
    double end_runge = 5.0;
    int n_runge = 10; 
    double step_runge = (end_runge - start_runge) / (n_runge - 1);
    

    vector<double> x_points_r(n_runge), y_points_r(n_runge);
    for (int i = 0; i < n_runge; ++i) {
        double x_val_r = start_runge + i * step_runge;
        x_points_r[i] = x_val_r;
        y_points_r[i] = runge_function(x_val_r);
    }

    // save data points
    ofstream data_file_r("runge_nodes.txt");
    for (size_t i = 0; i < x_points_r.size(); ++i) {
        data_file_r << x_points_r[i] << " " << y_points_r[i] << "\n";
    }
    data_file_r.close();

    // initialize our interpolations
    BerrutB1 bb_runge(x_points_r, y_points_r);
    QuadSpline qs(x_points_r, y_points_r);

    // 3. Generate a fine grid path to capture the edge oscillations cleanly
    ofstream res_file("runge_comparison.txt");
    for (double x = start_runge; x <= end_runge + 1e-9; x += 0.02) {
        double exact   = runge_function(x);
        double poly    = polinterp(x_points_r, y_points_r, x);
        double berrut  = bb_runge.eval(x);
        double spline  = qs.eval(x);
        
        // Output format: x | Exact |  Poly | Berrut B1 | Quad Spline 
        res_file << x << " " << exact << " " << poly << " " << berrut << " " << spline << "\n";
    }
    res_file.close();

    cout << "Data saved to 'runge_nodes.txt' and 'runge_comparison.txt'." << endl;

    cout << "Result plotted in runge_comparison." << endl;
   

    return 0;
}