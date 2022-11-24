#ifndef CURVEBASE_HPP
#define CURVEBASE_HPP

typedef double(*FunctionPointer)(double);

class Curvebase{
protected:
    double pmin;  // a --> start value for p of the parameterised curve
    double pmax;  // b --> end value for p of the parameterised curve
    bool rev; // Boolean that indicates if the curve is reversed
    double length; // Length of the curve

    // ....

    virtual double xp(double p) = 0; // Parameterised curve in p. Returns x-value for given p
    virtual double yp(double p) = 0; // Parameterised curve in p. Returns y-value for given p
    virtual double dxp(double p) = 0; // Parameterised curve in p. Returns derivative in x for given p
    virtual double dyp(double p) = 0; // Parameterised curve in p. Returns derivative in y for given p

    double integrate(double p); // arc length integral
    double funcintegrate(double q); // function to integrate using ASI

    double ASI(double a, double  b, double tol); // ASI numerical integration
    double I_2(double a, double b); // Help function for ASI
    double I(double a, double b); // Help function for ASI

    double newton(double s, double p0, double tol); // Newton method
    double f(double p, double s); // Function to find a root on using newton --> the root gives the parameter p based on given s.


    // .....

public:
    Curvebase(); // Constructor
    ~Curvebase(); // Destructor

    double x(double s); // Returns x value of curve for given arc length parameter s in [0,1]
    double y(double s); // Returns y value of curve for given arc length parameter s in [0,1]

    double Pmin() const {return pmin;}; // Returns the minimum value p of the parameterised curve
    double Pmax() const {return pmax;}; // Returns the maximum value p of the parameterised curve
    bool Rev() const {return rev;}; // Returns if the curve is reversed or not
    double Length() const {return length;}; // Returns the length of the curve

    void printCurve(); // Prints the relevant information of the curve using cout

    // .....

};

#endif
