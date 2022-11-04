#include <iostream>
#include <cmath>
#include "curvebase.hpp"
#include "nonconstcurve.hpp"


Nonconstcurve::Nonconstcurve(double x0, double xf){
    pmin = x0; // QUESTION?
    pmax = xf; // QUESTION?

    rev = false;
    length = integrate(xf); // QUESTION?
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
        return -1; // first equation
    } else{
        return -1; // second equation
    }
}

double Nonconstcurve::dyp(double p){
    if(p < -3){
        return -1; // first derivative of equation
    } else{
        return -1; // second derivative of equation
    }
}
