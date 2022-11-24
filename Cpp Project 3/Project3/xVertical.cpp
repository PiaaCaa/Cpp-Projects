
#include <iostream>
#include <cmath>
#include "curvebase.hpp"
#include "xvertical.hpp"


// Constructor for vertical line
Xvertical::Xvertical(double y0, double yf, double x0){

    xconst = x0;

    // Check if y0 or yf is lower and adjust pmin, pmax and rev accordingly
    if(y0 < yf){
        rev = false;
        pmin = y0;
        pmax = yf;
    } else {
        rev = true;
        pmin = yf;
        pmax = y0;
    }

    // Length of the curve
    length = abs(yf - y0);
}


// Assign operator
Xvertical& Xvertical::operator=(const Xvertical& curve){
    if(this != &curve){
        pmin = curve.Pmin();
        pmax = curve.Pmax();
        rev = curve.Rev();
        length = curve.Length();
        xconst = curve.Xconst();
    }
    return *this;
}



// Since it is a straight vertical line, the x-value is constant
double Xvertical::xp(double p){
    return xconst;
}

// Following xp, its derivative is 0
double Xvertical::dxp(double p){
    return 0;
}

// Since it is a straight vertical line, the y-value is equal to p
double Xvertical::yp(double p){
    return p;
}

// Following yp, its derivative is const = 1
double Xvertical::dyp(double p){
    return 1;
}

double Xvertical::x(double s){
    double p;
    // Since it is a straight line, p can be obtained analytically using the length --> no newton method needed
    if (rev) p = pmax - s*length;
    else p = pmin + s*length;
    return xp(p);
}

double Xvertical::y(double s){
    double p;
    // Since it is a straight line, p can be obtained analytically using the length --> no newton method needed
    if (rev) p = pmax - s*length;
    else p = pmin + s*length;
    return yp(p);
}
