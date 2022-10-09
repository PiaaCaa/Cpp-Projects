#include <iostream>
#include <iostream>
#include <cmath>

#include "matrix.hpp"
using namespace std;

//TODO destructor!!

//Constructor for square matrix nxn given size n
Matrix::Matrix(int m){
    rows = m;
    cols = m;
    //matx = new double [rows][cols];

    //Allocate new Memory
    // TODO do we need to use calloc?
    // TODO also deallocate the array!!
    matx = new double*[rows];
    for(int i = 0; i < rows; i++)
        matx[i] = new double[cols];
}

//Construct similar matrix with same attributes as given matrix M
Matrix::Matrix(const Matrix& M){

    //take over the attributes
    rows = M.Rows();
    cols = M.Cols();
    //matx = M.Matx(); DISCUSSION: // check if this is correct! // I think this is not correct!!! since the pointer should point somewhere else but take over the same values

    //build new matrix
    matx = new double*[rows];

    for (int i = 0 ; i< rows ; i++){
        // allocate the memory
        matx[i] = new double[cols];
        for(int j = 0 ; j < cols ; j++)
            // Copy values
            matx[i][j] = M.Matx()[i][j];
    }
}


//Overrule copy operator
// DISCUSSION: how shoulds thi soperate do we want a new object with same elements or does it really should bee the same?
// Lecture: The value returned should be (a reference to) the rightmost expression.
//TODO check whether bjects have same dimensions!!
Matrix& Matrix::operator=(const Matrix& M){
    if (this != &M){
        if (rows != M.Rows() || cols !=M.Cols() )
            cout << "The Matrix dimensions do not match. Previous shape: " << rows << "x" << cols << " New shape: " << rows << "x" << cols << endl;

        //TODO this is very inefficient?? Since constrcuot does the same job! e.g. //Matrix(M);
        rows = M.Rows();
        cols = M.Cols();
        //matx = M.Matx(); // check if this is correct! // I think this is not correct!!! since the pointer should point somewhere else but take over the same values

        //DISCUSSION: DO we also need a desctructor here for previous matx?

        matx = new double*[rows];
        for (int i = 0 ; i< rows ; i++){
            // allocate memory
            matx[i] = new double[cols];

            for(int j = 0 ; j < cols ; j++)
                // copy values
                matx[i][j] = M.Matx()[i][j];
            }
        }
    return *this; // dereferencing
    // Lecture: For consistency with the built-in types, it should be a reference to the left-hand operand.
}

//Overload operator +=
Matrix& Matrix::operator+=(const Matrix& M ){
    if (rows == M.Rows() && cols == M.Cols()){

         // loop over each element
        for (int i = 0 ; i< rows ; i++){
            for(int j = 0 ; j < cols ; j++)
                matx[i][j] += M.Matx()[i][j];
        }
    } else
        cout << " ERROR += : The matrix shapes do not match for addition! Left Matrix " << rows  << " x " << cols << " Right matrix " << M.Rows() <<" x "<< M.Cols() << endl;
    return *this;

}

//Overload operator *= for Matrix multiplications
Matrix& Matrix::operator*=(const Matrix& M ){
    if (cols == M.Rows()){

        //copy previous matrix:
        //Matrix lmatx = Matrix(rows); // Does not work??

        //TODO creating a new matrix is very inefficient!! Solve this?
        double ** lmatx = new double*[rows];
        for (int i = 0 ; i< rows ; i++){
            // allocate the memory
            lmatx[i] = new double[cols];
            for(int j = 0 ; j < cols ; j++)
                lmatx[i][j] = matx[i][j];
        }
        // TODO delete afterwards!

        //create resulting matrix of size: rows x M.Cols()
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

//Overload operator *= To multiply matrix with scalar value
Matrix& Matrix::operator*=(const double a ){

         // loop over each element
        for (int i = 0 ; i< rows ; i++){
            for(int j = 0 ; j < cols ; j++)
                matx[i][j] *= a; // multply elementwise
        }
    return *this;
}


// Member function to print matrix:
void Matrix::printMatrix() const{
  for (int i = 0 ; i< rows ; i++){
    for(int j = 0 ; j < cols ; j++)
        cout << matx[i][j] << ", " ;
    cout << endl ;
    }
}

//TODO welche Matrix norm soll gewählt werden?
// habe p-norm , p=2 gewählt aber bissl unsicher
//implememting the 2 norm, i.e. sum over all elements, take the square elementwise and take the root of the sum
double Matrix::norm() const{
    double res = 0;
     for (int i = 0 ; i< rows ; i++){
            for(int j = 0 ; j < cols ; j++)
                res += matx[i][j]*matx[i][j];
    }
    res = sqrt(res);
    return res;
}
//Function, which fills all elements with the vector of length n*m columnwise
void Matrix::fillMatrix(double a[]){
    int length_a = sizeof(a)/sizeof(a[0]);
    if ( rows *cols== rows*cols){ // TODO change back!
    for (int i= 0 ; i< rows ; i++){
        for(int j = 0 ; j < cols ; j++)
            matx[i][j]= a[j*cols+i];
    }
    } else
     cout << "ERROR FILLMATRIX: The length of the array does not match the matrix shape: " << rows << " x " << cols << " Got shape: " << length_a << " Expected: " << rows*cols  << endl;
}


//Function, which fills all elements of the matrix with the same number a
void Matrix::fillNumber(double a){
    for (int i= 0 ; i< rows ; i++){
        for(int j = 0 ; j < cols ; j++)
            matx[i][j]= a;
    }
}

