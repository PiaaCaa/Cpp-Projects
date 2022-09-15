#include <iostream>
#include <cmath>

#include "ex1.h"
#include "ex2.h"

int main(){

    std::cout<<"Executing exercise 1" << std::endl;
    double res_sin = sinTaylor(8, 3.14/2) ;
    std::cout<< "result sin:" << res_sin;

    double res_cos = cosTaylor(8, 3.14/2) ;
    std::cout<< "result cos:" << res_cos;

    error();

    std::cout<<"Executing exercise 2" << std::endl;

    double tol [] = {0.01, 0.001, 0.0001};

    for (int i = 0; i < 3; i++){
        std::cout<<"tol: " << tol[i]  << " result: " << ASI(-1, 1, tol[i]) <<  std::endl;
    }
    return 0;
}


