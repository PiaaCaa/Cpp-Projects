#include <iostream>
#include <cmath>

#include "curvebase.hpp"
using namespace std;


//Constructor
Curvebase::Curvebase(){
    //pmin = 0;
    //pmax = 1;
    //rev = false;
    //length = 2;
    // constructor

//Constructor
// Curvebase::Curvebase(Functionpointer x){
    // constructor
}

Curvebase& Curvebase::operator=(const Curvebase& curve){
    if(this != &curve){
        pmin = curve.Pmin();
        pmax = curve.Pmax();
        rev = curve.Rev();
        length = curve.Length();
    }
    return *this;
}


Curvebase::~Curvebase(){};


//Curvebase::Curvebase(Functionpointer x){
//    pmin = 0;
//    pmax = 1;
//    rev = false;
//    length = 2;
//}

double Curvebase::integrate(double p){
    double lp = 0;
    lp = ASI(pmin, p,0.01);
    return lp;
}


double Curvebase::funcintegrate(double q){
    return sqrt(pow(dxp(q),2.0) + pow(dyp(q),2.0));
}


double Curvebase::x(double s){
    //if(false) exit(-1);
    //return -1.0;
    double p;
    if(rev) p = newton(1.0-s,(pmin+pmax)/2.0,0.01);
    else p = newton(s,(pmin+pmax)/2.0,0.01);
    return xp(p);

}


double Curvebase::y(double s){
    double p;
    if(rev) p = newton(1.0-s,(pmin+pmax)/2.0,0.01);
    else p = newton(s,(pmin+pmax)/2.0,0.01);
    return yp(p);//double p = newton(yp,dyp,s,(pmin+pmax)/2,e-2);
    //return yp(p);
}


double Curvebase::newton(double s, double p0, double tol){
    double res=p0;
    while(abs(f(res,s)) > tol){
        res = res - f(res,s)/funcintegrate(res);
    }
    return res;
}


double Curvebase::f(double p, double s){
    return integrate(p) - s*length;
}


//double f(){
//    double res;
//    res = c + integrate();
//}


// Use Simpsons rule to estimate Integral value
double Curvebase::I(double a, double b){
    return ((b-a)/6)*(funcintegrate(a) +4*funcintegrate((a+b)/2)+ funcintegrate(b));

}

// Use I2  to decrease error value for Integral approximation
double Curvebase::I_2(double a, double b){
    double gamma = (a+b)/2;
    return I(a, gamma) + I(gamma,b);
}

// Adaptive Simpson Estimation
double Curvebase::ASI(double a, double  b, double tol){
    double I1 =  I(a, b);
    double I2 = I_2(a, b);
    double errest = std::abs(I1-I2);
    if (errest < 15*tol){
        return I2;
    }
    return ASI(a, (a+b)/2, tol/2) + ASI((a+b)/2, b, tol/2);
}
