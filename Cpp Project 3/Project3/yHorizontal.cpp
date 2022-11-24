#include <iostream>
#include <cmath>
#include "curvebase.hpp"
#include "yhorizontal.hpp"


// Constructor for horizontal line
Yhorizontal::Yhorizontal(double x0, double xf, double y0){

    yconst = y0;

    // Check if x0 or xf is lower and adjust pmin, pmax and rev accordingly
    if(x0 < xf){
        rev=false;
        pmin = x0;
        pmax = xf;
    } else {
        rev=true;
        pmin = xf;
        pmax = x0;
    }

    // Length of curve
    length = abs(xf - x0);
}

// Assign operator
Yhorizontal& Yhorizontal::operator=(const Yhorizontal& curve){
    if(this != &curve){
        pmin = curve.Pmin();
        pmax = curve.Pmax();
        rev = curve.Rev();
        length = curve.Length();
        yconst = curve.Yconst();
    }
    return *this;
}

// Since it is a straight horizontal line, the x-value is equal to the parameter p
double Yhorizontal::xp(double p){
    return p;
}

// Following xp, its derivative is constant = 1
double Yhorizontal::dxp(double p){
    return 1;
}

// Since it is a straight horizontal line, the y-value is constant
double Yhorizontal::yp(double p){
    return yconst;
}

// Following yp, its derivative is 0
double Yhorizontal::dyp(double p){
    return 0;
}

// Return x-value for given arc length s in [0,1]
double Yhorizontal::x(double s){
    double p;
    // Since it is a straight line, p can be obtained analytically using the length --> no newton method needed
    if (rev) p = pmax - s*length;
    else p = pmin + s*length;
    return xp(p);
}

// Return y-value for given arc length s in [0,1]
double Yhorizontal::y(double s){
    double p;
    // Since it is a straight line, p can be obtained analytically using the length --> no newton method needed
    if (rev) p = pmax - s*length;
    else p = pmin + s*length;
    return yp(p);
}
