#include <memory>
#include <vector>
#include "curvebase.hpp"
#ifndef DOMAIN_HPP

#define DOMAIN_HPP

using namespace std;

class Domain{

private:
    // Four curvebases defining the border of the domain
    // Curvebase* sides[4];
    shared_ptr<Curvebase> sides[4];


    // Double arrays that will store the coordinates of the grid points
    vector<double> x_;
    vector<double> y_;


    // Size of the grid
    int n_ = 0;
    int m_ = 0;

    // Checks the consistency of the border of the domain
    bool check_consistency();

    // Help interpolation functions for generate_grid
    double phi1(double s) const {return 1-s;};
    double phi2(double s) const {return s;};

public:
    // Constructor
    Domain(shared_ptr<Curvebase> s1, shared_ptr<Curvebase> s2, shared_ptr<Curvebase> s3, shared_ptr<Curvebase> s4);
    // Destructor
    ~Domain();
    // Generate grid in domain with size nxm
    void generate_grid(int n, int m);
    // Prints the grid using cout
    void printGrid();

    // Getter Functions
    shared_ptr<Curvebase>* Sides(){return sides;};

    vector<double> X_() const {return x_;};
    vector<double> Y_() const {return y_;};

    int N_() const {return n_;};
    int M_() const {return m_;};
};

#endif
