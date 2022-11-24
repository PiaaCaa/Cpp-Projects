#include <iostream>
#include <cmath>

#include "curvebase.hpp"
using namespace std;


//Constructor
Curvebase::Curvebase(){}

// Destructor
Curvebase::~Curvebase(){}


// Integrate function that integrates funcintegrate from pmin to p using the ASI function
double Curvebase::integrate(double p){
    return ASI(pmin, p,0.01);
}


// Function to integrate / derivative
double Curvebase::funcintegrate(double q){
    return sqrt(pow(dxp(q),2.0) + pow(dyp(q),2.0));
}

// Returns x value for given arc length s in [0,1]
double Curvebase::x(double s){
    double p;
    // Use newton method to find parameter p for given s. Use 1-s for a reversed curve
    if(rev) p = newton(1.0-s,(pmin+pmax)/2.0,0.01);
    else p = newton(s,(pmin+pmax)/2.0,0.01);
    // Return the x value for given parameter p of the parameterised curve
    return xp(p);
}

// Returns y value for given arc length s in [0,1]
double Curvebase::y(double s){
    double p;
    // Use newton method to find parameter p for given s. Use 1-s for a reversed curve
    if(rev) p = newton(1.0-s,(pmin+pmax)/2.0,0.01);
    else p = newton(s,(pmin+pmax)/2.0,0.01);
    // Return the y value for given parameter p of the parameterised curve
    return yp(p);
}


// Newton method with initial guess p0 and tolerance tol
double Curvebase::newton(double s, double p0, double tol){
    double res=p0;
    while(abs(f(res,s)) > tol){
        // Using Newton scheme to find root
        res = res - f(res,s)/funcintegrate(res);
    }
    return res;
}

// Function l(p) - s * l(pmax) that is used to find parameter p
double Curvebase::f(double p, double s){
    return integrate(p) - s*length;
}



// Use Simpsons rule to estimate Integral value
double Curvebase::I(double a, double b){
    return ((b-a)/6)*(funcintegrate(a) +4*funcintegrate((a+b)/2)+ funcintegrate(b));

}

// Use I2  to decrease error value for Integral approximation
double Curvebase::I_2(double a, double b){
    double gamma = (a+b)/2;
    return I(a, gamma) + I(gamma,b);
}

// Adaptive Simpson Estimation
double Curvebase::ASI(double a, double  b, double tol){
    double I1 =  I(a, b);
    double I2 = I_2(a, b);
    double errest = std::abs(I1-I2);
    if (errest < 15*tol){
        return I2;
    }
    return ASI(a, (a+b)/2, tol/2) + ASI((a+b)/2, b, tol/2);
}


// Print parameters using cout
void Curvebase::printCurve(){
    std::cout << pmin << pmax << std::endl;
    std::cout << rev << length << std::endl;
}
