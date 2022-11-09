#include "curvebase.hpp"
#ifndef XVERTICAL_HPP
#define XVERTICAL_HPP

class Xvertical: public Curvebase{
protected:
    double xp(double p);
    double yp(double p);
    double dxp(double p);
    double dyp(double p);

    //double integrate(double p); // arc length integral

private:
    double xconst;

public:
    Xvertical(double y0, double yf, double x0); // Constructor for a vertical line at x=x0 going from y0 to yf
    Xvertical& operator=(const Xvertical& curve);
    ~Xvertical(){};
    double x(double s);
    double y(double s);

    double Xconst() const {return xconst;};

    void printXvertical();


    // .....

};

#endif
