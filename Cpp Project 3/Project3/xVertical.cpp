
#include <iostream>
#include <cmath>
#include "curvebase.hpp"
#include "xvertical.hpp"


Xvertical::Xvertical(double y0, double yf, double x0){
    pmin = y0;
    pmax = yf;
    xconst = x0;
    rev = false;
    length = yf - y0;
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
    double p = pmin + s*length;
    return xp(p);
}

double Xvertical::y(double s){
    double p = pmin + s*length;
    return yp(p);
}
