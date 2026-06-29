#define _USE_MATH_DEFINES
#include <cmath>
#include <cstdio>
#include <functional>
#include <utility>
#include <limits>
#include <numbers>
#include <string>
#include <vector>
#include<iostream>
#include<fstream>

static long ncalls = 0;

//The error estimation is AI generated

std::pair<double,double> integrate(const std::function<double(double)>& f, double a, double b,double acc = 1e-3, double eps = 1e-3,double f2 = std::numeric_limits<double>::quiet_NaN(),double f3 = std::numeric_limits<double>::quiet_NaN()) {
    double h = b - a;

    if (std::isnan(f2)){
        f2 = f(a+2*h/6); ncalls++;
        f3 = f(a+4*h/6); ncalls++;
    }
    double f1 = f(a+1*h/6); ncalls++;
    double f4 = f(a+5*h/6); ncalls++;
 
    double Q = (2*f1+f2+f3+2*f4)/6*h;
    double q = (f1+f2+f3+f4)/4*h;
 
    double err = std::fabs(Q-q);
    double tol = acc+eps*std::fabs(Q);
 

    //This was proposed by AI
    if (err < tol || h < 1e-30 || a == b || !std::isfinite(Q)) {
        return {std::isfinite(Q) ? Q : 0.0, err};
    }
 
    double mid = (a + b) / 2;

    double acc2 = acc / std::sqrt(2.0);

    auto [Q1, err1] = integrate(f, a, mid, acc2, eps, f1, f2);
    auto [Q2, err2] = integrate(f, mid, b, acc2, eps, f3, f4);

    return {Q1 + Q2, std::sqrt(err1*err1 + err2*err2)};
}

std::pair<double,double> integrate_cc(const std::function<double(double)>& f, double a, double b,double acc = 1e-3, double eps = 1e-3){
    auto cc = [&f, a, b](double phi){
        double x = (a+b)/2+(b-a)/2*std::cos(phi);
        //This was proposed by AI after running into problems with the examples
        if (x <= a || x >= b) return 0.0; 
        return f(x)*std::sin(phi)*(b-a)/2;
        
    };
    return integrate(cc, 0, M_PI, acc, eps);
}


double testfunction1(double x){
    return std::sqrt(x);
}

double testfunction2(double x){
    return 1/std::sqrt(x);
}

double testfunction3(double x){
    return 1/std::sqrt(1-x*x);
}

double testfunction4(double x){
    return std::log(x)/std::sqrt(x);
}

double testfunction5(double x){
    return std::exp(-x);
}

double testfunction6(double x){
    return std::exp(-x*x);
}

double erf_part_1(double z){
    return std::exp(-z*z);
}

double erf_part_2(double z, double t){
    return std::exp(-(z+(1-t)/t)*(z+(1-t)/t))/t/t;
}

double erf_calc(double z, double acc, double eps){
    if(z<0){
        return -erf_calc(-z, acc, eps);
    }
    if(z<=1){;
        return 2.0/std::sqrt(M_PI)*integrate(erf_part_1,0,z,acc,eps).first;
    }
    if(1<z){
        auto erf_part_2z = [z](double t){return erf_part_2(z, t); };
        return 1-2.0/std::sqrt(M_PI)*integrate(erf_part_2z,0,1,acc,eps).first;
    }
    return 0;
}

std::pair<double,double> integrate_inf(const std::function<double(double)>& f, double a, double b, double acc = 1e-3, double eps = 1e-3){
    //This was proposed by AI
    bool a_inf = std::isinf(a);
    bool b_inf = std::isinf(b);
    //
    if (!a_inf && !b_inf){
        return integrate_cc(f, a, b, acc, eps);
    }
 
    if (!a_inf && b_inf){
        auto g = [&f, a](double t){
            double x = a + t/(1-t);
            return f(x) / ((1-t)*(1-t));
        };
        return integrate_cc(g, 0.0, 1.0, acc, eps);
    }
 
    if (a_inf && !b_inf){
        auto g = [&f, b](double t){
            double x = b + t/(1+t);
            return f(x) / ((1+t)*(1+t));
        };
        return integrate_cc(g, -1.0, 0.0, acc, eps);
    }

    auto g = [&f](double t){
        double x = t/(1-t*t);
        double y = (1+t*t)/((1-t*t)*(1-t*t));
        return f(x) * y;
    };
    return integrate_cc(g, -1.0, 1.0, acc, eps);
}

int main(){
    double acc_test = 1e-8;
    double eps_test = 1e-8;

    std::cout << "We run a few test cases:" << std::endl;

    ncalls = 0;
    auto [I1, errest1] = integrate(testfunction1,0,1,acc_test,eps_test);
    double acc_I1 = I1-2.0/3.0;

    std::cout << "∫dx√(x) from 0 to 1 calculated to " << I1 << " with accuracy " << acc_I1 << " (estimated " << errest1 << ") < 1e-8 and it took ncalls = " << ncalls << std::endl;

    ncalls = 0;
    auto [I2, errest2] = integrate(testfunction2,0,1,acc_test,eps_test);
    double acc_I2 = I2-2.0;

    std::cout << "∫dx1/√(x) from 0 to 1 calculated to " << I2 << " with accuracy " << acc_I2 << " (estimated " << errest2 << ") < 1e-8 and it took ncalls = " << ncalls << std::endl;

    ncalls = 0;
    auto [I3, errest3] = integrate(testfunction3,0,1,acc_test,eps_test);
    double acc_I3 = I3-M_PI/2;

    std::cout << "∫dx/√(1-x*x) from 0 to 1 calculated to " << I3 << " with accuracy " << acc_I3 << " (estimated " << errest3 << ") < 1e-8 and it took ncalls = " << ncalls << std::endl;

    ncalls = 0;
    auto [I4, errest4] = integrate(testfunction4,0,1,acc_test,eps_test);
    double acc_I4 = I4 + 4;

    std::cout << "∫dxln(x)/√(x) from 0 to 1 calculated to " << I4 << " with accuracy " << acc_I4 << " (estimated " << errest4 << ") < 1e-8 and it took ncalls = " << ncalls << std::endl;

    std::ofstream out("erf.dat");
    for(int i=-100; i<=100; i++){
        out << i/50.0 << " " << erf_calc(i/50.0,acc_test,0) << "\n";
    }
    out.close();

    std::cout << "We calculate erf(x) compare it to the integrated erf(x) function and check its accuracy. This can be seen in erf.pdf and erf1.pdf." << std::endl;

    double erf1_exact = 0.84270079294971486934;

    std::ofstream out2("erf1.dat");
    for(int i=1; i<=10; i++){
        out2 << std::pow(10,-i) << " " << std::fabs(erf1_exact - erf_calc(1,std::pow(10,-i),0)) << "\n";
    }
    out2.close();

    std::cout << "We test the Clenshaw-Curtis variable transformation for two examples from before" << std::endl;

    ncalls = 0;
    auto [I2cc, errest2cc] = integrate_cc(testfunction2,0,1,acc_test,eps_test);
    double acc_I2cc = I2cc-2.0;

    std::cout << "∫dx1/√(x) from 0 to 1 calculated to " << I2cc << " with accuracy " << acc_I2cc << " (estimated " << errest2cc << ") < 1e-8 and it took ncalls = " << ncalls << std::endl;

    ncalls = 0;
    auto [I4cc, errest4cc] = integrate_cc(testfunction4,0,1,acc_test,eps_test);
    double acc_I4cc = I4cc + 4;

    std::cout << "∫dxln(x)/√(x) from 0 to 1 calculated to " << I4cc << " with accuracy " << acc_I4cc << " (estimated " << errest4cc << ") !< 1e-8 and it took ncalls = " << ncalls << std::endl;

    double inf = std::numeric_limits<double>::infinity();

    ncalls = 0;
    auto [I5, errest5] = integrate_inf(testfunction5,0,inf,acc_test,eps_test);
    double acc_I5 = I5-1;

    std::cout << "∫dxe(-x) from 0 to inf calculated to " << I5 << " with accuracy " << acc_I5 << " (estimated " << errest5 << ") < 1e-8 and it took ncalls = " << ncalls << std::endl;

    ncalls = 0;
    auto [I6, errest6] = integrate_inf(testfunction6,-inf,0,acc_test,eps_test);
    double acc_I6 = I6 - 0.5*std::sqrt(M_PI);

    std::cout << "∫dxe(-x*x) from -inf to 0 calculated to " << I6 << " with accuracy " << acc_I6 << " (estimated " << errest6 << ") < 1e-8 and it took ncalls = " << ncalls << std::endl;

    ncalls = 0;
    auto [I7, errest7] = integrate_inf(testfunction6,-inf,inf,acc_test,eps_test);
    double acc_I7 = I7 - std::sqrt(M_PI);

    std::cout << "∫dxe(-x*x) from -inf to inf calculated to " << I7 << " with accuracy " << acc_I7 << " (estimated " << errest7 << ") < 1e-8 and it took ncalls = " << ncalls << std::endl;

    std::cout << "Investigating error estimate quality across difficult integrals:\n";
    std::cout << std::scientific;

    //These recursion are AI generated out of convenience.
    
    struct Case { std::string name; std::function<double(double)> f; double a, b; double exact; bool use_cc; };
    std::vector<Case> cases = {
        {"sqrt(x)",        testfunction1, 0, 1, 2.0/3.0,        false},
        {"1/sqrt(x)",      testfunction2, 0, 1, 2.0,            false},
        {"1/sqrt(1-x^2)",  testfunction3, 0, 1, M_PI/2,         false},
        {"ln(x)/sqrt(x)",  testfunction4, 0, 1, -4.0,           false},
        {"1/sqrt(x) [CC]", testfunction2, 0, 1, 2.0,            true},
        {"ln(x)/sqrt(x) [CC]", testfunction4, 0, 1, -4.0,       true},
    };

    for (auto& c : cases) {
        std::cout << "  " << c.name << ":\n";
        for (double tol : {1e-2, 1e-4, 1e-6, 1e-8, 1e-10}) {
            ncalls = 0;
            auto [Q, est] = c.use_cc ? integrate_cc(c.f, c.a, c.b, tol, tol)
                                      : integrate(c.f, c.a, c.b, tol, tol);
            double trueerr = std::fabs(Q - c.exact);
            std::cout << "    tol=" << tol
                      << "  true_err=" << trueerr
                      << "  est_err="  << est
                      << "  ratio(est/true)=" << (trueerr > 0 ? est/trueerr : 0.0)
                      << "  ncalls=" << ncalls << "\n";
        }
    }
    std::cout << std::defaultfloat;

    return 0;
}