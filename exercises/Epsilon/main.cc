#include<iostream>
#include<cmath>
#include<limits>
#include "comp.h"

int main(){
    std::cout << "machine epsilon for types float, double and long double" << std::endl;
    
    float f = 1.0f;
    while((float) (1.0f+f) != 1.0f){f/=2.0f;} f*=2.0f;
    std::cout << "float eps: " << f << std::endl;

    double d = 1.0;
    while((double) (1.0+d) != 1.0){d/=2.0;} d*=2.0;
    std::cout << "double eps: " << d << std::endl;

    long double ld = 1.0L;
    while ((long double) (1.0L+ld) != 1.0L){ld/=2.0L;} ld*=2.0L;
    std::cout << "long double eps: " << ld << std::endl;

    std::cout << "machine epsilon from my system" << std::endl;

    std::cout << "float eps: " << std::numeric_limits<float>::epsilon() << std::endl;
    std::cout << "double eps: " << std::numeric_limits<double>::epsilon() << std::endl;
    std::cout << "long double eps: " << std::numeric_limits<long double>::epsilon() << std::endl;

    std::cout << "machine epsilon from theory" << std::endl;

    std::cout << "float eps: " << std::pow(2, -23) << std::endl;
    std::cout << "double eps: " << std::pow(2, -52) << std::endl;

    std::cout << "non-commutativity of addition for double" << std::endl;

    double epsilon = std::numeric_limits<double>::epsilon();
    double tiny = epsilon/2;
    double a = 1+tiny+tiny;
    double b = tiny+tiny+1;
    std::cout << "tiny = epsilon/2: " << tiny << std::endl;
    std::cout << "a = 1+tiny+tiny: " << a << std::endl;
    std::cout << "b = tiny+tiny+1: " << b << std::endl;

    std::cout << "a == b: " << (a==b ? "true" : "false") << std::endl;
    std::cout << "a > 1: " << (a>1 ? "true" : "false") << std::endl;
    std::cout << "b > 1: " << (b>1 ? "true" : "false") << std::endl; 

    std::cout << "comparing doubles via == and approx" << std::endl;
    double d1 = 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1;
    double d2 = 8*0.1;

    std::cout << "d1 == d2: " << (d1==d2 ? "true" : "false") << std::endl;
    std::cout << "d1 approx d2: " << (comp::approx(d1, d2, 10*epsilon, 10*epsilon) ? "true" : "false") << std::endl;
}

