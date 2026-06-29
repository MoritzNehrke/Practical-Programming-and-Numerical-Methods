#include<iostream>
#include<cmath> 
#include<cstdio>
#include"sfuns.h"
#include<complex>

using complex=std::complex<double>;
constexpr double pi=3.1415926535897932384626433832795;
constexpr double E=2.7182818284590452353602874713527;
constexpr complex I=complex(0,1);

int main(){
    std::cout << "log(I)=" << std::log(I) << "\n";
    std::cout << "I^I=" << std::pow(I,I) << "\n";
    std::cout << "pi^I=" << std::pow(pi,I) << "\n";
    std::cout << "E^I=" << std::pow(E,I) << "\n";

    for(double x=1;x<=9;x+=1)
        std::cout << "fgamma(" << x << ")=" << sfuns::fgamma(x) << "\t gamma(" << x << ")=" << std::tgamma(x) << "\n";
    
    std::cout << "fgamma(-1)=" << sfuns::fgamma(-1) << "\t gamma(-1)=" << std::tgamma(-1) << "\n";

    for(double x=1;x<=9;x+=1)
        std::cout << "lnfgamma(" << x << ")=" << sfuns::lnfgamma(x) << "\t lngamma(" << x << ")=" << std::lgamma(x) << "\n";
}