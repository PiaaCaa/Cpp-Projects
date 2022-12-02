#ifndef MATRIX_HPP
#define MATRIX_HPP


// Header file for Matrix object
class Matrix {
private:
    int rows;
    int cols;
    double **matx;
public:
    //Constructors
    Matrix(int m); // Creates mxm Matrix with all entries 0
    Matrix(int n, int m); // Creates nxm Matrix with all entries 0
    Matrix(int m, double* a, int arraySize); // Creates mxm Matrix with values given by vector a with size arraySize
    Matrix(const Matrix&); // Copy constructor

    // Destructor
    ~Matrix();

    //Operation overloading
    Matrix& operator=(const Matrix&);
    Matrix& operator+=(const Matrix&);
    Matrix& operator*=(const Matrix&);
    Matrix& operator*=(const double);

    //Getter (member) functions
    int Rows() const {return rows;};
    int Cols() const {return cols;};
    double** Matx() const {return matx;};

    //Member functions
    double p2norm() const;
    double maxnorm() const;
    void printMatrix() const;
    void fillMatrix(double *, int);
    void fillNumber(double );
    void fillDiagonal(double);
};
#endif

