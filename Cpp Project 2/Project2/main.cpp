#include <iostream>
#include <cmath>

#include "matrix.hpp"
using namespace std;
#include "r8lib.h"
#include "r8mat_expm1.h"

//approximate exponential of real number
double myexp(double x, double tol=1e-10){

    double exp_n = 1; // set first component to n=0
    int n = 1; // This is used for displaying number of iterations used for appoximation
    double err = 10000;  // CHANGE

    //store previous components to avoid computational expense
    double prev_val = exp_n;

    //iterate until tolerance is reached
    while (err > tol) {

        //calculate next summand n by using previous summand (n-1)
        prev_val = (prev_val*x)/n;

        //add new component to approximation series
        exp_n += prev_val;

        // Measure error by measuring absolute difference between the approximated exponentials between iterations
        //this is the absolute value of the last summand added to the series
        err = abs(prev_val);
        n +=1 ;
    }
    cout << "number of iterations used: " << n << " with tolerance: " << tol<<endl;
    return exp_n;
}


// Compute matrix exponential with series up to a given tolerance
Matrix matexp(Matrix& M, double tol=1e-10){

    //first exponential component is the identity matrix
    Matrix exp_n = Matrix(M.Cols());
    exp_n.fillNumber(0);
    exp_n.fillDiagonal(1);
    double n = 1.0;
    double err = 100000; // CHANGE

    //store previous components to avoid computational expense
    Matrix prev_val = exp_n;

     // iterate until tolerance is reached
    while (err > tol) {

        //compute next summand n with previous summand n-1
        prev_val *= M;
        prev_val *= 1.0/n;

        //update series by new summand
        exp_n += prev_val;

        //The error is here defined as the maximal difference between elements of new and old calculated matrix exponential approximations
        // this is the maximal value of the last summand added to the series
        err = prev_val.maxnorm();
        n +=1.0 ;
    }
    cout << "number of iterations used: " << n<< endl;
    return exp_n;

}


int main(){

    cout << "Executing Task 1" <<endl ;
    double res = myexp(2.0);
    for(int i= -5; i<10; i++)
        cout << "res: " << myexp((double) i) << endl;

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
    double b[]  = {1,-1,-1,1};

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
