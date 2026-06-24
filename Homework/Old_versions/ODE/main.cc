#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include "ODE.hpp"

using Vector = pp::vector<double>;

// helper for part B, saves to file + runs driver
void run_orbit(double epsilon, Vector yinit, double phi_max, std::string filename, double h_max = 100.0) {
    auto func = [epsilon](double phi, const Vector& y) -> Vector {
        // y[0] = u, y[1] = u'
        return { y[1], 1.0 - y[0] + epsilon * y[0] * y[0] };
    };

    auto [philist, ulist] = driver(func, 0, phi_max, yinit, 0.05, 1e-6, 1e-6, h_max);

    std::ofstream orbit_file(filename);
    for (size_t i = 0; i < philist.size(); ++i) {
        orbit_file << philist[i] << " " << ulist[i][0] << "\n";
    }
    orbit_file.close();
}

int main() {


    // define the debug system: u'' = -u
    auto f = [](double x, const Vector& y) -> Vector {
        return {y[1], -y[0]}; 
    };

    std::cout << "Testing u'' = - u" << "\n";


    std::cout << " With starting condition: u(0)=0 and u'(0)=1" << "\n";

    std::cout << "This has solution u(x)= sin(x)" << "\n";


    Vector yinit = {0.0, 1.0};
    
    // calling driver
    auto [xlist, ylist] = driver(f, 0, 5, yinit);

    std::cout << std::setw(10) << "x" 
          << std::setw(15) << "u (num)" 
          << std::setw(15) << "u (exact)" 
          << std::setw(15) << "error" << "\n";
          
    for (size_t i = 0; i < xlist.size(); ++i) {
        double x = xlist[i];
        double u_calc = ylist[i][0];   // y[0] is u
        double u_exact = std::sin(x); // exact solution
        
        std::cout << std::fixed << std::setprecision(4)
                << std::setw(10) << x 
                << std::setw(15) << u_calc 
                << std::setw(15) << u_exact 
                << std::setw(15) << std::abs(u_calc - u_exact) << "\n";
    }

    std::cout << "Testing with Lotka-Volterra equations " << "\n";

    // parameter from solve_ivp
    double a = 1.5, b = 1.0, c = 3.0, d = 1.0;

    // Lotka-Volterra system
    auto f1 = [&](double t, const Vector& z) -> Vector {
        double x = z[0];
        double y = z[1];
        return {
            a * x - b * x * y,      // dx/dt
            -c * y + d * x * y      // dy/dt
        };
    };

    // Initial conditions
    Vector zinit = {10.0, 5.0};
    auto [tlist, zlist] = driver(f1, 0, 15, zinit);

    // save results to file
    std::ofstream data_file("lv_solve_data.txt");
    for (size_t i = 0; i < tlist.size(); ++i) {
        data_file << tlist[i] << " " << zlist[i][0] << " " << zlist[i][1] << "\n";
    }
    data_file.close();

    std::cout << "See recreated plot in lv_plot.svg " << "\n";

    std::cout << "Part B: Relativistic precession of planetary orbit " << "\n";
    
    double rotations = 6.0; // run for 6 rotations
    double phi_end = rotations * 2.0 * M_PI;

    //  1: (eps=0, u=1, u'=0)
    run_orbit(0.0, {1.0, 0.0}, phi_end, "orbit_circ.txt", 0.1); 
    //above needs a h_max argument becuase otherwise jumps to the end too soon

    // 2: (eps=0, u=1, u'=-0.5)
    run_orbit(0.0, {1.0, -0.5}, phi_end, "orbit_ell.txt");

    // 3: (eps=0.01, u=1, u'=-0.5)
    run_orbit(0.01, {1.0, -0.5}, phi_end, "orbit_prec.txt");


    return 0;
}
