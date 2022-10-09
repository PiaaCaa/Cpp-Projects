#include <iostream>
#include <cmath>

#include "matrix.hpp"
using namespace std;

//approximate exponential of number
double myexp(double x, double tol=1e-10){
    double exp_n = 1;
    int n = 1;
    double err = 20;

    //store previous components to avoid computational expense
    double prev_val = 1;
    double sum_comp;

    //DISCUSSION: how do you measure accuracy?
    // Or does this mean the difference between the summands?
    while (err > tol) {
        //exp_n += pow(x, n)/factorial(n);

        sum_comp = (prev_val*x)/n;
        prev_val = sum_comp;
        exp_n += sum_comp;

        //measure accuracy like this?
        err = abs(exp_n- exp(x));
        n +=1 ;
    }
    cout << "number of iterations used: " << n<< endl;
    return exp_n;
}






int main(){

    cout << "Executing Task 1" <<endl ;
    double res = myexp(2.0);


    cout << "Executing Task 2"<< endl;

    Matrix A = Matrix(2);
    Matrix B = Matrix(A); // Observation: If B changes A changes. Should this be the case?
    Matrix C = Matrix(4);
    Matrix D = Matrix(3);

    C = A;
    cout << "C cols:" << C.Cols()<< endl;
    C.printMatrix();

    A.fillNumber(1.0);
    B.fillNumber(2.0);
    C.fillNumber(3.0);

    cout << "A, B, C" << endl;
    A.printMatrix();
    B.printMatrix();
    C.printMatrix();

    A *=C;
    B +=C;
    cout << "A, B, C" << endl;
    A.printMatrix();
    B.printMatrix();
    C.printMatrix();

    cout << "A norm:"<< A.norm() << endl;
    double a[]  = {1.0,2.0,3.0,4.0, 5.0};
    double b[]  = {5.0,6.0,7.0,8.0};

    A.fillMatrix(a);
    B.fillMatrix(b);
    A.printMatrix();
    B.printMatrix();

    A +=B;
    A.printMatrix();

    A *=B;
    A.printMatrix();

    double aa = 3.0;
    A *= aa;
    A.printMatrix();
 return 0;
}
