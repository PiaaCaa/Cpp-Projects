#include <iostream>
#include <cmath>

#include "ex1.h"
#include "ex2.h"

// example function for Task 2
double func(double x){
    return (1 + sin(exp(3*x)));
}

//Main function to execute Task 1 and 2
int main(){

    //Task 1
    std::cout<<"Executing Task 1" << std::endl;
    //double res_sin = sinTaylor(8, 3.14/2) ;
    //std::cout<< "result sin:" << res_sin;

    //double res_cos = cosTaylor(8, 3.14/2) ;
    //std::cout<< "result cos:" << res_cos;

    //estimate error
    error();

    std::cout<<"Executing Task 2" << std::endl;

    //Print Integral estimate for different tolerances
    double tol [] = {0.01, 0.001, 0.0001};
    for (int i = 0; i < 3; i++){
        std::cout<<"tol: " << tol[i]  << " result: " << ASI(&func,-1, 1, tol[i]) <<  std::endl;
    }

    return 0;
}


