#include <iostream>
#include <cmath>

#include "matrix.hpp"
using namespace std;
#include "r8lib.h"
#include "r8mat_expm1.h"


// Approximate exponential of real number
double myexp(double x, double tol=1e-10){

    double exp_n = 1; // set first component to n=0
    int n = 1; // This is used for displaying number of iterations used for approximation
    double err = tol*2; // Set error larger than tolerance to ensure at least one summand of the approximation

    // Store previous components to avoid computational expense
    double prev_val = exp_n;

    // Iterate until tolerance is reached
    while (err > tol) {

        // Calculate next summand n by using previous summand (n-1)
        prev_val = (prev_val*x)/n;

        // Add new component to approximation series
        exp_n += prev_val;

        if (isinf(exp_n)){
            break;
        }

        // Measure error by measuring absolute difference between the approximated exponentials between iterations
        // this is the absolute value of the last summand added to the series
        err = abs(prev_val);
        n +=1 ;
    }
    cout << "number of iterations used: " << n << " with tolerance: " << tol<<endl;
    return exp_n;
}


// Compute matrix exponential with series up to a given tolerance
Matrix matexp(Matrix& M, double tol=1e-10){

    // First exponential component is the identity matrix
    Matrix exp_n = Matrix(M.Cols());
    exp_n.fillNumber(0);
    exp_n.fillDiagonal(1);
    double n = 1.0;
    double err = tol*2;


    // Store previous components to avoid computational expense
    Matrix prev_val = exp_n;

     // Iterate until tolerance is reached
    while (err > tol) {

        // Compute next summand n with previous summand n-1
        prev_val *= M;
        prev_val *= 1.0/n;

        // Update series by new summand
        exp_n += prev_val;

        // The error is here defined as the maximal difference between elements of new and old calculated matrix exponential approximations
        // this is the maximal value of the last summand added to the series
        err = prev_val.maxnorm();

        if (isinf(err))
            break;

        n +=1.0 ;
    }
    cout << "number of iterations used: " << n<< endl;
    return exp_n;

}


int main(){

    cout << "Executing Task 1" << endl << endl;
    double myval; double testval;
    double testvalues[] = {1.0,5.3,-6.2,156.3,13523.74, -47.3};
    for(auto& e : testvalues){
        cout << "---------------------" << endl << "Evaluating e^" << e << endl;
        myval = myexp(e);
        testval = exp(e);
        cout << "res: " << myval << endl;
        cout << "exp function: " << testval << endl;
        cout << "Difference: " << abs(myval - testval) << endl << "---------------------" << endl << endl;
    }



    cout << "Executing Task 2"<< endl;


    cout << endl << endl << endl << "----------------------" << endl << endl << endl;

    // Building Test Matrices

    // Taking exemplary values
    double v1[9] = {1.3,2.4,6.7,-4.2,4.78,12,9.81,0.0,1.0};

    // Matrix with bad condition number and single large value
    double v2[4] = {37, -0.002, 3.4, 0.0345};

    // Large Matrix 7x7 with random big numbers (up to 100)
    double v3[49];
    for (int i=0;i<49;i++){
         v3[i] = rand() % 100;
    }

    // Matrix with random decimal numbers between 0 and -50
    double v4[25];
    for (int i=0;i<25;i++){
         v4[i] = -((double)(rand() % 5000)) / 100;
    }

    // Matrix with random numbers between -5 and 5 with decimals
    double v5[16];
    for (int i=0;i<16;i++){
         v5[i] = (((double)(rand() % 1000)) / 100) - 5;
    }

    // Matrix with random numbers between -25 and 0 with decimals
    double v6[16];
    for (int i=0;i<16;i++){
         v6[i] = -(((double)(rand() % 2500)) / 100);
    }

    // Creating and filling matrices
    Matrix T1 = Matrix(3, v1, (sizeof(v1) / sizeof(*v1)));
    Matrix T2 = Matrix(2, v2, (sizeof(v2) / sizeof(*v2)));
    Matrix T3 = Matrix(7, v3, (sizeof(v3) / sizeof(*v3)));
    Matrix T4 = Matrix(5, v4, (sizeof(v4) / sizeof(*v4)));
    Matrix T5 = Matrix(4, v5, (sizeof(v5) / sizeof(*v5)));
    Matrix T6 = Matrix(4, v6, (sizeof(v6) / sizeof(*v6)));

    Matrix matrices[6]= {T1,T2,T3,T4,T5,T6};
    double* vectors[6] = {v1,v2,v3,v4,v5,v6};
    int sizes[6] = {9,4,49,25,16,16};


    for (int i = 0; i < (sizeof(matrices) / sizeof(*matrices)); i++){

        cout << endl << "------------------------" << endl;
        cout << endl << "Given matrix: " << endl;

        Matrix M = matrices[i];
        double* v = vectors[i];
        M.printMatrix();

        // Calculate exponential with our function
        Matrix expM = matexp(M);
        cout << endl << "Exponential of given matrix: " << endl;
        expM.printMatrix();

        // Checking with given function
        double* checkres = r8mat_expm1(M.Cols(), vectors[i]);
        Matrix checkmat = Matrix(M.Cols());
        checkmat.fillMatrix(checkres, sizes[i]);
        cout << endl << "Given result: " << endl;
        checkmat.printMatrix();

        // Calculating the errors
        checkmat *= -1;
        cout << endl << "Error Matrix: " << endl;
        expM += checkmat;
        expM.printMatrix();

        cout << "------------------------" << endl;

    }

 return 0;
}
