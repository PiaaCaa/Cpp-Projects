#include <iostream>
#include <cmath>
#include "GFkt.hpp"

using namespace std;

// Operation overload, addition by another grid function
GFkt GFkt::operator+(const GFkt& U) const {
    if(grid == U.grid){ // Defined on the same Grid
        GFkt tmp(*this);
        tmp.u += U.u; // Use Matrix += operator which is overloaded
        return tmp;
    } else {
        cout << "Grids are not identical, + operation failed!" << endl;
        exit(0);
    }
}


// Operation overload, multiplication with a scalar
GFkt GFkt::operator*(const double p) const {
    GFkt tmp(*this);
    tmp.u *= p; // Using the overloaded *= operator of class Matrix
    return tmp;
}


// Calculate the derivatives of u and store them in Gridfunctions dx and dy
void GFkt::D0xy(GFkt *dx, GFkt *dy) const {

    // If the grid does not match, set it to the one of u
    if(grid != dx->Grid()){
        dx->setGrid(grid);
    }

    if(grid != dy->Grid()){
        dy->setGrid(grid);
    }

    // Size of grid
    int m = grid->M_();
    int n = grid->N_();

    // Create matrices that will contain the partial derivatives
    Matrix du_dx(n+1, m+1);
    Matrix du_dy(n+1, m+1);

    // Step size on the reference grid
    double h1 = 1.0/n;
    double h2 = 1.0/m;

    // Vectors to fill the derivative matrices
    double dux[(n+1)*(m+1)];
    double duy[(n+1)*(m+1)];

    // Iterate over every grid point
    for(int j = 0; j <= m; ++j){
        for(int i = 0; i <= n; ++i){

            // Define indices, this is done because the finite differences on the boundaries us forward/backward differences
            // instead of central differences.
            double lix = i-1; // Left index for xi variable
            double rix = i+1; // Right index for xi variable
            double liy = -(n+1); // Left index for eta variable
            double riy = n+1; // Right index for eta variable
            double hxi = 2*h1; // Standard step size (the denominator of the finite difference) in xi direction
            double heta = 2*h2; // Standard step size (the denominator of the finite difference) in eta direction

            if (i==0){ // if i==0, we are at the left boundary in xi direction
                lix = i; // Therefore the left index is adjusted (use forward difference)
                hxi = h1; // Step size is also adjusted
            } else if( i== n){ // if i ==n we are at the right boundary
                rix = i ; // Adjust parameters for backward difference
                hxi = h1;
            }

             if (j==0){ // The same as for i but now in eta direction
                liy = 0; // Use forward difference
                heta = h2;
            } else if( j== m){
                riy = 0; // Use backward difference
                heta = h2;
            }

            // Define required parameters for the equations to solve for du/dx and du/dy as presented in the lecture
            double dphix_dxi;
            double dphix_deta;
            double dphiy_dxi;
            double dphiy_deta;

            // Using finite differences to calculate  the partial derivatives of Phi. These values are already stored in the physical
            // coordinates grid->X_() and grid->Y_()
            dphix_dxi = (grid->X_()[j*(n+1)+rix] - grid->X_()[j*(n+1)+lix]) / hxi;

            dphix_deta = (grid->X_()[j*(n+1)+i+riy] - grid->X_()[j*(n+1)+i+ liy]) / heta;

            dphiy_dxi = (grid->Y_()[j*(n+1)+rix] - grid->Y_()[j*(n+1)+lix]) / hxi;

            dphiy_deta = (grid->Y_()[j*(n+1)+i+riy] - grid->Y_()[j*(n+1)+i+liy]) / heta;


            // Calculate the determinant as described in the lecture
            double DetJ = dphix_dxi * dphiy_deta - dphix_deta * dphiy_dxi;

            // Define parameters for the partial derivatives du/dxi and du/deta
            double du_dxi;
            double du_deta;

            // Again using finite differences:
            if (i==0){ // If i == 0, use forward difference
                du_dxi = (-u.Matx()[i][j] + u.Matx()[i+1][j]) / h1;
            } else if (i==n){ // If i == n use backward difference
                du_dxi = (-u.Matx()[i-1][j] + u.Matx()[i][j]) / h1;
            } else { // Everywhere else use central difference
                du_dxi = (-u.Matx()[i-1][j] + u.Matx()[i+1][j]) / (2*h1);
            }

            if (j==0){ // if j == 0 use forward difference
                du_deta = (-u.Matx()[i][j] + u.Matx()[i][j+1]) / h2;
            } else if(j==m){ // if j == m use backward difference
                du_deta = (-u.Matx()[i][j-1] + u.Matx()[i][j]) / h2;
            } else { // Everywhere else use central difference
                du_deta = (-u.Matx()[i][j-1] + u.Matx()[i][j+1]) / (2*h2);
            }

            // Now calcualte the partial derivatives at the current grid point as defined by the equation in the lecture
            dux[j*(n+1)+i] = 1 / DetJ * (du_dxi * dphiy_deta - du_deta * dphiy_dxi);
            duy[j*(n+1)+i] = 1 / DetJ * (du_deta * dphix_dxi - du_dxi * dphix_deta);
        }
    }

    // Fill the matrices with the vectors that contain the derivative information
    du_dx.fillMatrix(dux, (m+1)*(n+1));
    du_dy.fillMatrix(duy, (m+1)*(n+1));

    // Set derivative functions for the grid functions
    dx->setFunction(du_dx);
    dy->setFunction(du_dy);

}

// Function that returns the laplacian of u as a gridfunction
GFkt GFkt::Laplacian() const {

    // Make copies of the grid to store the first derivatives
    GFkt ux = GFkt(*this);
    GFkt uy = GFkt(*this);

    // Make copies of the grid to store the second derivatives
    GFkt uxx = GFkt(*this);
    GFkt uyy = GFkt(*this);
    GFkt uxy = GFkt(*this);

    // Calculate the first derivatives
    D0xy(&ux, &uy);

    // Calculate the second derivatives
    ux.D0xy(&uxx, &uxy);
    uy.D0xy(&uxy, &uyy);

    // The laplacian is the sum of uxx and uyy
    uxx.u += uyy.u;

    return uxx;
}

// Function to set a function on the grid
void GFkt::setFunction(Matrix u_new){
    u = u_new;
    cout << "Created new function on the grid!" << endl;
}

// Function to set a new grid
void GFkt::setGrid(shared_ptr<Domain> newgrid){
    grid = newgrid;
}

// Print function
void GFkt::printGFkt() const {
    grid->printGrid();
    u.printMatrix();
}
