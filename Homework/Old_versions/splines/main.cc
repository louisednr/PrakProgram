#include "spline.hpp" //check!!!!!!
#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>
#include <fstream>




using namespace std;


int binsearch(const vector<double>& x, double z)
	{/* locates the interval for z by bisection */ 
	assert( z>=x[0] && z<=x[x.size()-1] );
	int i=0, j=x.size()-1;
	while(j-i>1){
		int mid=(i+j)/2;
		if(z>x[mid]) i=mid; else j=mid;
		}
	return i;
	}   


double linterp(const vector<double>& x, const vector<double>& y, double z){
	int i=binsearch(x,z);
  	double dx=x[i+1]-x[i];
  	assert(dx>0);
  	double dy=y[i+1]-y[i];
  	return y[i]+dy/dx*(z-x[i]);
  	}


double linterpInteg(const vector<double>& x, const vector<double>& y, double z) {
    /* adapted from page 3 of interpolation pdf */ 
    int idx = binsearch(x, z);
    double total_integral = 0.0;

    // 
    for (int i = 0; i < idx; i++) {
        double dx = x[i+1] - x[i];
        double dy = y[i+1] - y[i];
        double p_i = dy / dx;
        // equation (8)
        total_integral += y[i] * dx + p_i * (dx * dx) / 2.0;
    }

    // partial integral from x[idx] to z
    double dx_partial = z - x[idx];
    double dx_full = x[idx+1] - x[idx]; 
    double dy_full = y[idx+1] - y[idx];
    double p_idx = dy_full / dx_full;
    
    // equation (8) again
    total_integral += y[idx] * dx_partial + p_idx * (dx_partial * dx_partial) / 2.0;

    return total_integral;
}


int main() {


    double start = 0.0;
    double end = 9.0;
    double step = 0.5;
    int n = ((end - start) / step + 1e-9) + 1;

    vector<double> x_points(n), y_points(n);
    for (int i = 0; i < n; ++i) {
        double xi = start + i * step;
        x_points[i] = xi;
        y_points[i] = cos(xi);
    }

    // adding data for plotting
    ofstream data_file("data.txt");
    for (size_t i = 0; i < x_points.size(); ++i) {
        data_file << x_points[i] << " " << y_points[i] << "\n";
    }
    data_file.close();


    //for linear spline
    ofstream res_file("results.txt");
    for (double z= start; z < end + 1e-9; z += 0.05) {
        double val = linterp(x_points, y_points, z);
        double integ = linterpInteg(x_points, y_points, z);
        // format: z, interp_val, integral_val
        res_file << z << " " << val << " " << integ << "\n";
    }
    res_file.close();

    QuadSpline qs(x_points, y_points); 
    ofstream res_quad("res_quad.txt");
    for (double z = start; z <= end + 1e-9; z += 0.05) {
        double val = qs.eval(z);
        double der = qs.derivative(z);
        double integ = qs.integral(z);
        // format: x, spline, derivative, integral
        res_quad << z << " " << val << " " << der << " " << integ << "\n";
    }
    res_quad.close();


    cout << "Data generated" << endl;
   


    // testing functions: 

    // {xi=i, yi=1} -> Expected: b=0, c=0
    vector<double> x1 = {1, 2, 3, 4, 5}, y1 = {1, 1, 1, 1, 1};
    QuadSpline qs1(x1, y1);
    qs1.print_coeffs("Table {xi=i, yi=1}");
    cout << "Expected: b=0, c=0" << endl;

    // {xi=i, yi=xi} -> Expected: b=1, c=0
    vector<double> x2 = {1, 2, 3, 4, 5}, y2 = {1, 2, 3, 4, 5};
    QuadSpline qs2(x2, y2);
    qs2.print_coeffs("Table {xi=i, yi=xi}");
    cout << "Expected: b=1, c=0"<< endl;

    // {xi=i, yi=xi^2} -> Expected: b=2*xi, c=1
    vector<double> x3 = {1, 2, 3, 4, 5}, y3 = {1, 4, 9, 16, 25};
    QuadSpline qs3(x3, y3);
    qs3.print_coeffs("Table {xi=i, yi=xi^2}");
    cout << "Expected: b=2*xi, c=1" << endl;

    
 



    return 0;
}
