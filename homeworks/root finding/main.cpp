#include<iostream>
#define _USE_MATH_DEFINES
#include<cmath>
#include<functional>
#include<vector>
#include<tuple>
#include"linearalgebra.h"
#include<fstream>

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

pp::vector schrodinger(double E, double r, const pp::vector& y){
	pp::vector dydr(2);
	dydr[0] = y[1];
	dydr[1] = -2.0*(E + 1.0/r)*y[0];
	return dydr;
}
 
std::tuple<pp::vector,pp::matrix> shoot(double E, double rmin, double rmax){
	pp::vector yinit(2);
	yinit[0] = rmin - rmin*rmin;
	yinit[1] = 1.0 - 2.0*rmin;
 
	std::function<pp::vector(double,pp::vector)> F = [E](double r, pp::vector y){
		return schrodinger(E,r,y);
	};
 
	return pp::driver(F, rmin, rmax, yinit, 0.01, 1e-6, 1e-6);
}

int main(){

    //A

    std::cout << "We find an extremum to the Rosenbrock function starting at (0,0)" << std::endl;
    {
		pp::vector x0{0.0,0.0};
		pp::vector root = pp::newton(rosenbrock_grad,x0,1e-10,1e-3,2000);
		std::cout<<"(x,y) =  (" << root[0] << "," << root[1] << ")" << std::endl;;
		std::cout<<"f(x,y) at extremum = " << rosenbrock(root) << std::endl;
        std::cout<<"grad(f) at extremum = (" << rosenbrock_grad(root)[0] << "," <<rosenbrock_grad(root)[1] << ")" << std::endl;
    }
	std::cout << "We find an extremum to the Rosenbrock function starting at (10,10)" << std::endl;
    {
		pp::vector x0{10.0,10.0};
		pp::vector root = pp::newton(rosenbrock_grad,x0,1e-10,1e-3,2000); //needed to increase the step size
		std::cout<<"(x,y) =  (" << root[0] << "," << root[1] << ")" << std::endl;;
		std::cout<<"f(x,y) at extremum = " << rosenbrock(root) << std::endl;
        std::cout<<"grad(f) at extremum = (" << rosenbrock_grad(root)[0] << "," <<rosenbrock_grad(root)[1] << ")" << std::endl;
    }

    std::cout << "We find an extremum to the Himmelblau function starting at (0,0)" << std::endl;
    {
		pp::vector x0{0.0,0.0};
		pp::vector root = pp::newton(himmelblau_grad,x0,1e-10,1e-3,200);
		std::cout<<"(x,y) =  (" << root[0] << "," << root[1] << ")" << std::endl;;
		std::cout<<"f(x,y) at extremum = " << himmelblau(root) << std::endl;
        std::cout<<"grad(f) at extremum = (" << himmelblau_grad(root)[0] << "," <<himmelblau_grad(root)[1] << ")" << std::endl;
    }

    std::cout << "We find an extremum to the Himmelblau function starting at (5,5)" << std::endl;
    {
		pp::vector x0{5.0,5.0};
		pp::vector root = pp::newton(himmelblau_grad,x0,1e-10,1e-3,200);
		std::cout<<"(x,y) =  (" << root[0] << "," << root[1] << ")" << std::endl;;
		std::cout<<"f(x,y) at extremum = " << himmelblau(root) << std::endl;
        std::cout<<"grad(f) at extremum = (" << himmelblau_grad(root)[0] << "," <<himmelblau_grad(root)[1] << ")" << std::endl;
    }

    std::cout << "We find an extremum to the Himmelblau function starting at (-5,5)" << std::endl;
    {
		pp::vector x0{-5.0,5.0};
		pp::vector root = pp::newton(himmelblau_grad,x0,1e-10,1e-3,200);
		std::cout<<"(x,y) =  (" << root[0] << "," << root[1] << ")" << std::endl;;
		std::cout<<"f(x,y) at extremum = " << himmelblau(root) << std::endl;
        std::cout<<"grad(f) at extremum = (" << himmelblau_grad(root)[0] << "," <<himmelblau_grad(root)[1] << ")" << std::endl;
    }

    std::cout << "We find an extremum to the Himmelblau function starting at (-5,-5)" << std::endl;
    {
		pp::vector x0{-5.0,-5.0};
		pp::vector root = pp::newton(himmelblau_grad,x0,1e-10,1e-3,200);
		std::cout<<"(x,y) =  (" << root[0] << "," << root[1] << ")" << std::endl;;
		std::cout<<"f(x,y) at extremum = " << himmelblau(root) << std::endl;
        std::cout<<"grad(f) at extremum = (" << himmelblau_grad(root)[0] << "," <<himmelblau_grad(root)[1] << ")" << std::endl;
    }

    std::cout << "We find an extremum to the Himmelblau function starting at (5,-5)" << std::endl;
    {
		pp::vector x0{5.0,-5.0};
		pp::vector root = pp::newton(himmelblau_grad,x0,1e-10,1e-3,200);
		std::cout<<"(x,y) =  (" << root[0] << "," << root[1] << ")" << std::endl;;
		std::cout<<"f(x,y) at extremum = " << himmelblau(root) << std::endl;
        std::cout<<"grad(f) at extremum = (" << himmelblau_grad(root)[0] << "," <<himmelblau_grad(root)[1] << ")" << std::endl;
    }

    //B

    double rmin = 1e-4;
	double rmax = 8.0;
 
	std::function<pp::vector(const pp::vector&)> M = [&](const pp::vector& E){
		pp::vector out(1);
		auto [rlist, ylist] = shoot(E[0], rmin, rmax);
        int last = ylist.size2()-1;
        out[0] = ylist[last][0];
		return out;
	};
 
	pp::vector E0{-1.0}; 
	pp::vector dxE{1e-6};
	pp::vector Eroot = pp::newton(M, E0, 1e-10, 1e-3, 200, dxE);
	double E_0 = Eroot[0];
 
	std::cout<<"Lowest bound-state energy E_0 = "<< E_0 << std::endl;
	
	auto [rlist, ylist] = shoot(E_0, rmin, rmax);
	int n = rlist.size();

	std::ofstream out("wavefunction.dat");
	for(int i=0;i<n;i++){
		double r = rlist[i];
		double f_num = ylist[i][0];
		out << r << " " << f_num << "\n";
	}
	out.close();

    std::cout << "The wavefunction of E_0 compared to the exact solution can be found in wavefunction.pdf." << std::endl;

    //C

    std::cout << "We implemented the Good Broyden method, the quadratic interpolation line-search and try it on the Himmelblau function" << std::endl;
    
    std::cout << "We find an extremum to the Himmelblau function starting at (0,0)" << std::endl;
    {
		pp::vector x0{0.0,0.0};
		pp::vector root = pp::broyden(himmelblau_grad,x0,1e-10,1e-3,200);
		std::cout<<"(x,y) =  (" << root[0] << "," << root[1] << ")" << std::endl;;
		std::cout<<"f(x,y) at extremum = " << himmelblau(root) << std::endl;
        std::cout<<"grad(f) at extremum = (" << himmelblau_grad(root)[0] << "," <<himmelblau_grad(root)[1] << ")" << std::endl;
    }

    std::cout << "We find an extremum to the Himmelblau function starting at (5,5)" << std::endl;
    {
		pp::vector x0{5.0,5.0};
		pp::vector root = pp::broyden(himmelblau_grad,x0,1e-10,1e-3,200);
		std::cout<<"(x,y) =  (" << root[0] << "," << root[1] << ")" << std::endl;;
		std::cout<<"f(x,y) at extremum = " << himmelblau(root) << std::endl;
        std::cout<<"grad(f) at extremum = (" << himmelblau_grad(root)[0] << "," <<himmelblau_grad(root)[1] << ")" << std::endl;
    }

    std::cout << "We find an extremum to the Himmelblau function starting at (-5,5)" << std::endl;
    {
		pp::vector x0{-5.0,5.0};
		pp::vector root = pp::broyden(himmelblau_grad,x0,1e-10,1e-3,200);
		std::cout<<"(x,y) =  (" << root[0] << "," << root[1] << ")" << std::endl;;
		std::cout<<"f(x,y) at extremum = " << himmelblau(root) << std::endl;
        std::cout<<"grad(f) at extremum = (" << himmelblau_grad(root)[0] << "," <<himmelblau_grad(root)[1] << ")" << std::endl;
    }

    std::cout << "We find an extremum to the Himmelblau function starting at (-5,-5)" << std::endl;
    {
		pp::vector x0{-5.0,-5.0};
		pp::vector root = pp::broyden(himmelblau_grad,x0,1e-10,1e-3,200);
		std::cout<<"(x,y) =  (" << root[0] << "," << root[1] << ")" << std::endl;;
		std::cout<<"f(x,y) at extremum = " << himmelblau(root) << std::endl;
        std::cout<<"grad(f) at extremum = (" << himmelblau_grad(root)[0] << "," <<himmelblau_grad(root)[1] << ")" << std::endl;
    }

    std::cout << "We find an extremum to the Himmelblau function starting at (5,-5)" << std::endl;
    {
		pp::vector x0{5.0,-5.0};
		pp::vector root = pp::broyden(himmelblau_grad,x0,1e-10,1e-3,200);
		std::cout<<"(x,y) =  (" << root[0] << "," << root[1] << ")" << std::endl;;
		std::cout<<"f(x,y) at extremum = " << himmelblau(root) << std::endl;
        std::cout<<"grad(f) at extremum = (" << himmelblau_grad(root)[0] << "," <<himmelblau_grad(root)[1] << ")" << std::endl;
    }


    return 0;
}