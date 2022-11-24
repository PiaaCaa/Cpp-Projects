#include "curvebase.hpp"
#ifndef XVERTICAL_HPP
#define XVERTICAL_HPP

class Xvertical: public Curvebase{
protected:
    double xp(double p); // Parameterised curve in p. Returns x-value for given p
    double yp(double p); // Parameterised curve in p. Returns y-value for given p
    double dxp(double p); // Parameterised curve in p. Returns derivative in x for given p
    double dyp(double p); // Parameterised curve in p. Returns derivative in y for given p


private:
    double xconst; // Parameter that stores the constant x-value of the vertical line

public:
    Xvertical(double y0, double yf, double x0); // Constructor for vertical line going from y0 to yf at x-value = x0
    Xvertical& operator=(const Xvertical& curve); // Copy assignement
    ~Xvertical(){}; // Destructor
    double x(double s); // Returns x value of curve for given arc length parameter s in [0,1]
    double y(double s); // Returns y value of curve for given arc length parameter s in [0,1]

    double Xconst() const {return xconst;}; // Returns the constant x-value of the vertical line

    // .....

};

#endif
