#include <iostream>
#include <cmath>

#include "matrix.hpp"
using namespace std;
#include "r8lib.h"
#include "r8mat_expm1.h"

//approximate exponential of number
double myexp(double x, double tol=1e-10){
    double exp_n = 1;
    int n = 1;
    double err = 10000;  // CHANGE

    //store previous components to avoid computational expense
    double prev_val = exp_n;
    double sum_comp;

    //DISCUSSION: how do you measure accuracy?
    // DO THIS: Or does this mean the difference between the summands?
    while (err > tol) {
        //exp_n += pow(x, n)/factorial(n);

        sum_comp = (prev_val*x)/n;
        prev_val = sum_comp;

        exp_n += sum_comp;

        //measure accuracy like this?
        // CHANGE
        err = abs(exp_n- exp(x));
        n +=1 ;
    }
    cout << "number of iterations used: " << n<< endl;
    return exp_n;
}



Matrix matexp(Matrix& M, double tol=1e-10){
    Matrix exp_n = Matrix(M.Cols());
    exp_n.fillNumber(0);
    exp_n.fillDiagonal(1);
    double n = 1.0;
    double err = 100000; // CHANGE

    //store previous components to avoid computational expense
    Matrix prev_val = exp_n;
    // Matrix sum_comp(M.Cols());

    //DISCUSSION: how do you measure accuracy?
    // DO THIS: Or does this mean the difference between the summands?
    while (err > tol) {
        //exp_n += pow(x, n)/factorial(n);

        prev_val *= M;
        prev_val *= 1.0/n;

        cout << "Prev_val: " << endl;
        prev_val.printMatrix();

        Matrix exp_n_old =exp_n;
        exp_n += prev_val;

        exp_n_old *= (-1);
        exp_n_old += exp_n;

        cout << "Difference: " << endl;
        exp_n_old.printMatrix();

        err = exp_n_old.maxnorm();
        cout << "Maximumsnorm: " << err << endl;
        // Maximumsnorm der Differenz beider Matrizen
        n +=1.0 ;
    }
    cout << "number of iterations used: " << n<< endl;
    return exp_n;

}



int main(){

    cout << "Executing Task 1" <<endl ;
    double res = myexp(2.0);

    // Compare with exp function


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

    cout << "A norm:"<< A.maxnorm() << endl;
    double a[]  = {1.0,2.0,3.0,4.0, 5.0};
    double b[]  = {1,0,0,1};

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

    cout << endl << endl << endl << "----------------------" << endl << endl << endl;
    B.printMatrix();
    matexp(B).printMatrix();
    cout << endl << "------------------------" << endl;

    double* checkres = r8mat_expm1(2, b);

    Matrix checkmat = Matrix(2);
    checkmat.fillMatrix(checkres);
    cout << "Given result: " << endl;
    checkmat.printMatrix();
 return 0;
}
