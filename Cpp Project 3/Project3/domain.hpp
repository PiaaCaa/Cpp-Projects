#include "curvebase.hpp"
#ifndef DOMAIN_HPP
#define DOMAIN_HPP


class Domain{

private:
    // Four curvebases defining the border of the domain
    Curvebase* sides[4];

    // Double arrays that will store the coordinates of the grid points
    double* x_ = nullptr;
    double* y_ = nullptr;


    // Size of the grid
    int n_;
    int m_;

    // Checks the consistency of the border of the domain
    bool check_consistency();

    // Help interpolation functions for generate_grid
    double phi1(double s){return 1-s;};
    double phi2(double s){return s;};

public:
    // Constructor
    Domain(Curvebase& s1, Curvebase& s2, Curvebase& s3, Curvebase& s4);
    // Destructor
    ~Domain();
    // Generate grid in domain with size nxm
    void generate_grid(int n, int m);
    // Prints the grid using cout
    void printGrid();

    // Getter Functions
    Curvebase** Sides(){return sides;};

    double* X_(){return x_;};
    double* Y_(){return y_;};

    int N_(){return n_;};
    int M_(){return m_;};
};

#endif
