#include "domain.hpp"
#include "matrix.hpp"

#ifndef GFKT.HPP
#define GFKT.HPP

class GFkt {

private:
    // Matrix u; <-- CHANGE !!!
    shared_ptr<Domain> grid;


public:
    Matrix u;
    GFkt(shared_ptr<Domain> grid_) : u(grid_->N_()+1,grid_->M_()+1), grid(grid_) {}
    GFkt(const GFkt& U) : u(U.u), grid(U.grid) {}
    GFkt operator+(const GFkt& U) const;
    GFkt operator*(const GFkt& U) const;
    GFkt operator*(const double p) const;

    void D0xy(GFkt *dx, GFkt *dy) const;

    void D0xyold(GFkt *dx, GFkt *dy) const;

    GFkt Laplacian() const;

    void printGFkt() const;

    //

};

#endif // GFKT
