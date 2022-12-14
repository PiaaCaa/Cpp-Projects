#include "domain.hpp"
#include "matrix.hpp"

#ifndef GFKT.HPP
#define GFKT.HPP

class GFkt {

private:
    Matrix u; // Stores the function values at the grid points defined by grid
    shared_ptr<Domain> grid; // Object of class Grid. Represents a grid consisting of four curvebases


public:
    // Constructor
    GFkt(shared_ptr<Domain> grid_) : u(grid_->N_()+1,grid_->M_()+1), grid(grid_) {}

    // Copy constructor
    GFkt(const GFkt& U) : u(U.u), grid(U.grid) {}

    // Operator overload
    // Addition by another Gridfunction
    GFkt operator+(const GFkt& U) const;

    // Multiplication with a scalar
    GFkt operator*(const double p) const;

    // Generate partial derivatives of u and save them into dx and dy
    void D0xy(GFkt *dx, GFkt *dy) const;

    // Generate Laplacian of u and return it as a Gridfunction
    GFkt Laplacian() const;

    // Getter functions
    Matrix U() const {return u;};
    shared_ptr<Domain> Grid() const {return grid;};

    // Set function values for u
    void setFunction(Matrix u_new);

    // Setter for a new grid
    void setGrid(shared_ptr<Domain> newgrid);

    // Print function
    void printGFkt() const;

};

#endif // GFKT
