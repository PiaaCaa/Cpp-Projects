#include <iostream>
#include <cmath>
#include "gfkt.hpp"

using namespace std;

GFkt GFkt::operator+(const GFkt& U) const {
    if(grid == U.grid){ // Defined on the same Grid
        GFkt tmp(U);
        tmp.u += U.u;
        return tmp;
    } else {
        cout << "Grids are not identical, + operation failed!" << endl;
        exit(0);
    }
}


GFkt GFkt::operator*(const double p) const {
    GFkt tmp(this);
    tmp.u *= p;
    return tmp;

}


void GFkt::printGFkt() const {
    grid->printGrid();
    u.printMatrix();
}
