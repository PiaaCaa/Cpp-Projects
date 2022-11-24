#include "curvebase.hpp"
#ifndef NONCONSTCURVE_HPP
#define NONCONSTCURVE_HPP

class Nonconstcurve: public Curvebase{
protected:
    double xp(double p); // Parameterised curve in p. Returns x-value for given p
    double yp(double p); // Parameterised curve in p. Returns y-value for given p
    double dxp(double p); // Parameterised curve in p. Returns derivative in x for given p
    double dyp(double p); // Parameterised curve in p. Returns derivative in y for given p


public:
    Nonconstcurve(double x0, double xf); // Constructor of a curve described by the two equations given by the exercise. The y-translations is always y0=0
    Nonconstcurve& operator=(const Nonconstcurve& curve); // Copy assignement
    ~Nonconstcurve(){}; // Destructor


    // .....

};

#endif
