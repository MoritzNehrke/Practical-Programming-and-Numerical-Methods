#include"linearalgebra.h"
#include<cmath>
#include<iostream>
#include<fstream>

double g(double x){
    return std::cos(5*x-1)*std::exp(-x*x);
}

int main(){
	int N = 50;
	pp::vector x(N), y(N);
	for(int k=0;k<N;k++){
		x[k] = -1.0 + 2.0*k/(N-1);
		y[k] = g(x[k]);
	}

	int n_hidden = 8;
	pp::ann net(n_hidden);

	double C0 = 0;
	for(int k=0;k<N;k++){ double r = net.response(x[k])-y[k]; C0 += r*r; }
	std::cout << "Cost function before training:" << C0 << "\n";

	net.train(x,y);

	double C1 = 0;
	for(int k=0;k<N;k++){ double r = net.response(x[k])-y[k]; C1 += r*r; }
	std::cout << "Cost function after training: " << C1 << "\n";

	std::ofstream tout("anntest.dat");
	int M = 400;
	for(int k=0;k<M+1;k++){
		double xv = -1.0 + 2.0*k/M;
		tout << xv << " " << net.response(xv) << " " << net.deriv(xv) << " " << net.deriv2(xv) << " " << net.integ(xv) << "\n";
	}
	tout.close();

	return 0;
}