#include <iostream>
#include <cmath>
#include "ex2.h"


// Use Simpsons rule to estimate Integral value
double I(FunctionPointer f, double a, double b){
    return ((b-a)/6)*(f(a) +4*f((a+b)/2)+ f(b));

}

// Use I2  to decrease error value for Integral approximation
double I_2(FunctionPointer f, double a, double b){
    double gamma = (a+b)/2;
    return I(f, a, gamma) + I(f, gamma,b);
}

// Adaptive Simpson Estimation
double ASI(FunctionPointer f, double a, double  b, double tol){
    double I1 =  I(f, a, b);
    double I2 = I_2(f, a, b);
    double errest = std::abs(I1-I2);
    if (errest < 15*tol){
        return I2;
    }
    return ASI(f, a, (a+b)/2, tol/2) + ASI(f, (a+b)/2, b, tol/2);
}

