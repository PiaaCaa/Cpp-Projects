#include "curvebase.hpp"
#ifndef YHORIZONTAL_HPP
#define YHORIZONTAL_HPP

class Yhorizontal: public Curvebase{
protected:
    double xp(double p); // Parameterised curve in p. Returns x-value for given p
    double yp(double p); // Parameterised curve in p. Returns y-value for given p
    double dxp(double p); // Parameterised curve in p. Returns derivative in x for given p
    double dyp(double p); // Parameterised curve in p. Returns derivative in y for given p


private:
    double yconst; // Parameter that stores the constant y-value of the horizontal line

public:
    Yhorizontal(double x0, double xf, double y0); // Constructor for horizontal line going from x0 to xf at y-value = y0
    Yhorizontal& operator=(const Yhorizontal& curve); // Copy assignement
    ~Yhorizontal(){}; // Destructor
    double x(double s); // Returns x value of curve for given arc length parameter s in [0,1]
    double y(double s); // Returns y value of curve for given arc length parameter s in [0,1]

    double Yconst() const {return yconst;}; // Returns the constant y-value of the horizontal line

    // .....

};

#endif
