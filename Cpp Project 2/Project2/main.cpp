#include <iostream>
#include <cmath>

#include "matrix.hpp"
using namespace std;
#include "r8lib.h"
#include "r8mat_expm1.h"


// Approximate exponential of real number
double myexp(double x, double tol=1e-10){

    double exp_n = 1; // set first component to n=0
    int n = 1; // This is used for displaying number of iterations used for appoximation
    double err = tol*2;

    //store previous components to avoid computational expense
    double prev_val = exp_n;

    //iterate until tolerance is reached
    while (err > tol) {

        //calculate next summand n by using previous summand (n-1)
        prev_val = (prev_val*x)/n;

        //add new component to approximation series
        exp_n += prev_val;

        if (isinf(exp_n)){
            cout << "inf broken!" << endl;
            break;
        }

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
    double err = tol*2;


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
    Matrix T1 = Matrix(3);
    Matrix T2 = Matrix(2);
    Matrix T3 = Matrix(7);
    Matrix T4 = Matrix(5);
    Matrix T5 = Matrix(4);

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

    // Filling matrices
    T1.fillMatrix(v1, (sizeof(v1) / sizeof(*v1)));
    T2.fillMatrix(v2, (sizeof(v2) / sizeof(*v2)));
    T3.fillMatrix(v3, (sizeof(v3) / sizeof(*v3)));
    T4.fillMatrix(v4, (sizeof(v4) / sizeof(*v4)));
    T5.fillMatrix(v5, (sizeof(v5) / sizeof(*v5)));

    Matrix matrices[5]= {T1,T2,T3,T4,T5};
    double* vectors[5] = {v1,v2,v3,v4,v5};
    int sizes[5] = {9,4,49,25,16};


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
