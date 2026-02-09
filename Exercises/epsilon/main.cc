#include<iostream>
#include"approx.h"
#include<limits>
#include<cmath>
#include<iomanip>


int main(){
    // Exercise 1: Machine epsilon
    float       f=1.0f; while((float)      (1.0f+f) != 1.0f){f/=2.0f;} f*=2.0f;
    double      d=1.0; while((double)     (1.0+d) != 1.0){d/=2.0;} d*=2.0;
    long double l=1.0L; while((long double)(1.0L+l) != 1.0L){l/=2.0L;} l*=2.0L;


    std::cout <<" float eps= " << f << "\n";
    std::cout <<" double eps= " << d << "\n";
    std::cout <<" long double eps= " << l << "\n";

    std::cout <<" float eps system = " << std::numeric_limits<float>::epsilon() << "\n";
    std::cout <<" double eps system = "<< std::numeric_limits<double>::epsilon() << "\n";
    std::cout << "test 2^-52 = " << std::pow(2,-52) << "\n";
    std::cout <<" long double eps system = " << std::numeric_limits<long double>::epsilon() << "\n";
    std::cout << "test 2^-23 = " << std::pow(2,-23) << "\n";


    if (std::abs(f - std::numeric_limits<float>::epsilon()) < 1e-50
        && abs(d - std::numeric_limits<double>::epsilon()) < 1e-50
        && abs(l - std::numeric_limits<long double>::epsilon()) < 1e-50)   {
    std::cout << "float, double, long double epsilon matches system standard. Since the diffrence between all three sets of numbers is < 1e-50 " << std::endl;}
    

    // Exercise 2: Non-commutativity of addition
    double epsilon=std::pow(2,-52);
    double tiny=epsilon/2;
    double a=1+tiny+tiny;
    double b=tiny+tiny+1;
    std::cout << "a==b ? " << (a==b ? "true":"false") << "\n";
    std::cout << "a>1  ? " << (a>1  ? "true":"false") << "\n";
    std::cout << "b>1  ? " << (b>1  ? "true":"false") << "\n";

    std::cout << "Explain result:"  << "\n";
    std::cout << "Floating-point addition is not associative because intermediate rounding causes small values to be discarded when added to significantly larger numbers." << "\n";


    std::cout << std::fixed << std::setprecision(17);
    std::cout << "       tiny=" << tiny << "\n";
    std::cout << "1+tiny+tiny=" << a << "\n";
    std::cout << "tiny+tiny+1=" << b << "\n";

    // Exercise 3: Comparing doubles: introduction
    double d1 = 0.1+0.1+0.1+0.1+0.1+0.1+0.1+0.1;
    double d2 = 8*0.1;

    std::cout << "d1==d2?" << (d1==d2 ? "true":"false") << "\n";

    std::cout << std::fixed << std::setprecision(17);
    std::cout << "d1=" << d1 << "\n";
    std::cout << "d2=" << d2 << "\n";

    std::cout << "Approx(d1, d2, double acc=1e-9, double eps=1e-9) is = "  << approx(d1,d2) <<"\n";

    

    return 0;
}