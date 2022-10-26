#include <iostream>
#include <cmath>
#include "ex1.h"


// Recursive factorial evaluation for the error estimation
double factorial(double n)
{
    if (n == 0){
       return 1;
    }
    return n * factorial(n - 1);
}


// Taylor approximation of the sine function
double sinTaylor(int N, double x)
{

    //check and return x if N = 0 to no divide through 0
    if (N == 0) {
        return x;
    }
    // Initialize temporary variable
    double temp;

    // Initialize current result variable res as the right part of the innermost bracket (1 - res)
    double res = (x*x)/((2*N)*(2*N+1));

    // Evaluate the result using horners scheme. Start from N and decrease
    for (int i=N; i > 1 ; i--){
        // Temp values evaluates the current innermost bracket (1-res)
        temp = 1-res;

        // Multiply temp value (current solution of the horner scheme so far) with the right term of the next bracket
        res =  temp*x*x/((2*i-1)*(2*i-2));

    }

    // Multiply with x as sine Taylor approximation starts with x (see equation in documentation)
    return x*(1-res);
}

//Taylor approximation of the cosine function
double cosTaylor(int N, double x)
{

     //check and return 1 if N = 0 to no divide through 0
    if (N == 0) {
        return 1;
    }

    // Initialize temporary variable
    double temp;

    // Initialize current result variable res as the right part of the innermost bracket (1 - res)
    double res = x*x/((2*N)*(2*N-1));

    // Evaluate the result using horners scheme. Start from N-1 and decrease
    for (int i=N-1; i >= 1; i--){
        // Temp values evaluates the current innermost bracket (1-res)
        temp = 1-res;

        // Multiply temp value (current solution of the horner scheme so far) with the right term of the next bracket
        res = temp*(x*x)/((2*i)*(2*i-1));

    }

    // Return evaluation of outermost bracket (1-res)
    return 1-res;
}


//Prints error for the Taylor approximations of sine and cosine for different N and x
void error()
{
    //set array sequences with x and N values
    double x_s[] = {-1, 1,2, 3, 5 ,10}; //
    int N_s[] = {1, 3 , 6, 10};

    int num_N = sizeof(N_s)/sizeof(N_s[0]);
    int num_x = sizeof(x_s)/sizeof(x_s[0]);

    //iterate over different x_s
    for (int j = 0; j < num_x; j++){
        std::cout << "---------------------------" << std::endl;
        std::cout << "For x=" << x_s[j] << ":" << std::endl;
        //iterate over number of Ns
        for (int i = 0; i< num_N; i++ ){

            // Calculating the n+1 term of the sinus Taylor approximation to check if it bound the error
            double sin_error_bound =  std::abs((1/factorial(2*N_s[i]+1))*(pow(x_s[j], 2*N_s[i]+1)));


            // Calculating the n+1 term of the cosinus Taylor approximation to check if it bound the error
            double cos_error_bound =  std::abs((1/factorial(2*N_s[i]))*(pow(x_s[j], 2*N_s[i])));

            // Calculate absolute error value
            double err_sin = std::abs(sin(x_s[j])-sinTaylor(N_s[i],x_s[j]));
            double err_cos = std::abs(cos(x_s[j])-cosTaylor(N_s[i],x_s[j]));

            // Printing out the errors when using the Taylor approximation and the estimated error bound of the n+1 term
            std::cout << "N=" << N_s[i] << ", x=" << x_s[j] << ",   error sin: " << err_sin << ",   n+1 term:" << sin_error_bound << std::endl;
            std::cout << "N=" << N_s[i] << ", x=" << x_s[j] << ",   error cos: " << err_cos << ",   n+1 term:" << cos_error_bound << std::endl;
        }
    }
}
