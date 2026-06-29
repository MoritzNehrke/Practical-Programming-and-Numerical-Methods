#include<iostream>
#include<cmath>
#include<cstdio>
#include"linearalgebra.h"
#include<fstream>

int main(){
    int n=20; 
    pp::vector x(n), y(n);
    for(int i=0;i<n;i++){ x[i]=0.5*i; y[i]=std::cos(x[i]); }
 
    int npts=30;

    pp::qspline qs(x,y);

    auto hf = make_qspline(x,y);

    std::ofstream out("interpolation.dat");
    for(int k=0;k<=npts;k++){
        double z = x[0] + (x[n-1]-x[0])*k/npts;
        double f = linterp(x,y,z);
        double F = linterpInteg(x,y,z);
        double g = qs.eval(z);
        double G = qs.integ(z);
        double h = hf(z);
        out << z << " "  << f << " " << F << " " << g << " " << G << " " << h << "\n";
    }
    out.close();

    std::cout << "Everything can be found in the plots :)" << std::endl;
}