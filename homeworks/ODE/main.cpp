#include<iostream>
#define _USE_MATH_DEFINES
#include<cmath>
#include<functional>
#include<vector>
#include<tuple>
#include"linearalgebra.h"
#include<fstream>



pp::vector harmonic(double /*x*/, pp::vector y){
    pp::vector dydx(2);
    dydx[0] = y[1];
    dydx[1] = -y[0];
    return dydx;
}

pp::vector pend(double /*t*/, pp::vector y){
    pp::vector dydt {y[1], -0.25*y[1]-5.0*std::sin(y[0])};
    return dydt;
}

pp::vector star(double /*phi*/, pp::vector y, double eps){
    pp::vector dydphi {y[1], 1+eps*y[0]*y[0]-y[0]};
    return dydphi;
}

pp::vector threebody(double /*t*/, pp::vector z){
    pp::vector dzdt(12);

    double x[3], y[3];
    for(int i=0;i<3;i++){
        x[i] = z[6+2*i];
        y[i] = z[7+2*i];
    }

    for(int i=0;i<6;i++) dzdt[6+i] = z[i];
 
    for(int i=0;i<3;i++){
        double ax=0, ay=0;
        for(int j=0;j<3;j++){
            if(j!=i){
            double dx = x[j]-x[i];
            double dy = y[j]-y[i];
            double r2 = dx*dx+dy*dy;
            double r3 = r2*std::sqrt(r2);
            ax += dx/r3;
            ay += dy/r3;
            }
        }
        dzdt[2*i]   = ax;
        dzdt[2*i+1] = ay;
    }
 
    return dzdt;
}

int main(){
    
    //A

    std::cout << "We test the algorithm on the simple example u'' = - u with initial conditions u(0) = 1 and u'(0) = 0. The result can be seen in test.pdf." << std::endl;

    double a=0, b=10;
    pp::vector yinit_harm{1.0,0.0};
    auto [xlist_harm,ylist_harm] = pp::driver(harmonic,a,b,yinit_harm,0.125,1e-4,1e-4);

    std::cout<<"steps taken: "<<xlist_harm.size()-1<<"\n";

    std::ofstream out("test.dat");
    for(int i=0; i<xlist_harm.size(); i++){
        out << xlist_harm[i] << " " << ylist_harm[i][0] << " " << ylist_harm[i][1] << "\n";
    }
    out.close();

    std::cout << "We futher test the algorithm for a pendulum with friction. This can be seen in pend.pdf." << std::endl;

    pp::vector yinit_pend {M_PI-0.1, 0.0};
    auto [xlist_pend,ylist_pend] = pp::driver(pend,a,b,yinit_pend,0.125,1e-4,1e-4);

    std::cout<<"steps taken: "<<xlist_pend.size()-1<<"\n";

    std::ofstream out2("pend.dat");
    for(int i=0; i<xlist_pend.size(); i++){
        out2 << xlist_pend[i] << " " << ylist_pend[i][0] << " " << ylist_pend[i][1] << "\n";
    }
    out2.close();

    //B

    std::cout << "We consider the equation of equatorial motion of a planet around a star in General Relativity for: eps = 0.01, u(0) = 1 and u'(0) = 0 found in star1.pdf, eps = 0, u(0) = 1 and u'(0) = -0.5 found in star2.pdf, eps = 0.01, u(0) = 1 and u'(0) = -0.5 found in star1.pdf" << std::endl;

    double a_star = 0, b_star = 100;

    pp::vector yinit_star1 {1, 0.0};
    double epsilon1 = 0.001; //I am using a non-zero epsilon here, because otherwise the stepsize would be to big. I decided against a step-size limit.
    auto star1 = [epsilon1](double phi, pp::vector y){ return star(phi, y, epsilon1); };
    auto [xlist_star1,ylist_star1] = pp::driver(star1,a_star,b_star,yinit_star1,0.125,1e-4,1e-4);

    std::cout<<"steps taken: "<<xlist_star1.size()-1<<"\n";

    std::ofstream out3("star1.dat");
    for(int i=0; i<xlist_star1.size(); i++){
        out3 << xlist_star1[i] << " " << ylist_star1[i][0] << " " << ylist_star1[i][1] << "\n";
    }
    out3.close();

    pp::vector yinit_star2 {1, -0.5};
    double epsilon2 = 0.0; 
    auto star2 = [epsilon2](double phi, pp::vector y){ return star(phi, y, epsilon2); };
    auto [xlist_star2,ylist_star2] = pp::driver(star2,a_star,b_star,yinit_star2,0.125,1e-4,1e-4);

    std::cout<<"steps taken: "<<xlist_star2.size()-1<<"\n";

    std::ofstream out4("star2.dat");
    for(int i=0; i<xlist_star2.size(); i++){
        out4 << xlist_star2[i] << " " << ylist_star2[i][0] << " " << ylist_star2[i][1] << "\n";
    }
    out4.close();

    double epsilon3 = 0.01; 
    auto star3 = [epsilon3](double phi, pp::vector y){ return star(phi, y, epsilon3); };
    auto [xlist_star3,ylist_star3] = pp::driver(star3,a_star,b_star,yinit_star2,0.125,1e-4,1e-4);

    std::cout<<"steps taken: "<<xlist_star3.size()-1<<"\n";

    std::ofstream out5("star3.dat");
    for(int i=0; i<xlist_star3.size(); i++){
        out5 << xlist_star3[i] << " " << ylist_star3[i][0] << " " << ylist_star3[i][1] << "\n";
    }
    out5.close();

    //C

    std::cout << "We will know find a planar periodic solution to the dynamics of a Newtonian gravitational three-body problem. This can be seen in threebody.pdf" << std::endl;

    double x1=0.97000436, y1=-0.24308753;
    double vx3=-0.93240737, vy3=-0.8647314;
 
    pp::vector zinit_3body {-0.5*vx3, -0.5*vy3, -0.5*vx3, -0.5*vy3, vx3, vy3, x1, y1, -x1, -y1, 0.0, 0.0,};
 
    double period = 6.32591398;
    double a3 = 0, b3 = 3*period;
    auto [xlist_3body, ylist_3body] = pp::driver(threebody, a3, b3, zinit_3body, 1e-3, 1e-6, 1e-6);
 
    std::cout<<"steps taken: "<<xlist_3body.size()-1<<"\n";
 
    std::ofstream out6("threebody.dat");
    for(int i=0; i<xlist_3body.size()/100; i++){
        out6 << xlist_3body[100*i];
        for(int k=0;k<12;k++){
            out6 << " " << ylist_3body[100*i][k];
        }
        out6 << "\n";
    }
    out6.close();
 
    return 0;
}