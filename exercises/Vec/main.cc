#include "vec.h"
#include <iostream>
#include<vector>

int main() {
    std::cout<<"two constructors are going to be called shortly..."<<std::endl;
    pp::vec<int> v1(9,9,9);
    pp::vec<int> v2(-1,-1,-1);

    std::cout<<"calling friend operator"<<std::endl;
    std::cout<<"v1: "<<v1<<std::endl;
    std::cout<<"v2: "<<v2<<std::endl;

    std::cout<<"calling operator+ and one destructor"<<std::endl;
    pp::vec<int> v3 = v1 + v2;
    std::cout<<"v3: "<<v3<<std::endl;

    std::cout<<"calling operator*"<<std::endl;
    pp::vec<int> v4 = 2 * v3;
    std::cout<<"v4: "<<v4<<std::endl;

    std::cout<<"two constructors are going to be called shortly..."<<std::endl;
    pp::vec<double> v5(2.5,2.5,2.5);
    pp::vec<double> v6(-3.5,-3.5,-3.5);

    std::cout<<"calling friend operator"<<std::endl;
    std::cout<<"v5: "<<v5<<std::endl;
    std::cout<<"v6: "<<v6<<std::endl;

    std::cout<<"calling operator+ and one destructor"<<std::endl;
    pp::vec<double> v7 = v5 + v6;
    std::cout<<"v7: "<<v7<<std::endl;

    std::cout<<"calling operator*"<<std::endl;
    pp::vec<double> v8 = 2 * v7;
    std::cout<<"v8: "<<v8<<std::endl;

    std::cout<<"eight destructors are going to be called shortly..."<<std::endl;

}
