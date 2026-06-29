#include<iostream>
#define _USE_MATH_DEFINES
#include<cmath>
#include<functional>
#include<vector>
#include<tuple>
#include"linearalgebra.h"
#include<fstream>
#include<sstream>

double rosenbrock(const pp::vector& v){
    return (1-v[0])*(1-v[0]) + 100*(v[1]-v[0]*v[0])*(v[1]-v[0]*v[0]);
}

pp::vector rosenbrock_grad(const pp::vector& v){
	double x=v[0], y=v[1];
	pp::vector g(2);
	g[0] = -2.0*(1.0-x) - 400.0*x*(y-x*x);
	g[1] = 200.0*(y-x*x);
	return g;
}

double himmelblau(const pp::vector& v){
    return (v[0]*v[0] + v[1] - 11)*(v[0]*v[0] + v[1] - 11) + (v[0] + v[1]*v[1] - 7)*(v[0] + v[1]*v[1] - 7);
}

pp::vector himmelblau_grad(const pp::vector& v){
    double x=v[0], y=v[1];
	pp::vector g(2);
	g[0] = 4*x*(x*x + y - 11) + 2*(x + y*y - 7);
	g[1] = 2*(x*x + y - 11) + 4*y*(x + y*y - 7);
	return g;
}

double breit_wigner(const double E, const double m, const double Gamma, const double A){
    return A / ( (E-m)*(E-m) + Gamma*Gamma/4.0 );
}

double D(const pp::vector& p, const pp::vector signal, const pp::vector error, const pp::vector energy){
    double m = p[0], Gamma = p[1], A = p[2];
    double sum = 0;
    int n = signal.size();
    for(int i = 0; i<n; i++){
        double Fi = breit_wigner(energy[i], m, Gamma, A);
        double d = (Fi - signal[i])/error[i];
        sum += d*d;
    }
    return sum;
}

int main(){

    //A

    std::cout << "We find an extremum to the Rosenbrock function starting at (0,0)" << std::endl;
    {
		pp::vector x0{0.0,0.0};
		auto [min, steps] = pp::newton_minimize(rosenbrock,x0,1e-5);
		std::cout<<"(x,y) =  (" << min[0] << "," << min[1] << ") in steps = " << steps << std::endl;;
		std::cout<<"f(x,y) at extremum = " << rosenbrock(min) << std::endl;
        std::cout<<"grad(f) at extremum = (" << rosenbrock_grad(min)[0] << "," <<rosenbrock_grad(min)[1] << ")" << std::endl;
    }

    std::cout << "We find an extremum to the Rosenbrock function starting at (10,10)" << std::endl;
    {
		pp::vector x0{10.0,10.0};
		auto [min, steps] = pp::newton_minimize(rosenbrock,x0,1e-5);
		std::cout<<"(x,y) =  (" << min[0] << "," << min[1] << ") in steps = " << steps << std::endl;;
		std::cout<<"f(x,y) at extremum = " << rosenbrock(min) << std::endl;
        std::cout<<"grad(f) at extremum = (" << rosenbrock_grad(min)[0] << "," <<rosenbrock_grad(min)[1] << ")" << std::endl;
    }
    

    //We can nicely see that newton_minimize times out for the starting point (0,0) unlike seen in the roots homework

    std::cout << "We find an extremum to the Himmelblau function starting at (0,0)" << std::endl;
    {
		pp::vector x0{0.0,0.0};
		auto [min, steps] = pp::newton_minimize(himmelblau,x0,1e-5);
		std::cout<<"(x,y) =  (" << min[0] << "," << min[1] << ") in steps = " << steps << std::endl;;
		std::cout<<"f(x,y) at extremum = " << himmelblau(min) << std::endl;
        std::cout<<"grad(f) at extremum = (" << himmelblau_grad(min)[0] << "," <<himmelblau_grad(min)[1] << ")" << std::endl;
    }

    std::cout << "We find an extremum to the Himmelblau function starting at (5,5)" << std::endl;
    {
		pp::vector x0{5.0,5.0};
		auto [min, steps] = pp::newton_minimize(himmelblau,x0,1e-5);
		std::cout<<"(x,y) =  (" << min[0] << "," << min[1] << ") in steps = " << steps << std::endl;;
		std::cout<<"f(x,y) at extremum = " << himmelblau(min) << std::endl;
        std::cout<<"grad(f) at extremum = (" << himmelblau_grad(min)[0] << "," <<himmelblau_grad(min)[1] << ")" << std::endl;
    }
    std::cout << "We find an extremum to the Himmelblau function starting at (-5,5)" << std::endl;
    {
		pp::vector x0{-5.0,5.0};
		auto [min, steps] = pp::newton_minimize(himmelblau,x0,1e-5);
		std::cout<<"(x,y) =  (" << min[0] << "," << min[1] << ") in steps = " << steps << std::endl;;
		std::cout<<"f(x,y) at extremum = " << himmelblau(min) << std::endl;
        std::cout<<"grad(f) at extremum = (" << himmelblau_grad(min)[0] << "," <<himmelblau_grad(min)[1] << ")" << std::endl;
    }
    std::cout << "We find an extremum to the Himmelblau function starting at (-5,-5)" << std::endl;
    {
		pp::vector x0{-5.0,-5.0};
		auto [min, steps] = pp::newton_minimize(himmelblau,x0,1e-5);
		std::cout<<"(x,y) =  (" << min[0] << "," << min[1] << ") in steps = " << steps << std::endl;;
		std::cout<<"f(x,y) at extremum = " << himmelblau(min) << std::endl;
        std::cout<<"grad(f) at extremum = (" << himmelblau_grad(min)[0] << "," <<himmelblau_grad(min)[1] << ")" << std::endl;
    }
    std::cout << "We find an extremum to the Himmelblau function starting at (5,-5)" << std::endl;
    {
		pp::vector x0{5.0,-5.0};
		auto [min, steps] = pp::newton_minimize(himmelblau,x0,1e-5);
		std::cout<<"(x,y) =  (" << min[0] << "," << min[1] << ") in steps = " << steps << std::endl;;
		std::cout<<"f(x,y) at extremum = " << himmelblau(min) << std::endl;
        std::cout<<"grad(f) at extremum = (" << himmelblau_grad(min)[0] << "," <<himmelblau_grad(min)[1] << ")" << std::endl;
    }

    //B


    //AI generated out of convenience
    pp::vector energy, signal, error;
    double x,y,z;
    std::string line;
    while (std::getline(std::cin, line)) {
        std::istringstream iss(line);
        if (iss >> x >> y >> z) {
            energy.data.push_back(x); signal.data.push_back(y); error.data.push_back(z);
        }
    }
    //

    pp::vector p0{125.0, 5.0, 25};

    auto Dfit = [&](const pp::vector& p){ return D(p, signal, error, energy); };
    auto [popt, steps] = pp::newton_minimize(Dfit, p0, 1e-6);
 
    double m = popt[0];
    double Gamma = std::abs(popt[1]);
    double A = popt[2];

    std::cout << "Breit-Wigner fit to Higgs boson resonance data in steps = " << steps << std::endl;
    std::cout << "Fitted Higgs boson mass m = " << m << " GeV" << std::endl;
    std::cout << "Fitted width Gamma = " << Gamma << " GeV" << std::endl;
    std::cout << "Fitted scale factor A = " << A << std::endl;
    std::cout << "Steps needed steps = " << steps << std::endl;

    std::cout << "The comparison between fit and measurement can be seen in higgs.pdf." << std::endl;

    std::ofstream out("higgsfit.dat");
    int n = energy.size();
    double Emin = energy[0], Emax = energy[n-1];
    int grid = 500;
    for(int i=0; i<grid; i++){
        double E = Emin + (Emax - Emin)*i/grid;
        double bw = breit_wigner(E, m, Gamma, A);
        out << E << " " << bw << "\n";
    }
    out.close();

    //A

    std::cout << "We find an extremum to the Rosenbrock function starting at (0,0)" << std::endl;
    {
		pp::vector x0{0.0,0.0};
		auto [min, steps] = pp::newton_minimize(rosenbrock,x0,1e-5,pp::gradient_cd);
		std::cout<<"(x,y) =  (" << min[0] << "," << min[1] << ") in steps = " << steps << std::endl;;
		std::cout<<"f(x,y) at extremum = " << rosenbrock(min) << std::endl;
        std::cout<<"grad(f) at extremum = (" << rosenbrock_grad(min)[0] << "," <<rosenbrock_grad(min)[1] << ")" << std::endl;
    }

    std::cout << "We find an extremum to the Rosenbrock function starting at (10,10)" << std::endl;
    {
		pp::vector x0{10.0,10.0};
		auto [min, steps] = pp::newton_minimize(rosenbrock,x0,1e-5,pp::gradient_cd);
		std::cout<<"(x,y) =  (" << min[0] << "," << min[1] << ") in steps = " << steps << std::endl;;
		std::cout<<"f(x,y) at extremum = " << rosenbrock(min) << std::endl;
        std::cout<<"grad(f) at extremum = (" << rosenbrock_grad(min)[0] << "," <<rosenbrock_grad(min)[1] << ")" << std::endl;
    }
    

    //We can nicely see that newton_minimize times out for the starting point (0,0) unlike seen in the roots homework

    std::cout << "We find an extremum to the Himmelblau function starting at (0,0)" << std::endl;
    {
		pp::vector x0{0.0,0.0};
		auto [min, steps] = pp::newton_minimize(himmelblau,x0,1e-5,pp::gradient_cd,pp::hessian_cd);
		std::cout<<"(x,y) =  (" << min[0] << "," << min[1] << ") in steps = " << steps << std::endl;;
		std::cout<<"f(x,y) at extremum = " << himmelblau(min) << std::endl;
        std::cout<<"grad(f) at extremum = (" << himmelblau_grad(min)[0] << "," <<himmelblau_grad(min)[1] << ")" << std::endl;
    }

    std::cout << "We find an extremum to the Himmelblau function starting at (5,5)" << std::endl;
    {
		pp::vector x0{5.0,5.0};
		auto [min, steps] = pp::newton_minimize(himmelblau,x0,1e-5,pp::gradient_cd,pp::hessian_cd);
		std::cout<<"(x,y) =  (" << min[0] << "," << min[1] << ") in steps = " << steps << std::endl;;
		std::cout<<"f(x,y) at extremum = " << himmelblau(min) << std::endl;
        std::cout<<"grad(f) at extremum = (" << himmelblau_grad(min)[0] << "," <<himmelblau_grad(min)[1] << ")" << std::endl;
    }
    std::cout << "We find an extremum to the Himmelblau function starting at (-5,5)" << std::endl;
    {
		pp::vector x0{-5.0,5.0};
		auto [min, steps] = pp::newton_minimize(himmelblau,x0,1e-5,pp::gradient_cd,pp::hessian_cd);
		std::cout<<"(x,y) =  (" << min[0] << "," << min[1] << ") in steps = " << steps << std::endl;;
		std::cout<<"f(x,y) at extremum = " << himmelblau(min) << std::endl;
        std::cout<<"grad(f) at extremum = (" << himmelblau_grad(min)[0] << "," <<himmelblau_grad(min)[1] << ")" << std::endl;
    }
    std::cout << "We find an extremum to the Himmelblau function starting at (-5,-5)" << std::endl;
    {
		pp::vector x0{-5.0,-5.0};
		auto [min, steps] = pp::newton_minimize(himmelblau,x0,1e-5,pp::gradient_cd,pp::hessian_cd);
		std::cout<<"(x,y) =  (" << min[0] << "," << min[1] << ") in steps = " << steps << std::endl;;
		std::cout<<"f(x,y) at extremum = " << himmelblau(min) << std::endl;
        std::cout<<"grad(f) at extremum = (" << himmelblau_grad(min)[0] << "," <<himmelblau_grad(min)[1] << ")" << std::endl;
    }
    std::cout << "We find an extremum to the Himmelblau function starting at (5,-5)" << std::endl;
    {
		pp::vector x0{5.0,-5.0};
		auto [min, steps] = pp::newton_minimize(himmelblau,x0,1e-5,pp::gradient_cd,pp::hessian_cd);
		std::cout<<"(x,y) =  (" << min[0] << "," << min[1] << ") in steps = " << steps << std::endl;;
		std::cout<<"f(x,y) at extremum = " << himmelblau(min) << std::endl;
        std::cout<<"grad(f) at extremum = (" << himmelblau_grad(min)[0] << "," <<himmelblau_grad(min)[1] << ")" << std::endl;
    }

    std::cout << "We can see that central difference achieves generally better results." << std::endl;

    return 0;
}