#include "linearalgebra.h"
#include <iostream>
#include <random>

//--------------------------------------------------------------------------------------
// Here are the implentations for random vector and matrix generation, currently set to a fixed seed for reproducibility.
//--------------------------------------------------------------------------------------

pp::vector random_vector(int n, double min = 0.0, double max = 1.0) {
    std::random_device rd;
    std::mt19937 gen(10);
    std::uniform_real_distribution<double> dis(min, max);

    pp::vector v(n);
    for (int i = 0; i < n; ++i) {
        v[i] = dis(gen);
    }
    return v;
}

pp::matrix random_matrix(int m, int n, double min = 0.0, double max = 1.0) {
    std::random_device rd;
    std::mt19937 gen(10);
    std::uniform_real_distribution<double> dis(min, max);

    pp::matrix A(m, n);
    for (int j = 0; j < n; ++j) {
        for (int i = 0; i < m; ++i) {
            A(i, j) = dis(gen);
        }
    }
    return A;
}

//--------------------------------------------------------------------------------------
//Here you can find the main function that tests the QR decomposition and other functionalities of the linear algebra implentation.
//--------------------------------------------------------------------------------------

int main(int argc, char const *argv[]) {
    std::cout << "We create a random tall 10 x 4 matrix A and perform QR decomposition on it." <<std::endl;
    pp::matrix A = random_matrix(10, 4);
    A.print("A=");
    pp::qr qr(A);
    pp::matrix Q = qr.Q;
    pp::matrix R = qr.R;
    Q.print("Q=");
    R.print("R=");
    std::cout << "We can see that R is upper triangular and we check that Q*R = A and that Q^T*Q = I." << std::endl;
    (Q*R-A).print("QR-A=");
    (Q.transpose()*Q).print("QtQ=");
    std::cout << "We create a random square matrix B of size 10 x 10 and a random vector b and solve the system Bx=b using the QR decomposition." << std::endl;
    pp::matrix B = random_matrix(10, 10);
    pp::vector b = random_vector(10);
    b.print("b=");
    pp::qr qr2(B);
    pp::vector x = qr2.solve(b);
    x.print("x=");
    std::cout << "We check that Bx=b." << std::endl;
    (B*x-b).print("Bx-b=");
    std::cout << "The determinant of B is given as the determinant of R." << qr2.det() << std::endl;
    std::cout << "We compute the inverse of B using the QR decomposition." << std::endl;
    pp::matrix B_inv = qr2.inverse();
    B_inv.print("B^{-1}=");
    std::cout << "We check that B*B^{-1} = I." << std::endl;
    (B*B_inv).print("BB^{-1}=");
    
    //--------------------------------------------------------------------------------------
    // Here we measure the time it takes to solve a system of linear equations using the QR decomposition for different sizes of matrices and vectors.
    //--------------------------------------------------------------------------------------


    int N = 100;

    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "-size" && i + 1 < argc)
            N = std::stoi(argv[++i]);

    pp::qr qr3(random_matrix(N, N));
    qr3.solve(random_vector(N));
    }

    std::cout << "The measured times out.times.data are plotted and fitted by a*N^3 in times.svg and the algorithmic complexity is seen to be O(N^3)" << std::endl;

}