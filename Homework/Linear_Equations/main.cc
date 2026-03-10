#include "matrix.hpp"
#include "qr.hpp"
#include <iostream>
#include <ctime>
#include <chrono>
#include <random>








int main(int argc, char* argv[]) {


    // for random generation
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(0.0, 1.0);


    // -------- for timing --------
    if (argc > 2 && std::string(argv[1]) == "-timing") {
        int N = std::stoi(argv[2]);
        pp::matrix<double> A(N, N);
        for(int j=0; j<N; j++)
            for(int i=0; i<N; i++) A[i,j] = dist(gen);

        // make matrix, then start timing
        auto start = std::chrono::high_resolution_clock::now();
        
        pp::qr<double> solver(A); 
        
        // stop timer
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = end - start;


        std::cout << N << " " << diff.count() << std::endl;
        return 0; 
    }

     // -------- -------- -------- --------

    std::cout << "--- Part A ---\n";

    std::cout << "--- 2. ---\n";


    

    
    // check for arguments, otherwise use standard square 
    int n = (argc > 1) ? std::stoi(argv[1]) : 3; 
    int m = (argc > 2) ? std::stoi(argv[2]) : 3;


    // make matrix
    pp::matrix<double> A(n, m);
    pp::vector<double> b(n);



   

    
    // make A random 
    for(int j=0; j<m; j++) 
        for(int i=0; i<n; i++) A[i,j] = dist(gen);

    //make b random
    for(int j=0; j<n; j++)  b[j] = dist(gen);


    // make identitiy matrix for checking later
    pp::matrix<double> I(m,m);
    for (int i=0; i<m; i++) I[i,i] = 1;



    pp::qr<double> solver(A);


    //printing checks

    std::cout << "--- Random matrix A ---\n";
    A.print();



    std::cout << "\n--- Check R is upper triangular ---\n";
    solver.R.print("R Matrix:");

    std::cout << "\n--- Check Q^T * Q = I ---\n";
    auto QtQ = solver.Q.transpose() * solver.Q;
    QtQ.print("Q^T * Q:");

     // check  approx equal
    if(pp::approx(QtQ, I )) {
        std::cout << "Success: QtQ is approximately I!" << std::endl;
    }

    std::cout << "\n--- Check Q * R = A ---\n";
    auto QR = solver.Q * solver.R;
    QR.print("Q * R:");

     // check  approx equal
    if(pp::approx(QR, A )) {
        std::cout << "Success: QR is approximately A!" << std::endl;
    }

    std::cout << "\n";



    std::cout << "--- 3. ---\n";

    std::cout << "--- Random vector b (same size as A) ---\n";
    b.print();

    //  solve QRx = b
    pp::vector<double> x = solver.solve(b);

    // check  Ax = b
    pp::vector<double> Ax = A * x;
    Ax.print("A*x:");

    // check  approx equal
    if(pp::approx(Ax, b)) {
        std::cout << "Success: Ax is approximately b!" << std::endl;
    }

    std::cout << "\n";


    std::cout << "--- 4. ---\n";

    double determinant = solver.det();
    std::cout << "det(R)= " << determinant << std::endl;





    std::cout << "\n";


    std::cout << "--- Part B ---\n";
    pp::matrix<double> B = solver.inverse();

    

    std::cout << "B=inv(A)= " << std::endl;

    B.print();

    std::cout << "check that AB=I: " << std::endl;

    pp::matrix<double> AB = A * B;
    AB.print("A*B:");

    // check  approx equal
    if(pp::approx(AB, I)) {
        std::cout << "Success: A*B is approximately I!" << std::endl;
    }











    return 0;
}