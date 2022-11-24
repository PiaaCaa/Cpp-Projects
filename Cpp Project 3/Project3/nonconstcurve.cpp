#include <iostream>
#include <cmath>
#include "curvebase.hpp"
#include "nonconstcurve.hpp"

// Constructor
Nonconstcurve::Nonconstcurve(double x0, double xf){
    pmin = x0;
    pmax = xf;

    // Check if x0 or xf is lower and adjust pmin, pmax and rev accordingly
    if(x0 < xf){
        pmin = x0;
        pmax = xf;
        rev = false;
    } else {
        pmin = xf;
        pmax = x0;
        rev = true;
    }

    // Length of the curve
    length = integrate(pmax);
}

// Since the curve described by the exercise changes in x, its x value is equal to the parameter p
double Nonconstcurve::xp(double p){
    return p;
}

// Following xp, its derivative is const = 1
double Nonconstcurve::dxp(double p){
    return 1;
}

// The y-value is given by the equations as shown in the exercise
double Nonconstcurve::yp(double p){
    if(p < -3){
        return 0.5 * ((1)/(1+exp(-3*(p+6)))); // first equation
    } else{
        return 0.5 * (1/(1+exp(3*p))); // second equation
    }
}

// Following yp, the derivatives of the equations can be implemented
double Nonconstcurve::dyp(double p){
    if(p < -3){
        return (1.5 * exp(-3*(p+6)))/((exp(-3*(p+6))+1) * (exp(-3*(p+6))+1)); // first derivative of equation
    } else{
        return (-1.5 * exp(3*p))/((exp(3*p)+1) * (exp(3*p)+1)); // second derivative of equation
    }
}
