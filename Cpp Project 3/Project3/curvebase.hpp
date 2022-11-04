#ifndef CURVEBASE_HPP
#define CURVEBASE_HPP

typedef double(*FunctionPointer)(double);

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
    double funcintegrate(double q); // function to integrate using ASI
    double ASI(double a, double  b, double tol);
    double I_2(double a, double b);
    double I(double a, double b);

    double newton(double s, double p0, double tol);
    double f(double p, double s);


    // .....

public:
    Curvebase(); // Constructor
    ~Curvebase(); // Destructor
    //Curvebase(Functionpointer f); // Constructor
    double x(double s);
    double y(double s);
    // .....

};

#endif
