#include <iostream>
#include <cmath>
#include "curvebase.hpp"
#include "yhorizontal.hpp"


Yhorizontal::Yhorizontal(double x0, double xf, double y0){

    yconst = y0;

    if(x0 < xf){
        rev=false;
        pmin = x0;
        pmax = xf;
    } else {
        rev=true;
        pmin = xf;
        pmax = x0;
    }

    length = abs(xf - x0);
}

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

void Yhorizontal::printYhorizontal(){
    std::cout << pmin << pmax << std::endl;
    std::cout << rev << length << std::endl;
}


double Yhorizontal::xp(double p){
    return p;
}

double Yhorizontal::dxp(double p){
    return 1;
}

double Yhorizontal::yp(double p){
    return yconst;
}

double Yhorizontal::dyp(double p){
    return 0;
}

double Yhorizontal::x(double s){
    double p;
    if (rev) p = pmax - s*length; // ????
    else p = pmin + s*length;
    return xp(p);
}

double Yhorizontal::y(double s){
    double p;
    if (rev) p = pmax - s*length; // ????
    else p = pmin + s*length;
    return yp(p);
}
