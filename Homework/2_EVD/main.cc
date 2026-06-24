#include "matrix.hpp"
#include "evd.hpp"
#include <iostream>
#include <ctime>
#include <chrono>
#include <random>
#include <algorithm> //need for std::sort




int main(int argc, char* argv[]) {


    // for random generation
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    // default values
  
    double rmax = 10; 
    double dr =  0.3;
    int N_benchmark = 100;
    int n =  3; 


    bool convergence_mode = false;
    bool test_mode = false;
    bool benchmark_mode = false;


    for (int i = 1; i < argc; i++) {
    std::string arg = argv[i];

    if (arg == "-convergence") {
        convergence_mode = true;
    } 
    else if (arg == "-test") {
        test_mode = true;
    }
  
    else if (arg == "-benchmark" && i + 1 < argc) {
        benchmark_mode = true;
        N_benchmark = std::stoi(argv[++i]); // matrix of size N
    }
    else if (arg == "-rmax" && i + 1 < argc) {
        rmax = std::stod(argv[++i]);
    } 
    else if (arg == "-dr" && i + 1 < argc) {
        dr = std::stod(argv[++i]);
    }
}


    int npoints = (int)(rmax/dr)-1;
    pp::vector<double> r(npoints);
    for(int i=0;i<npoints;i++)r[i]=dr*(i+1);
    pp::matrix<double> H(npoints,npoints);
    for(int i=0;i<npoints-1;i++){
        H[i,i]  =-2*(-0.5/dr/dr);
        H[i,i+1]= 1*(-0.5/dr/dr);
        H[i+1,i]= 1*(-0.5/dr/dr);
    }
    H[npoints-1,npoints-1]=-2*(-0.5/dr/dr);
    for(int i=0;i<npoints;i++)H[i,i]+=-1/r[i];


    //diagonalizing 

    pp::EVD<double> hamiltonian(H);

    



    if (test_mode) {

        std::cout << "--- Part A ---\n";

        std::cout << "--- 1., 2. and 3. ---\n";
        


        // make matrix
        pp::matrix<double> A(n, n);
        //pp::vector<double> b(n);

        
        // make a random symetric matrix A
        for(int j=0; j<n; j++) 
            for(int i=0; i<n; i++) A[i,j] = A[j,i]=  dist(gen);

        //make b random
        //for(int j=0; j<n; j++)  b[j] = dist(gen);


        // make identitiy matrix for checking later
        pp::matrix<double> I(n,n);
        for (int i=0; i<n; i++) I[i,i] = 1;




        pp::EVD<double> solver(A);


        //printing checks

        std::cout << "--- Random symmetric matrix A ---\n";
        A.print();

        std::cout << "\n--- Check that VtAV == D ---\n";

        auto VtAV = solver.V.transpose() * A * solver.V;
        VtAV.print(" V^T * A * V :");

        auto D = solver.D;

        D.print(" D : ");




        // check  approx equal
        if(pp::approx(VtAV, D )) {
            std::cout << "Success: VtAV is approximately D!" << std::endl;
        }


        std::cout << "\n--- Check that VDVT == A ---\n";

        auto VDVT =   solver.V * solver.D * solver.V.transpose();
        VDVT.print(" V * D * V^T :");

        // check  approx equal
        if(pp::approx(VDVT, A )) {
            std::cout << "Success: VDVT is approximately A!" << std::endl;
        }


        std::cout << "\n--- Check that VtV == 1 ---\n";

        auto VtV = solver.V.transpose() * solver.V;
        VtV.print(" V^T * V :");

        // check  approx equal
        if(pp::approx(VtV, I )) {
            std::cout << "Success: VtV is approximately 1!" << std::endl;
        }


        std::cout << "\n--- Check that VVt == 1 ---\n";

        auto VVt =  solver.V * solver.V.transpose();
        VVt.print(" V * V^T :");

        // check  approx equal
        if(pp::approx(VVt, I )) {
            std::cout << "Success: VVt is approximately 1!" << std::endl;
        }


        std::cout << "--- Part B ---\n";


        // building H



        std::cout << "Running with n=" << n << ", rmax = " << rmax << ", dr = " << dr << "\n";


        H.print(" Original H : ");

        

        std::cout << "\n--- Diagonalized H (D) ---\n";

        hamiltonian.D.print();

        std::cout << "\n--- Eigenvectors (V) ---\n";

        hamiltonian.V.print();


        std::cout << "\n--- Eigenvales (w) ---\n";


        hamiltonian.w.print();


    }

    // for part c: 
    if (benchmark_mode) {
        // random symetric matrix of size N
        pp::matrix<double> A(N_benchmark, N_benchmark);
        std::mt19937 gen(42); 
        std::uniform_real_distribution<double> dist(-1.0, 1.0);

        for (int i = 0; i < N_benchmark; i++) {
            for (int j = i; j < N_benchmark; j++) {
                A[i, j] = A[j, i] = dist(gen);
            }
        }

        // start timing
        auto start = std::chrono::high_resolution_clock::now();
        
        // run solver
        pp::EVD<double> solver(A);

        // end timing
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;

        // output results
        std::cout << N_benchmark << " " << elapsed.count() << std::endl;
        
        return 0; 
    }


    // for part b:
    //the lowest egenvalues and eigenfunctions of the s-wave states in the hydrogen atom and compare with the exact results.

    else if (convergence_mode) {
   
        // Find the min eigenvalue (have not been sorted)
        double e0 = hamiltonian.w[0];
        for(int i=1; i<hamiltonian.w.size(); i++) if(hamiltonian.w[i] < e0) e0 = hamiltonian.w[i];
        
        std::cout << dr << " " << rmax << " " << e0 << std::endl; 
        return 0; 
    } else { // for wavefunctions plots 

        // vector of indices [0, 1, 2, ..., n-1]
        std::vector<int> idx(hamiltonian.w.size());
        for (size_t i = 0; i < idx.size(); ++i) idx[i] = i;

        // sort the indices based on the values in hamiltonian.w
        std::sort(idx.begin(), idx.end(), [&](int a, int b) {
            return hamiltonian.w[a] < hamiltonian.w[b];
        });

        
        // for constant
        double inv_sqrt_dr = 1.0 / std::sqrt(dr);

        // print wave function in correct colums, choose to plot first 4
        for (int i = 0; i < npoints; i++) {
            double r_val = dr * (i + 1);
            std::cout << r_val << " " 
                  << hamiltonian.V[i, idx[0]] * inv_sqrt_dr << " " 
                  << hamiltonian.V[i, idx[1]] * inv_sqrt_dr << " "
                  << hamiltonian.V[i, idx[2]] * inv_sqrt_dr << " "
                  << hamiltonian.V[i, idx[3]] * inv_sqrt_dr << std::endl;
    }
    }
    


  








    return 0;
}
