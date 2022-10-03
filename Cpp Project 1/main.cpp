#include <iostream>
#include <cmath>

#include "ex1.h"
#include "ex2.h"

// example function given for Task 2
double func(double x){
    return (1 + sin(exp(3*x)));
}

// Main function to execute Task 1 and 2
int main(){

    // Task 1
    std::cout<<"Executing Task 1" << std::endl;

    // function to calculate the estimated error
    error();

    std::cout << std::endl;
    std::cout << "--------------------------" << std::endl;
    std::cout << std::endl;

    // Task 2
    std::cout << "Executing Task 2" << std::endl;
    std::cout << std::endl;

    // MATLAB result for integration using integral() function with absolute tolerance
    // of 1e-8 rounded to 5 digits
    double matlab_res = 2.50081;

    std::cout << "Using MATLAB's integration method with an absolute tolerance of 1e-8 results in: " << matlab_res << std::endl;

    // Print Integral estimate for different tolerances
    double tol [] = {0.01, 0.001, 0.0001};
    for (int i = 0; i < 3; i++){
        // ASI function takes left border, right, border, tolerance and a function which takes a double and returns a double
        double asi_res =    ASI(&func,-1, 1, tol[i]);
        // Comparing ASI result to MATLAB result
        std::cout<<"Tolerance: " << tol[i]  << ", ASI result: " << asi_res <<  ", Difference to MATLAB result: " << std::abs(matlab_res - asi_res)<< std::endl;
    }

    return 0;
}


