#define _USE_MATH_DEFINES
#include<cmath>
#include<random>
#include<iostream>
#include<string>
#include"linearalgebra.h"
#include"ft.h"

//AI generated out of convenience

int main(int argc, char const *argv[]){

	int N = 256;
	std::string algo = "dft";

	for(int i=1; i<argc; i++){
		std::string arg = argv[i];
		if(arg == "-size" && i+1 < argc) N = std::stoi(argv[++i]);
		if(arg == "-algo" && i+1 < argc) algo = argv[++i];
	}

	double noise_strength = 0.3;
	std::mt19937 gen(1234);
	std::normal_distribution<double> noise(0.0, noise_strength);

	pp::vector y(N);
	for(int n=0; n<N; n++) y[n] = std::cos(2*M_PI*n/N) + noise(gen);

	ft::cvec yc = ft::to_complex(y);

	if(algo == "fft") ft::fft(yc);
	else              ft::dft(yc);

	return 0;
}