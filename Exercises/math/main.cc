#include<cmath>
#include<iostream>
#include <numbers>
#include"sfuns.h"
#include <iomanip> // Required for setprecision


int main(){

    std::cout << std::setprecision(6) << std::showpoint;


    double sqrt2=std::sqrt(2.0);
    std::cout << "sqrt(2) = " << sqrt2 << std::endl;

    double two_root_five=std::pow(2.0, 0.2);
    std::cout << "2^(1/5) = " << two_root_five << std::endl;

    double exp__to_pi=std::exp(std::numbers::pi);
    std::cout << "e^(pi)    = " << exp__to_pi << std::endl;

    double pi__to_exp=std::pow(std::numbers::pi, std::numbers::e);
    std::cout << "pi^(e) = " << pi__to_exp << std::endl;

    for(int i=1;i<=10;i++) {
        std::cout << "Gamma of " << i << " is: " << sfuns::fgamma(i) <<"\n";
    }

    for(int i=1;i<=10;i++) {
        std::cout << "lngamma of " << i << " is: " << sfuns::lngamma(i) <<"\n";
    }


    return 0;
}



