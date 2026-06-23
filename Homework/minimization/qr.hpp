
#pragma once
#include<iostream>
#include "matrix.hpp"



namespace pp{

    template <typename T>
    struct qr {
        matrix<T> Q,R;
        
        qr(const matrix<T>& A) {
            
            
            int m = A.size2();

            //initializing Q and R

            Q = A;
            R = matrix<T>(m,m);

            //orthogonalization

            for (int i=0;i<m; i++){
                R[i,i] = Q[i].norm();
                Q[i] /= R[i,i];
                for (int j=i+1;j<m; j++){
                    R[i,j]= Q[i].dot(Q[j]);
                    Q[j] -= Q[i] * R[i,j];
                }
            }
            
            
        }

          // back-substitution
        vector<T> backsub(const matrix<T>& R, const vector<T>& z) const{
            vector<T> subs(R.size2());
            for (int i = z.size() -1 ; i >= 0; i--) {
                T sum = 0;
                for (int k= i+1; k< z.size(); k++) sum += R[i,k] * subs[k];
                subs[i]= (z[i]-sum)/R[i,i];
            }

            return subs; 
        }

        // solve method inside class
        vector<T> solve(const vector<T>& b) const {
            vector<T> y = Q.transpose() * b;
            return backsub(R, y);
        }


        double det() const {
            double determin = 1;
            for (int i=0; i < R.size1(); i++) {
                determin *= R[i,i];
            }
            return determin;
        }


        matrix<T> inverse() const {

            //backsubs 

            // find Q^T since I will need it a lot :)
            // then use R*x=Q^T[ith columb], since I know e[i] are unit vectors
            // retrun inverse


            int n = Q.size1();
            matrix<T> B(n,n);


            matrix<T> QT = Q.transpose();


            for (int i=0; i<n; i++) {

                // definining i'th column of  Q^T as a vector
                // because this is Q^T*e_i
        
                vector<T> qt_col = QT[i];

                // instead of using solve, use backsubs
                vector<T> x_i = backsub(R, qt_col);

                B[i]= x_i;

            }
            return B;

        }

    };
}


