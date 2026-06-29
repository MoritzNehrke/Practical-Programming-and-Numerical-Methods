#include<cmath>
#include"sfuns.h"
#include<limits>

namespace sfuns{
    constexpr double pi = 3.1415926535897932384626433832795;
    constexpr double NaN = std::numeric_limits<double>::quiet_NaN();
    double fgamma(double x){
        if(x<=0) return NaN;
        if(x<9) return fgamma(x+1)/x;
        double lnfgamma = x*std::log(x+1/(12*x-1/(10*x)))-x+std::log(2*pi/x)/2;
        return std::exp(lnfgamma);
    }
    double lnfgamma(double x){
        if(x<=0) return NaN;
        if(x<9) return lnfgamma(x+1)-std::log(x);
        return x*std::log(x+1/(12*x-1/(10*x)))-x+std::log(2*pi/x)/2;
    }
}