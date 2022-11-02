#include <iostream>
#include <cmath>

#include "matrix.hpp"
using namespace std;


//Constructor for a square matrix with dimensions m x m
Matrix::Matrix(int m){
    rows = m;
    cols = m;

    // Allocate new Memory
    matx = new double*[rows];
    for(int i = 0; i < rows; i++){
        matx[i] = new double[cols];
        for(int j = 0 ; j < cols ; j++){
            matx[i][j] = 0; // Assume 0 Matrix as initial value
        }
    }

}

// Constructor for a square matrix with dimensions m x m and values given by vector a
Matrix::Matrix(int m, double* a, int arraySize){
    if(m*m == arraySize){
        rows = m;
        cols = m;

        // Fill Matrix with a
        matx = new double*[rows];
        for(int i = 0; i < rows; i++){
            matx[i] = new double[cols];
            for(int j = 0 ; j < cols ; j++){
                matx[i][j]= a[j*cols+i];
            }
        }
    } else cout << "ERROR Matrix Constructor: Dimension of a does not fit into Matrix with size: " << m << "x" << m << endl;
}


// Copy constructor, construct similar matrix with same attributes as given matrix M
Matrix::Matrix(const Matrix& M){

    //take over the attributes
    rows = M.Rows();
    cols = M.Cols();

    //build new matrix
    matx = new double*[rows];

    // loop over each element
    for (int i = 0 ; i< rows ; i++){
        // allocate the memory
        matx[i] = new double[cols];
        for(int j = 0 ; j < cols ; j++)
            matx[i][j] = M.Matx()[i][j]; // Copy values
    }
}


// Destructor for the matrix
Matrix::~Matrix() {
    for (int i = 0; i < rows; i++) {
        delete[] matx[i];
    }
        delete[] matx;
}


//Overrule copy operator
Matrix& Matrix::operator=(const Matrix& M){
    if (this != &M){
        // Create new Matrix with the number of rows and coloums being the same as M
        rows = M.Rows();
        cols = M.Cols();
        matx = new double*[rows];

        // Filling the values
        for (int i = 0 ; i< rows ; i++){
            matx[i] = new double[cols];

            for(int j = 0 ; j < cols ; j++)
                // copy values
                matx[i][j] = M.Matx()[i][j];
            }
        }
    return *this; // dereferencing
}

//Overload operator +=
Matrix& Matrix::operator+=(const Matrix& M ){
    if (rows == M.Rows() && cols == M.Cols()){

         // loop over each element
        for (int i = 0 ; i< rows ; i++){
            for(int j = 0 ; j < cols ; j++)
                matx[i][j] += M.Matx()[i][j]; // addition element-wise
        }
    } else
        cout << " ERROR += : The matrix shapes do not match for addition! Left Matrix " << rows  << " x " << cols << " Right matrix " << M.Rows() <<" x "<< M.Cols() << endl;
    return *this;

}

//Overload operator *= for Matrix multiplications
Matrix& Matrix::operator*=(const Matrix& M ){
    if (cols == M.Rows()){

        double ** lmatx = new double*[rows];

        // Copy Matrix
        lmatx = matx;

        // Create resulting matrix of size: rows x M.Cols()
        matx = new double*[rows];
        for(int i = 0 ; i < M.Cols() ; i++){
            matx[i] = new double[M.Cols()];
        }

         // loop over each element
        for (int i= 0; i< rows; i++ ){
            for (int j = 0 ; j< M.Cols() ; j++){
                double sum = 0;

                //get the linear combination to compute element i,j
                for (int k=0; k< rows; k++)
                    sum += lmatx[i][k]*M.Matx()[k][j];
                matx[i][j] = sum;
            }
        }
        //Set the new amount of columns (rows stay the same)
        cols = M.Cols();
    }
    else
        cout << " ERROR *=: The matrix shapes do not match for multiplication! Left Matrix " << rows  << " x " << cols << " Right matrix " << M.Rows() <<" x "<< M.Cols() << endl;
    return *this;

}

// Overload operator *= To multiply matrix with scalar value
Matrix& Matrix::operator*=(const double a ){

         // loop over each element
        for (int i = 0 ; i< rows ; i++){
            for(int j = 0 ; j < cols ; j++)
                matx[i][j] *= a; // multiply element-wise
        }
    return *this;
}


// Member function to print matrix:
void Matrix::printMatrix() const{
  for (int i = 0 ; i< rows ; i++){
    cout << "|";
    for(int j = 0 ; j < cols-1 ; j++)
        cout << matx[i][j] << ", " ;
    cout << matx[i][cols-1] << "|" << endl ;
    }
}

// Implementing the 2 norm, i.e. sum over all elements, take the square element-wise and take the root of the sum
double Matrix::p2norm() const{
    double res = 0;
     for (int i = 0 ; i< rows ; i++){
            for(int j = 0 ; j < cols ; j++)
                // Add square of each element
                res += matx[i][j]*matx[i][j];
    }
    // Take the root
    res = sqrt(res);
    return res;
}

//Maximum norm returns the absolute largest value of the matrix
double Matrix::maxnorm() const{
    // Initialize max value
    double current_max = -1.0;
    for (int i = 0 ; i< rows ; i++){
        for(int j = 0 ; j < cols ; j++){
            // Update if absolute value is larger
            if (abs(matx[i][j]) > current_max){
                current_max = abs(matx[i][j]);
            }
        }
    }
    return current_max;
}


// Function which fills all elements with the vector a of length n*m column-wise
void Matrix::fillMatrix(double *a, int arraySize){

    // Check if dimension align
    if ( rows*cols == arraySize ) {
        for (int i= 0 ; i< rows ; i++){
            for(int j = 0 ; j < cols ; j++)
                // Fill value with value given by the vector
                matx[i][j]= a[j*cols+i];
        }
    } else

     cout << "ERROR FILLMATRIX: The length of the array does not match the matrix shape: " << rows << " x " << cols << " Got shape: " << a << " Expected: " << rows*cols  << endl;
}


// Function which fills all elements of the matrix with the same double a
void Matrix::fillNumber(double a){
    for (int i= 0 ; i< rows ; i++){
        for(int j = 0 ; j < cols ; j++)
            matx[i][j]= a;
    }
}

// Fill diagonal of matrix with value a
void Matrix::fillDiagonal(double a){
    int smallersize;
    // if non-square matrix find min(rows, cols)
    if(rows < cols){
        smallersize = rows;
    }
    else {
        smallersize = cols;
    }

    for (int i= 0 ; i< smallersize ; i++){
        matx[i][i]= a; // fill diagonal
    }
}
