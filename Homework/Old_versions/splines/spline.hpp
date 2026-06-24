#include <vector>
#include <cassert>
#include <cmath>
#include <iostream>

//----- AI generated -----
class QuadSpline {
private:
    std::vector<double> x, y, b, c;
    int n;

    int binsearch(double z) const {
        assert(z >= x[0] && z <= x[n-1]);
        int i = 0, j = n - 1;
        while (j - i > 1) {
            int mid = (i + j) / 2;
            if (z > x[mid]) i = mid; else j = mid;
        }
        return i;
    }

public:
    QuadSpline(const std::vector<double>& x_points, const std::vector<double>& y_points) 
        : x(x_points), y(y_points) {
        n = x.size();
        b.resize(n - 1);
        c.resize(n - 1);

        std::vector<double> p(n - 1), h(n - 1);
        for (int i = 0; i < n - 1; i++) {
            h[i] = x[i + 1] - x[i];
            p[i] = (y[i + 1] - y[i]) / h[i];
        }
// ----- End AI generated -----

        // Forward recursion for c_i
        c[0] = 0; 
        for (int i = 0; i < n - 2; i++)
            c[i + 1] = (p[i + 1] - p[i] - c[i] * h[i]) / h[i + 1];

        // Backward recursion for c_i
        c[n - 2] /= 2.0;
        for (int i = n - 3; i >= 0; i--)
            c[i] = (p[i + 1] - p[i] - c[i + 1] * h[i + 1]) / h[i];

        // Calculate b_i
        for (int i = 0; i < n - 1; i++)
            b[i] = p[i] - c[i] * h[i];
    }

    double eval(double z) const {
        int i = binsearch(z);
        double dx = z - x[i];
        return y[i] + dx * (b[i] + dx * c[i]);
    }

    double derivative(double z) const {
        int i = binsearch(z);
        double dx = z - x[i];
        return b[i] + 2.0 * c[i] * dx;
    }

    double integral(double z) const {
        int idx = binsearch(z);
        double total = 0;
        // full intervals
        for (int i = 0; i < idx; i++) {
            double h = x[i + 1] - x[i];
            total += y[i] * h + b[i] * h * h / 2.0 + c[i] * h * h * h / 3.0;
        }
        // partial interval
        double dx = z - x[idx];
        total += y[idx] * dx + b[idx] * dx * dx / 2.0 + c[idx] * dx * dx * dx / 3.0;
        return total;

        
    }
    // for checking
    void print_coeffs(const std::string& label) const {
        std::cout << "\n--- " << label << " ---" << std::endl;
        std::cout << "i\txi\tyi\tbi\tci" << std::endl;
        for (int i = 0; i < n - 1; i++) {
            printf("%d\t%.1f\t%.1f\t%.2f\t%.2f\n", i, x[i], y[i], b[i], c[i]);
        }
    }
};