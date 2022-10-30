#ifndef MATRIX_HPP
#define MATRIX_HPP


//header file for Matrix object
class Matrix {
private:
    int rows;
    int cols; // if square matrix not necessary, but with this the class could be extended non square matrices
    double **matx;
public:
    //Constructors
    Matrix(int m);
    Matrix(const Matrix&);

    // Destructor
    ~Matrix();

    //Operation overloading
    Matrix& operator=(const Matrix&);
    Matrix& operator+=(const Matrix&);
    Matrix& operator*=(const Matrix&);
    Matrix& operator*=(const double);

    //Getter (member) functions
    int Rows() const {return rows;}; // const indicates that the object will not change its state when the attribute is used
    int Cols() const {return cols;};
    double** Matx() const {return matx;};

    //Member functions
    double p2norm() const;
    double maxnorm() const;
    void printMatrix() const;
    void fillMatrix(double *, int);
    void fillNumber(double ); // added by me
    void fillDiagonal(double);
};
#endif

