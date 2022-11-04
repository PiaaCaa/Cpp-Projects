#include "curvebase.hpp"
#ifndef YHORIZONTAL_HPP
#define YHORIZONTAL_HPP

class Yhorizontal: public Curvebase{
protected:
    double xp(double p);
    double yp(double p);
    double dxp(double p);
    double dyp(double p);

    //double integrate(double p); // arc length integral

private:
    double yconst;

public:
    Yhorizontal(double x0, double xf, double y0); // Constructor
    ~Yhorizontal(){};
    double x(double s);
    double y(double s);

    void printYhorizontal();


    // .....

};

#endif
