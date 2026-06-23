#pragma once
#include<iostream>
#include<cstdio>
#include<cassert>
#include<cstdio>
#include<iomanip>
#include<cmath>
#include<string>
#include<vector>
#include<initializer_list>
#include<functional>
#include<ranges>
#define FOR(i,V) for(int i=0;i<V.size();i++)
#define FOR1(i,A) for(int i=0;i<A.size1();i++)
#define FOR2(j,A) for(int j=0;j<A.size2();j++)




namespace pp{

    template <typename T>
    struct vector {
        std::vector<T> data;

        vector() = default;
        vector(int n) : data(n) {}
        vector(std::initializer_list<T> list) : data(list) {}
        vector(const vector&) = default;
        vector(vector&&) noexcept = default;

        vector& operator=(const vector&) = default;
        vector& operator=(vector&&) noexcept = default;

        inline int size() const {return data.size();}
    //	auto n(){return std::views::iota(0,size());}
    //	void resize(int n) {data.resize(n);}
        inline T& operator[](int i) {return data[i];}
        inline const T& operator[](int i) const {return data[i];}


        vector& operator+=(const vector& other) {
            for (int i = 0; i< size(); i++ ) {
                data[i] += other.data[i];
            }
            return *this;
        }

        vector& operator-=(const vector& other) {
            for (int i = 0; i < size(); i++) {
                data[i] -= other.data[i];
            }
            return *this;
        }

        vector& operator*=(T c) {
            for (auto& element : data) {
                element *= c;
            }
            return *this;
        }

        vector& operator/=(T c) {
            for (auto& element : data) {
                element /= c;
            }
            return *this;
        }

        T norm() const {
            T sum2=0;
            for (const auto& val : data) {
                sum2 += val * val;
            }
            return std::sqrt(sum2);
        }

        T dot(const vector& other) const {
            T sum1 = 0;
            for(int i = 0; i<size(); i++) {
                sum1 += (*this)[i]*other[i];
            }
            return sum1;
        }

        void print(std::string s="") const {
            std::cout << s << "\n";
            for(int i = 0; i < size(); i++) {
                std::cout << std::setw(10) << (*this)[i] << " ";
                }
                std::cout << "\n";
            }
        

        


        vector<T> map(std::function<T(T)> f) const{
            vector<T> r(size());
            FOR(i, (*this)) r.data[i]=f(data[i]);
            return r;
        }

    }; //vector

    template <typename T>
    inline vector<T>  operator+(vector<T> a, const vector<T>& b){ a+=b ; return a; }
    template <typename T>
    inline vector<T>  operator-(vector<T> a)                 { a*=-1; return a; }
    template <typename T>
    inline vector<T>  operator-(vector<T> a, const vector<T>& b){ a-=b ; return a; }
    template <typename T>
    inline vector<T>  operator*(vector<T> a, const T c) { a*=c ; return a; }
    template <typename T>
    inline vector<T>  operator*(const T c, vector<T> a) { a*=c ; return a; }
    template <typename T>
    inline vector<T>  operator/(vector<T> a, const T c) { a/=c ; return a; }

   
    template <typename T>
    bool approx(T a,T b,double acc = 1e-6 ,double eps = 1e-6){
        using std::abs;
        auto diff = abs(a-b);
	    if( diff <acc)return true;
	    if( diff <eps*(abs(a)+ abs(b)))return true;
	    return false;
	}
    template <typename T>
    bool approx(const vector<T>& u, const vector<T>& v, double acc =1e-6, double eps = 1e-6){
        auto d = (u-v).norm();
        if (d < acc) return true;
        if (d < eps * (u.norm() + v.norm())) return true;
        return false;
	}


    template <typename T>
    struct matrix {
        std::vector<pp::vector<T>> cols;
        matrix()=default;
        matrix(int n,int m) : cols(m, pp::vector<T>(n)) {}
        matrix(const matrix& other)=default;
        matrix(matrix&& other)=default;
        matrix& operator=(const matrix& other)=default;
        matrix& operator=(matrix&& other)=default;
        int size1() const {return cols.empty() ? 0 : cols[0].size(); }
        int size2() const {return cols.size();}
        inline T& operator()(int i, int j){return cols[j][i];}
        inline T& operator[](int i, int j){return cols[j][i];}
        inline const T& operator()(int i, int j)const{return cols[j][i];}
        inline const T& operator[](int i, int j)const{return cols[j][i];}
        inline vector<T>& operator[](int i){return cols[i];}
        inline const vector<T>& operator[](int i) const {return cols[i];}


    //	void resize(int n, int m);
        void setid(){
            assert(size1()==size2());
            for(int i=0;i<size1();i++){
                (*this)[i,i]=1;
                for(int j=i+1;j<size1();j++)(*this)[i,j]=(*this)[j,i]=0;
                }
            }
        matrix transpose() const{
            matrix R(size2(),size1());
            FOR1(i,(*this))
            FOR2(j,(*this))
                R[j,i]=(*this)[i,j];
            return R;
        }

        matrix transposed() const {return transpose();}
        
        T get (int i, int j) const {return cols[j][i];}
        void set(int i, int j, T value){cols[j][i] = value;}
    //	vector get_col(int j);
    //	void set_col(int j,vector& cj);

        matrix<T>& operator+=(const matrix<T>& B){
            for(int i=0;i<size2();i++)(*this)[i]+=B[i];
            return *this;
            }
        matrix<T>& operator-=(const matrix<T>& B){
            for(int i=0;i<size2();i++)(*this)[i]-=B[i];
            return *this;
            }
        matrix<T>& operator*=(const T c){
            for(int i=0;i<size2();i++)(*this)[i]*=c;
            return *this;
            }
        matrix<T>& operator/=(const T c){
            for(int i=0;i<size2();i++)(*this)[i]/=c;
            return *this;
            }
        matrix<T>& operator*=(const matrix<T>&);
        matrix<T>  operator^(int);

        void print(std::string s="") const{
            printf("%s\n",s.c_str());
            for(int i=0;i<size1();i++){
                for(int j=0;j<size2();j++)printf("%10.3g ",(*this)[i,j]);
                printf("\n");
            }
        }
    };


    template <typename T>
    inline matrix<T> operator+(matrix<T> A, const matrix<T>& B){
        for(int i=0;i<A.size2();i++)A[i]+=B[i];
        return A;
        }

    template <typename T>
    inline matrix<T> operator-(matrix<T> A, const matrix<T>& B){
        for(int i=0;i<A.size2();i++)A[i]-=B[i];
        return A;
        }

    template <typename T>
    inline vector<T> operator*(const matrix<T>& A, const vector<T>& v){
        vector<T> r(A.size1());
        FOR2(j,A){
            T vj=v[j];
            FOR1(i,A) r[i]+=A[i,j]*vj;
            }
        return r;
        }

    template <typename T>
    inline matrix<T> operator*(const matrix<T>& A, const matrix<T>& B){
        assert(A.size2()==B.size1());
        matrix<T> R(A.size1(),B.size2());
        FOR2(j,R) R[j]=A*B[j];
        return R;
        }

    template <typename T>
    inline matrix<T> operator*(matrix<T> A, const T c){
        for(auto &col : A.cols) col*=c;
        return A;
        }

    template <typename T>
    inline matrix<T> operator*(const T c, matrix<T> A){
        for(auto &col : A.cols) col*=c;
        return A;
        }
    
    template <typename T>
    inline matrix<T> operator/(matrix<T> A, const T c){
        for(auto &col : A.cols) col/=c;
        return A;
        }



    
    template <typename T>
    bool approx(const matrix<T>& A, const matrix<T>& B, double acc = 1e-6, double eps = 1e-6) {

        //check dimensions         
        if (A.size1() != B.size1() || A.size2() != B.size2()) return false;

        //trying to make this the same as vector approx by comparing norms

        double sum_sq_diff = 0.0;
        double sum_sq_A = 0.0;
        double sum_sq_B = 0.0;

        for (int j = 0; j < A.size2(); ++j) {
            auto diff_vec = A[j] - B[j];
            double d_norm = diff_vec.norm();
            sum_sq_diff += d_norm * d_norm;

            double a_norm = A[j].norm();
            sum_sq_A += a_norm * a_norm;

            double b_norm = B[j].norm();
            sum_sq_B += b_norm * b_norm;
        }

        double total_diff = std::sqrt(sum_sq_diff);
        double total_A    = std::sqrt(sum_sq_A);
        double total_B    = std::sqrt(sum_sq_B);


        if (total_diff < acc) return true;
        if (total_diff < eps * (total_A + total_B)) return true;
        
        return false;
    }



    // Vector out-stream
    template <typename T>
    std::ostream& operator<<(std::ostream& os, const vector<T>& v) {
        os << "[";
        for (int i = 0; i < v.size(); ++i) {
            os << v[i] << (i == v.size() - 1 ? "" : ", ");
        }
        os << "]";
        return os;
    }

    // Matrix out-stream
    template <typename T>
    std::ostream& operator<<(std::ostream& os, const matrix<T>& A) {
        for (int i = 0; i < A.size1(); ++i) {
            for (int j = 0; j < A.size2(); ++j) {
                // Using your A(i,j) accessor
                os << std::setw(10) << A(i, j) << " ";
            }
            os << "\n";
        }
        return os;
    }

}//pp




