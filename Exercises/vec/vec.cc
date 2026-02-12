#include"vec.h"
#include<cmath>

namespace vec{

    
    // arithmetic
    vec& vec::operator+=(const vec& a){
        x += a.x;
        y += a.y;
        z += a.z;
        return *this;
    }
    vec& vec::operator-=(const vec& a){
        x -= a.x;
        y -= a.y;
        z -= a.z;
        return *this;
    }

    vec& vec::operator*=(double a){
        x *= a;
        y *= a;
        z *= a;
        return *this;
    }
    vec& vec::operator/=(double a){
        x /= a;
        y /= a;
        z /= a;
        return *this;
    }


    // non-member operators

    vec operator+(vec a, const vec& b){
        a += b;
        return a;
    }

    vec operator-(const vec& a){
	vec r=a;
	r.x=-r.x;
	r.y=-r.y;
	r.z=-r.z;
	return r;
    }

    vec operator-(const vec& a, const vec& b){
        vec r=a;
        r-=b;
        return r;
    }

    vec operator*(const vec& a, double n){
        vec r=a;
        r*=n;
        return r;
    }

    vec operator*(double n, const vec& a){
        vec r=a;
        r*=n;
        return r;
    }


    // approx. (could also have taken this from epsilon exercise)
    bool approx(double a,double b,double acc,double eps){
	    if(std::fabs(a-b)<acc)return true;
	    if(std::fabs(a-b)<eps*(std::fabs(a)+std::fabs(b)))return true;
	    return false;
	}

    bool approx(const vec& u, const vec& v, double acc, double eps){
	    if(!approx(u.x,v.x,acc,eps))return false;
	    if(!approx(u.y,v.y,acc,eps))return false;
	    if(!approx(u.z,v.z,acc,eps))return false;
	    return true;
	}

    double dot(const vec& a, const vec& b){
        return a.x*b.x + a.y*b.y + a.z*b.z;
    }

    vec cross(const vec& a, const vec& b) {

        vec r;
        r.x = a.y*b.z - a.z*b.y;
        r.y = a.z*b.x - a.x*b.z;
        r.z = a.x*b.y - a.y*b.x;

        return r;
    }

    double norm(const vec& a) {
        double norm = sqrt(a.x*a.x + a.y*a.y + a.z*a.z);
        return norm;
    }



    // utility
    void vec::set(double a, double b, double c) { x = a; y = b; z = c; }

    void vec::print(const std::string& s) const{
	    std::cout << s << x << " " << y << " " << z;
    }           

    // stream output
    std::ostream& operator<<(std::ostream& os, const vec& v) {
        os << v.x << " " << v.y << " " << v.z;
        return os;
    }


}









