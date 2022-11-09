#include "curvebase.hpp"
#ifndef NONCONSTCURVE_HPP
#define NONCONSTCURVE_HPP

class Nonconstcurve: public Curvebase{
protected:
    double xp(double p);
    double yp(double p);
    double dxp(double p);
    double dyp(double p);

    //double integrate(double p); // arc length integral


public:
    Nonconstcurve(double x0, double xf); // Constructor
    Nonconstcurve& operator=(const Nonconstcurve& curve);
    ~Nonconstcurve(){};

    void printNonconstcurve();


    // .....

};

#endif
