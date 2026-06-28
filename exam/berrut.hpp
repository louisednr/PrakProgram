#pragma once
#include <vector>
#include <cassert>
#include <cmath>
#include <limits>

struct BerrutB1 {
    std::vector<double> xi, yi;
    int n_points;
    double epsilon;

    // constructor
    BerrutB1(const std::vector<double>& xi_points, const std::vector<double>& yi_points)
        : xi(xi_points), yi(yi_points) {
        assert(xi.size() == yi.size());
        assert(xi.size() > 1);
        n_points = xi.size();
        epsilon = std::numeric_limits<double>::epsilon();
    }

    // evaluates B1(x) using eq (1.41)
    double eval(double x) const {
    
        double num = 0.0;
        double den = 0.0;

        for (int i = 0; i < n_points; ++i) {
            double w = (i % 2 == 0) ? 1.0 : -1.0; // Alternates (-1)^i [cite: 291]
            double diff = x - xi[i];
            double term = w / diff;
            
            num += term * yi[i];
            den += term;
        }

        return num / den;
    }

    // analyitical first derivative B1'(x)
    double derivative(double x) const {
        
        double current_val = eval(x);
        double num = 0.0;
        double den = 0.0;

        for (int i = 0; i < n_points; ++i) {
            double w = (i % 2 == 0) ? 1.0 : -1.0;
            double diff = x - xi[i];
            
            num += (w / (diff * diff)) * (yi[i] - current_val);
            den += w / diff;
        }

        return num / den;
    }

    //integrates B1(x) from the first node xi[0] up to x_val
    //Using numerical 5-point Gauss-Legendre quadrature, described in chapter 7
    double integral(double x_val) const {
        assert(x_val >= xi[0] && x_val <= xi[n_points - 1]);
        
        // 5-point Gauss-Legendre quadrature weights and nodes mapped on [-1, 1] from https://dlmf.nist.gov/3.5
        const std::vector<double> nodes = {
            -0.906179845938664, -0.538469310105683, 0.0, 
             0.538469310105683,  0.906179845938664
        };
        const std::vector<double> weights = {
            0.236926885056189, 0.478628670598376, 0.568888888888889, 
            0.478628670598376, 0.236926885056189
        };

        // Linear transformation from [-1, 1] to interval [xi[0], x_val]
        double a = xi[0];
        double b = x_val;
        double mid = 0.5 * (a + b);
        double half_width = 0.5 * (b - a);

        double total_sum = 0.0;
        for (size_t i = 0; i < nodes.size(); ++i) {
            double target_x = mid + half_width * nodes[i];
            total_sum += weights[i] * eval(target_x);
        }

        return total_sum * half_width;
    }
};