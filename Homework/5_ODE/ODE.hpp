#include "matrix.hpp"
#include <functional>
#include <tuple>
#include <cmath>
#include <algorithm>



// so I dont have to write this many times
using Vector = pp::vector<double>;

// from homework text
inline std::tuple<Vector, Vector> rkstep12(
    const std::function<Vector(double, Vector)>& f,
    double x, Vector y, double h) 
{
    Vector k0 = f(x, y);
    Vector k1 = f(x + h/2.0, y + k0 * (h/2.0));
    Vector yh = y + k1 * h;      
    Vector dy = (k1 - k0) * h;   
    return {yh, dy};
}


// --- adaptive driver ---
// adapted from homework text
inline std::tuple<std::vector<double>, std::vector<Vector>> driver(
    std::function<Vector(double, Vector)> f,
    double a, double b, Vector yinit,
    double h = 0.125, double acc = 0.01, double eps = 0.01, double h_max = 100.0) 
{
    double x = a;
    Vector y = yinit;
    std::vector<double> xlist = {x};
    std::vector<Vector> ylist = {y};

    while (x < b) {
        if (x + h > b) h = b - x;

        auto [yh, dy] = rkstep12(f, x, y, h);
        
        // error scaling
        double tolerance = (acc + eps * yh.norm()) * std::sqrt(h / (b - a));
        double error = dy.norm();

        if (error <= tolerance) {
            x += h;
            y = yh;
            xlist.push_back(x);
            ylist.push_back(y);
        }

        // Step size adjustment
        if (error > 0) {
            h *= std::min(std::pow(tolerance / error, 0.25) * 0.95, 2.0);
        } else {
            h *= 2.0;
        }
        if (h > h_max) h = h_max;
    }
    return {xlist, ylist};
}