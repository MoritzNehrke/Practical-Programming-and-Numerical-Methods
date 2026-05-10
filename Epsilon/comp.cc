#include<cmath>
#include<limits>
#include "comp.h"
#include<algorithm>

namespace comp{

    bool approx(double a, double b, double acc, double eps){
        double diff = std::abs(a-b);
        if(diff <= acc) return true;
        double max_ab = std::max(std::abs(a), std::abs(b));
        if(diff <= max_ab*eps) return true;
        return false;
    }
}
