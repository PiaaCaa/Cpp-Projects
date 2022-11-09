#include <iostream>
#include <cmath>
#include "curvebase.hpp"
#include "nonconstcurve.hpp"


Nonconstcurve::Nonconstcurve(double x0, double xf){
    pmin = x0; // QUESTION?
    pmax = xf; // QUESTION?

    if(x0 < xf){
        pmin = x0;
        pmax = xf;
        rev = false;
    } else {
        pmin = xf;
        pmax = x0;
        rev = true;
    }

    length = integrate(pmax);
}


void Nonconstcurve::printNonconstcurve(){
    std::cout << pmin << pmax << std::endl;
    std::cout << rev << length << std::endl;
}


double Nonconstcurve::xp(double p){
    return p;
}

double Nonconstcurve::dxp(double p){
    return 1;
}

double Nonconstcurve::yp(double p){
    if(p < -3){
        return 0.5 * ((1)/(1+exp(-3*(p+6)))); // first equation
    } else{
        return 0.5 * (1/(1+exp(3*p))); // second equation
    }
}

double Nonconstcurve::dyp(double p){
    if(p < -3){
        return (1.5 * exp(-3*(p+6)))/((exp(-3*(p+6))+1) * (exp(-3*(p+6))+1)); // first derivative of equation
    } else{
        return (-1.5 * exp(3*p))/((exp(3*p)+1) * (exp(3*p)+1)); // second derivative of equation
    }
}
