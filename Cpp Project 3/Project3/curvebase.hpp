#ifndef MATRIX_HPP
#define MATRIX_HPP

class Curvebase{
protected:
    double pmin;  // a
    double pmax;  // b
    bool rev;
    double length;

    // ....

    virtual double xp(double p) = 0;
    virtual double yp(double p) = 0;
    virtual double dxp(double p) = 0;
    virtual double dyp(double p) = 0;

    double integrate(double p); // arc length integral

    // .....

public:
    Curvebase(); // Constructor
    double x(double s);
    double y(double s);
    // .....

};

#endif
