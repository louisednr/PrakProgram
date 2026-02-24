#pragma once
#include<iostream>
#include<cmath>
#include<string>
#include<complex>

namespace vec{

    template <typename T>
    struct vec {
        T x, y, z;

        // constructors
        vec(T x, T y, T z) : x(x), y(y), z(z) {}  // parameterized
        vec() : vec(0, 0, 0) {}                                    // default
        vec(const vec<T>&) = default;                                 // copy
        vec(vec<T>&&) = default;                                      // move
        ~vec() = default;                                          // destructor

        // assignment
        vec<T>& operator=(const vec<T>&) = default;                     // copy assignment
        vec<T>& operator=(vec<T>&&) = default;                          // move assignment

        // arithmetics
        vec<T>& operator+=(const vec<T>& a){
            x += a.x;
            y += a.y;
            z += a.z;
            return *this;
        }
        
        
        vec<T>& operator-=(const vec<T>& a){
            x -= a.x;
            y -= a.y;
            z -= a.z;
            return *this;
        }

     
        vec<T>& operator*=(T a){
            x *= a;
            y *= a;
            z *= a;
            return *this;
        }
       
        vec<T>& operator/=(T a){
            x /= a;
            y /= a;
            z /= a;
            return *this;
        }


        // utility
        void set(T a, T b, T c) { x = a; y = b; z = c; }

        
        void print(const std::string& s) const{
            std::cout << s << x << " " << y << " " << z;
        }           

        // stream output
        friend std::ostream& operator<<(std::ostream& os, const vec<T>& v) {
            os << v.x << " " << v.y << " " << v.z;
            return os;
        }
    };

   


  


    template <typename T>
    vec<T> operator+(vec<T> a, const vec<T>& b){
        a += b;
        return a;
    }

    template <typename T>
    vec<T> operator-(const vec<T>& a){
	vec r=a;
	r.x=-r.x;
	r.y=-r.y;
	r.z=-r.z;
	return r;
    }

    template <typename T>
    vec<T> operator-(const vec<T>& a, const vec<T>& b){
        vec<T> r=a;
        r-=b;
        return r;
    }

    template <typename T>
    vec<T> operator*(const vec<T>& a, T n){
        vec<T> r=a;
        r*=n;
        return r;
    }

    template <typename T>
    vec<T> operator*(T n, const vec<T>& a){
        vec<T> r=a;
        r*=n;
        return r;
    }


    // dot cross norm

     template <typename T>
    T dot(const vec<T>& a, const vec<T>& b){
        return a.x*b.x + a.y*b.y + a.z*b.z;
    }

    template <typename T>
    vec<T> cross(const vec<T>& a, const vec<T>& b) {

        vec<T> r;
        r.x = a.y*b.z - a.z*b.y;
        r.y = a.z*b.x - a.x*b.z;
        r.z = a.x*b.y - a.y*b.x;

        return r;
    }

    template <typename T>
    auto norm(const vec<T>& a) {
        return std::sqrt(std::norm(a.x) + std::norm(a.y) + std::norm(a.z));
    }

    // approximate equality
    template <typename T>
    bool approx(T a,T b,double acc = 1e-6 ,double eps = 1e-6){
        using std::abs;
        auto diff = abs(a-b);
	    if( diff <acc)return true;
	    if( diff <eps*(abs(a)+ abs(b)))return true;
	    return false;
	}
    template <typename T>
    bool approx(const vec<T>& u, const vec<T>& v, double acc =1e-6, double eps = 1e-6){
        auto d = norm(u - v);
        if (d < acc) return true;
        if (d < eps * (norm(u) + norm(v))) return true;
        return false;
	}
}