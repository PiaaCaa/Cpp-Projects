#include <iostream>
#include <cmath>
#include "curvebase.hpp"
#include "yhorizontal.hpp"


Yhorizontal::Yhorizontal(double x0, double xf, double y0){
    pmin = x0;
    pmax = xf;
    yconst = y0;
    rev = false;
    length = xf - x0;
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
    double p = pmin + s*length;
    return xp(p);
}

double Yhorizontal::y(double s){
    double p = pmin + s*length;
    return yp(p);
}
