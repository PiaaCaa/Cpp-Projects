
#include <iostream>
#include <cmath>
#include "curvebase.hpp"
#include "xvertical.hpp"


Xvertical::Xvertical(double y0, double yf, double x0){
    pmin = y0;
    pmax = yf;
    xconst = x0;

    if(y0 < yf){
        rev = false;
        pmin = y0;
        pmax = yf;
    } else {
        rev = true;
        pmin = yf;
        pmax = y0;
    }

    length = abs(yf - y0);
}


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

void Xvertical::printXvertical(){
    std::cout << pmin << pmax << std::endl;
    std::cout << rev << length << std::endl;
}


double Xvertical::xp(double p){
    return xconst;
}

double Xvertical::dxp(double p){
    return 0;
}

double Xvertical::yp(double p){
    return p;
}

double Xvertical::dyp(double p){
    return 1;
}

double Xvertical::x(double s){
    double p;
    if (rev) p = pmax - s*length; // ????
    else p = pmin + s*length;
    return xp(p);
}

double Xvertical::y(double s){
    double p;
    if (rev) p = pmax - s*length; // ????
    else p = pmin + s*length;
    return yp(p);
}
