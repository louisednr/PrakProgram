#include "matrix.hpp"
#include "qr.hpp"
#include "lsfit.hpp"
#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <vector>

//for approx of modern value
template <typename T>
    bool approx(T a,T b,double acc = 1e-6 ,double eps = 1e-6){
        using std::abs;
        auto diff = abs(a-b);
	    if( diff <acc)return true;
	    if( diff <eps*(abs(a)+ abs(b)))return true;
	    return false;
	}


int main(int argc, char* argv[]) {


    // data to investigate
    pp::vector<double> t = {1,  2,  3, 4, 6, 9,   10,  13,  15}; // time days
    pp::vector<double> y = {117,100,88,72,53,29.5,25.2,15.2,11.1} ; //activity of ThX (relative units)
    pp::vector<double> dy = {6,5,4,4,4,3,3,2,2}; // uncertainty assumed 5%

    int n = y.size();

    // transform for linear fit  (ln(y) = ln(a) - lambda*t)
    pp::vector<double> z(y.size());
    pp::vector<double> dz(y.size());
    for(int i = 0; i < y.size(); ++i) {
        z[i] = std::log(y[i]);
        dz[i] = dy[i] / y[i];
    }

    // initialize fs
    std::vector<std::function<double(double)>> fs = {
        [](double x) { return 1.0; },
        [](double x) { return -x; }
    };


    // Solve
    pp::ls_result result = pp::lsfit(fs, t, z, dz);

    // store results
    double a = std::exp(result.coefficients[0]);
    double error_ln_a = std::sqrt(result.covariance(0, 0));
    double error_a = a * error_ln_a;
    double lambda = result.coefficients[1];
    double half_life = std::log(2) / lambda;
    double error_lambda = std::sqrt(result.covariance(1, 1));
    double error_half_life = std::log(2)/std::pow(lambda, 2) * error_lambda;
    double diff = 3.6316 - half_life;

    // Output Results


    std::cout << std::fixed << std::setprecision(4);
    std::cout << "Fit results for ThX decay:" << std::endl;
    std::cout << "Initial activity (a): " << a << std::endl;
    std::cout << "Decay Ccnstant (lambda): " << lambda << " days^-1" << std::endl;
    std::cout << "Uncertainty in lambda: " << error_lambda << std::endl;
    std::cout << "Half-life: " << half_life << " days" << std::endl;
    std::cout << "Uncertainty in half-life: " << error_half_life << std::endl;
    std::cout << "Ra-224 decays by ɑ decay with a half-life of 3.6316(23) days."<< std::endl;
    std::cout << "Modern half-live - calculated half-life = "<< diff << std::endl;
    if (diff*diff < error_half_life*error_half_life) {
        std::cout << "Result agrees with the modern value within the estimated uncertainty"<<  std::endl;
    } else {
        std::cout << "Result does NOT agrees with the modern value within the estimated uncertainty"<<  std::endl;
    }

  
   
    


    // adding data for plotting
    std::ofstream data_file("data.txt");
    for(int i=0; i < n; ++i) {
        data_file << t[i] << " " << y[i] << " " << dy[i] << "\n";
    }
    data_file.close();

    std::ofstream fit_file("fit_results.txt");
    fit_file << a << " " << lambda << " " << error_a << " " << error_lambda << "\n";
    fit_file.close();
 



    return 0;
}


