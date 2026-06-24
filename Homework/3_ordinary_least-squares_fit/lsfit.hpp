#include "matrix.hpp"
#include "qr.hpp"
#include <functional>
#include <vector>

namespace pp {

    // for holding data
    struct ls_result {
        pp::vector<double> coefficients;
        pp::matrix<double> covariance;
    };
    // part A:
    ls_result lsfit(const std::vector<std::function<double(double)>>& fs, 
                             const pp::vector<double>& x, 
                             const pp::vector<double>& y, 
                             const pp::vector<double>& dy) {
        int n = x.size();
        int m = fs.size();
        
        pp::matrix<double> A(n, m);
        pp::vector<double> b(n);

        // Fill A and b with weighted values: A_ik = fk(xi)/dyi, bi = yi/dyi
        for (int i = 0; i < n; ++i) {
            b[i] = y[i] / dy[i];
            for (int k = 0; k < m; ++k) {
                A(i, k) = fs[k](x[i]) / dy[i];
            }
        }

        // perform QR 
        pp::qr<double> solver(A);

        // calculates Q.T * b and backsub
        pp::vector<double> result = solver.solve(b);

    




        // Calaculating R inverse
        pp::matrix<double> R_inv(m, m);
        for (int i = 0; i < m; i++) {
            pp::vector<double> e(m); 
            for(int k=0; k<m; k++) e[k] = 0;
            e[i] = 1.0;
            // inverse column
            pp::vector<double> row = solver.backsub(solver.R, e);
            for (int j = 0; j < m; j++) R_inv.set(j, i, row[j]);
        }

        //  (R^T * R)^-1
        pp::matrix<double> cov = R_inv * R_inv.transpose();





        return {result, cov};
    }
}