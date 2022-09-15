#include <iostream>
#include <cmath>


double f(double x){
    return (1 + sin(exp(3*x)));
}

double I(double a, double b){
    return ((b-a)/6)*(f(a) +4*f((a+b)/2)+ f(b));

}

double I_2(double a, double b){
    double gamma = (a+b)/2;
    return I(a, gamma) + I(gamma,b);
}

//TODO insert function as parameter
double ASI(double a, double  b, double tol){
    double I1 =  I(a, b);
    double I2 = I_2(a, b);
    double errest = std::abs(I1-I2);
    if (errest < 15*tol){
        return I2;
    }
    return ASI(a, (a+b)/2, tol/2) + ASI((a+b)/2, b, tol/2);
}



//int main () {

    //TODO for loop over tolerances
    //double res = ASI(-1, 1, tol);
    //#todo compare results to matlab function
//    return 0;
//}
