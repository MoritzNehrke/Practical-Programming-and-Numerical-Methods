#include<iostream>
#include<cstring>
#include<cstdlib>
#include<fstream>
#include"linearalgebra.h"
#include<random>

//function to create a random symmetric matric with a fixed seed

pp::matrix random_symmetric_matrix(int n, double min = 0.0, double max = 1.0){
    std::random_device rd;
    std::mt19937 gen(10);
    std::uniform_real_distribution<double> dis(min, max);

    pp::matrix A(n,n);
    for(int i=0;i<n;i++){
        for(int j=i;j<n;j++){
            double value = dis(gen);
            A(i,j) = value;
            A(j,i) = value;
        }
    }
    return A;
}


int main(int argc, char** argv) {

    //A

    std::cout << "We create a random symmetric matrix of size 10 A" << std::endl;
    pp::matrix A = random_symmetric_matrix(10);
    A.print("A=");
    std::cout << "We perform the Eigenvalue decomposition, obtain the matrices D and V and the eigenvalues in vector from w" << std::endl;
    pp::evd evd(A);
    evd.w.print("w=");
    evd.D.print("D=");
    evd.V.print("V=");
    std::cout << "We make sure that VtAV = D, VDVt = A VVt = 1" << std::endl;
    (evd.V.transpose()*A*evd.V-evd.D).print("VtAV - D =");
    (evd.V*evd.D*evd.V.transpose() - A).print("VDVt - A =");
    (evd.V*evd.V.transpose()).print("VVt =");

    //B

    double dr = 0.3;
    double rmax = 10;
    bool write_wavefile = false;

    for(int i=1;i<argc-1;i++){
        if(std::strcmp(argv[i],"-rmax")==0) rmax = std::atof(argv[i+1]);
        if(std::strcmp(argv[i],"-dr")  ==0) dr   = std::atof(argv[i+1]);
    }
    for(int i=1;i<argc;i++){
        if(std::strcmp(argv[i],"-wavefile")==0) write_wavefile = true;
    }

    // Mainly copied from the exercise

    int npoints = (int)(rmax/dr)-1;
    pp::vector r(npoints);
    for(int i=0; i<npoints; i++)r[i]=dr*(i+1);
    pp::matrix H(npoints,npoints);
    for(int i=0; i<npoints-1; i++){
        H(i,i) = -2*(-0.5/dr/dr);
        H(i,i+1) = (-0.5/dr/dr);
        H(i+1,i) = (-0.5/dr/dr);
    }
    H(npoints-1,npoints-1) = -2*(-0.5/dr/dr);
    for(int i=0; i<npoints; i++)H(i,i)+=-1/r[i];

    std::cout << "We can use our eigenvalue algorithm to solve the s-wave radial Schrödinger equation" << std::endl;

    pp::evd evd2(H);

    std::cout << "We now sweep over dr and rmax for fixed rmax and dr, the ground state energy calculated by this can be found in the corresponding plots" << std::endl;

    std::cout << "EPS0 " << dr << " " << rmax << " " << evd2.w[0] << std::endl;

    std::cout << "We now calculate several lowest eigen-functions for rmax = 50 and dr = 0.1. The result can be seen in wavefunctions.pdf " << std::endl;

    //Here I am using fstream, recommended by AI
     
    if(write_wavefile == true){
        pp::matrix norm_V = 1/sqrt(dr)*evd2.V;
        int nstates = std::min(npoints, 3);
 
        std::ofstream out("wavefunctions.dat");
        for(int i=0; i<npoints; i++){
            if(norm_V(i,i)<0)norm_V[i]*=-1;
            double rr = r[i];
            out << rr;
            for(int k=0; k<nstates; k++){
                out << " " << norm_V(i,k);
            }
            //AI generated out of convinience
            double f1_exact = 2.0*rr*std::exp(-rr);
            double f2_exact = (1.0/(2.0*std::sqrt(2.0)))*(2.0-rr)*rr*std::exp(-rr/2.0);
            double f3_exact = (2.0/(81.0*std::sqrt(3.0)))*(27.0-18.0*rr+2.0*rr*rr)*rr*std::exp(-rr/3.0);
            out << " " << f1_exact << " " << f2_exact << " " << f3_exact;
 
            out << "\n";
        }
        out.close();
    }

    //C

    std::cout << "We make sure the runtime scales as O(N^3), which can be seen in times.pdf" << std::endl;

    int N = 50;

    for(int i=1;i<argc-1;i++){
        if(std::strcmp(argv[i],"-N")==0) {
        N = std::atoi(argv[i+1]);
        pp::matrix C = random_symmetric_matrix(N);
        pp::evd evd3(C);
        }
    }

}