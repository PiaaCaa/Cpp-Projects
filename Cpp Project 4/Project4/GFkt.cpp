#include <iostream>
#include <cmath>
#include "gfkt.hpp"

using namespace std;

GFkt GFkt::operator+(const GFkt& U) const {
    if(grid == U.grid){ // Defined on the same Grid
        GFkt tmp(*this);
        tmp.u += U.u;
        return tmp;
    } else {
        cout << "Grids are not identical, + operation failed!" << endl;
        exit(0);
    }
}


GFkt GFkt::operator*(const double p) const {
    GFkt tmp(*this);
    tmp.u *= p;
    return tmp;
}



void GFkt::D0xy(GFkt *dx, GFkt *dy) const {

    int m = grid->M_();
    int n = grid->N_();


    Matrix du_dx(n+1, m+1);
    Matrix du_dy(n+1, m+1);

    double h1 = 1.0/n;
    double h2 = 1.0/m;

    double dux[(n+1)*(m+1)];
    double duy[(n+1)*(m+1)];


    for(int i = 0; i <= n; ++i){
        for(int j = 0; j <= m; ++j){

            double lix = i-1;
            double rix = i+1;
            double liy = -(n+1);
            double riy = n+1;
            double hxi = 2*h1;
            double heta = 2*h2;

            if (i==0){
                lix = i;
                hxi = h1;
            } else if( i== n){
                rix = i ;
                hxi = h1;
            }
             if (j==0){
                liy = 0;
                heta = h2;

            } else if( j== m){
                riy = 0;
                heta = h2;
            }


            double dphix_dxi;
            double dphix_deta;
            double dphiy_dxi;
            double dphiy_deta;

            dphix_dxi = (grid->X_()[j*(n+1)+rix] - grid->X_()[j*(n+1)+lix]) / hxi;

            dphix_deta = (grid->X_()[j*(n+1)+i+riy] - grid->X_()[j*(n+1)+i+ liy]) / heta;

            dphiy_dxi = (grid->Y_()[j*(n+1)+rix] - grid->Y_()[j*(n+1)+lix]) / hxi;

            dphiy_deta = (grid->Y_()[j*(n+1)+i+riy] - grid->Y_()[j*(n+1)+i+liy]) / heta;

            //cout << "hxi: " << hxi << endl;

            //cout << "left value: " << grid->X_()[j*(n+1)+lix] << endl;

            //cout << "right value: " << grid->X_()[j*(n+1)+rix] << endl;

            // cout << "res: " << (grid->X_()[j*(n+1)+rix] -  grid->X_()[j*(n+1)+lix]) / hxi << endl;
            // cout << "dphiy_deta: " << dphiy_deta << endl;


            double DetJ = dphix_dxi * dphiy_deta - dphix_deta * dphiy_dxi;

            // cout << "detJ: " << DetJ << endl;

            //i*h1 xi
            //j*h2 eta



            //dphix_dxi = (grid->X_()[j*(n+1)+i+1] - grid->X_()[j*(n+1)+i-1]) / 2*h1;

            //dphix_deta = (grid->X_()[j*(n+1)+i+(n+1)] - grid->X_()[j*(n+1)+i-(n+1)]) / 2*h2;

            //dphiy_dxi = dphix_dxi = (grid->Y_()[j*(n+1)+i+1] - grid->Y_()[j*(n+1)+i-1]) / 2*h1;

            //dphiy_deta = (grid->Y_()[j*(n+1)+i+(n+1)] - grid->Y_()[j*(n+1)+i-(n+1)]) / 2*h2;


            double du_dxi;
            double du_deta;

            if (i==0){
                du_dxi = (-u.Matx()[i][j] + u.Matx()[i+1][j]) / h1;
            } else if (i==n){
                du_dxi = (-u.Matx()[i-1][j] + u.Matx()[i][j]) / h1;
            } else {
                du_dxi = (-u.Matx()[i-1][j] + u.Matx()[i+1][j]) / (2*h1);
            }

            if (j==0){
                du_deta = (-u.Matx()[i][j] + u.Matx()[i][j+1]) / h2;
            } else if(j==m){
                du_deta = (-u.Matx()[i][j-1] + u.Matx()[i][j]) / h2;
            } else {
                du_deta = (-u.Matx()[i][j-1] + u.Matx()[i][j+1]) / (2*h2);
            }


            // cout << "du_xi: " << du_dxi << endl;
            // cout << "du_xi: " << du_dxi << endl << "du_deta: " << du_deta << endl;

            dux[j*(n+1)+i] = 1 / DetJ * (du_dxi * dphiy_deta - du_deta * dphiy_dxi);

            // cout << "dux: " << dux[j*(n+1)+i] << endl << endl;

            duy[j*(n+1)+i] = 1 / DetJ * (du_deta * dphix_dxi - du_dxi * dphix_deta);


        }
    }

    du_dx.fillMatrix(dux, (m+1)*(n+1));
    du_dy.fillMatrix(duy, (m+1)*(n+1));

    dx->u = du_dx;
    dy->u = du_dy;

}



void GFkt::D0xyold(GFkt *dx, GFkt *dy) const {


    int m = grid->M_();
    int n = grid->N_();


    Matrix du_dx(n+1, m+1);
    Matrix du_dy(n+1, m+1);

    double dux[(n+1)*(m+1)];
    double duy[(n+1)*(m+1)];


    for(int i = 0; i <= n; ++i){
        for(int j = 0; j <= m; ++j){

            double upperval_ux;
            double upperval_x;


            double upperval_uy;
            double upperval_y;

            double lowerval_ux;
            double lowerval_x;

            double lowerval_uy;
            double lowerval_y;

            if (i == 0){
                upperval_ux = u.Matx()[i+1][j];
                upperval_x = grid->X_()[j*(n+1)+i+1];

                lowerval_ux = u.Matx()[i][j];
                lowerval_x = grid->X_()[j*(n+1)+i];
            } else if (i == n){
                upperval_ux = u.Matx()[i][j];
                upperval_x = grid->X_()[j*(n+1)+i];

                lowerval_ux = u.Matx()[i-1][j];
                lowerval_x = grid->X_()[j*(n+1)+i-1];
            } else {
                upperval_ux = u.Matx()[i+1][j];
                upperval_x = grid->X_()[j*(n+1)+i+1];

                lowerval_ux = u.Matx()[i-1][j];
                lowerval_x = grid->X_()[j*(n+1)+i-1];
            }


            if (j == 0){
                upperval_uy = u.Matx()[i][j+1];
                upperval_y = grid->Y_()[j*(n+1)+i+(n+1)];

                lowerval_uy = u.Matx()[i][j];
                lowerval_y = grid->Y_()[j*(n+1)+i];
            } else if (j == m){
                upperval_uy = u.Matx()[i][j];
                upperval_y = grid->Y_()[j*(n+1)+i];

                lowerval_uy = u.Matx()[i][j-1];
                lowerval_y = grid->Y_()[j*(n+1)+i-(n+1)];
            } else {
                upperval_uy = u.Matx()[i][j+1];
                upperval_y = grid->Y_()[j*(n+1)+i+(n+1)];

                lowerval_uy = u.Matx()[i][j-1];
                lowerval_y = grid->Y_()[j*(n+1)+i-(n+1)];
            }

            dux[j*(n+1)+i] = (upperval_ux - lowerval_ux) / (upperval_x - lowerval_x) ;

            duy[j*(n+1)+i] = (upperval_uy - lowerval_uy) / (upperval_y - lowerval_y);

            //cout << "upperval_uy: " << upperval_uy << endl << "upperval_y: " << upperval_y << endl;
            //cout << "index: " << j*(m+1)+i << endl;
            //cout << "lowerval_y: " << lowerval_y << endl << "upperval_y: " << upperval_y << endl;
            //cout << "Res: " << (upperval_uy - lowerval_uy) / (upperval_y - lowerval_y) << endl;

            //Phi = grid->

        }
    }



    du_dx.fillMatrix(dux, (m+1)*(n+1));
    du_dy.fillMatrix(duy, (m+1)*(n+1));

    dx->u = du_dx;
    dy->u = du_dy;

/*

            x_[i + j*(n+1)] = phi1(i*h1) * sides[3]->x(1-j*h2) + phi2(i*h1) * sides[1]->x(j*h2)
                             +phi1(j*h2) * sides[0]->x(i*h1) + phi2(j*h2) * sides[2]->x(1-i*h1)
                             -phi1(i*h1) * phi1(j*h2) * sides[0]->x(0)  // Lower left corner point
                             -phi1(i*h1) * phi2(j*h2) * sides[3]->x(0)  // Upper left corner point
                             -phi2(i*h1) * phi1(j*h2) * sides[1]->x(0)  // Lower right corner point
                             -phi2(i*h1) * phi2(j*h2) * sides[2]->x(0); // Upper right corner point


            // y coordinate of grid points
            y_[i + j*(n+1)] = phi1(i*h1) * sides[3]->y(1-j*h2) + phi2(i*h1) * sides[1]->y(j*h2)
                             +phi1(j*h2) * sides[0]->y(i*h1) + phi2(j*h2) * sides[2]->y(1-i*h1)
                             -phi1(i*h1) * phi1(j*h2) * sides[0]->y(0)  // Lower left corner point
                             -phi1(i*h1) * phi2(j*h2) * sides[3]->y(0)  // Upper left corner point
                             -phi2(i*h1) * phi1(j*h2) * sides[1]->y(0)  // Lower right corner point
                             -phi2(i*h1) * phi2(j*h2) * sides[2]->y(0); // Upper right corner point



            double DetJ = dphix_dxi * dphiy_deta - dphix_deta * dphiy_dxi;

            //i*h1 xi
            //j*h2 eta

            double du_dxi = (-u.Matx()[i-1][j] + u.Matx()[i+1][j]) / 2*h1;

            double du_deta = (-u.Matx()[i][j-1] + u.Matx()[i][j+1]) / 2*h2;

            du_dx[i][j] = 1 / DetJ * (du_dxi * dphiy_deta - du_deta * dphiy_dxi);

            du_dy[i][j] = 1 / DetJ * (du_deta * dphix_dxi - du_dxi * dphix_deta);



            double dphix_dxi =  - 1 * grid->Sides()[3]->x(1-j*h2) + 1 * grid->Sides()[1]->x(j*h2)
                         + 1 * grid->phi1(j*h2) * grid->Sides()[0]->x(0) // Lower left corner point
                         + 1 * grid->phi2(j*h2) * grid->Sides()[3]->x(0) // Upper left corner point
                         - 1 * grid->phi1(j*h2) * grid->Sides()[1]->x(0) // Lower right corner point
                         - 1 * grid->phi2(j*h2) * grid->Sides()[2]->x(0); // Upper right corner point

            double dphix_deta = - 1 * grid->Sides()[0]->x(i*h1) + 1 * grid->Sides()[2]->x(1-i*h1)
                         + 1 * grid->phi1(i*h1) * grid->Sides()[0]->x(0) // Lower left corner point
                         - 1 * grid->phi1(i*h1) * grid->Sides()[3]->x(0) // Upper left corner point
                         + 1 * grid->phi2(i*h1) * grid->Sides()[1]->x(0) // Lower right corner point
                         - 1 * grid->phi2(i*h1) * grid->Sides()[2]->x(0); // Upper right corner point


            double dphiy_dxi =  - 1 * grid->Sides()[3]->y(1-j*h2) + 1 * grid->Sides()[1]->y(j*h2)
                         + 1 * grid->phi1(j*h2) * grid->Sides()[0]->y(0) // Lower left corner point
                         + 1 * grid->phi2(j*h2) * grid->Sides()[3]->y(0) // Upper left corner point
                         - 1 * grid->phi1(j*h2) * grid->Sides()[1]->y(0) // Lower right corner point
                         - 1 * grid->phi2(j*h2) * grid->Sides()[2]->y(0); // Upper right corner point

            double dphiy_deta = - 1 * grid->Sides()[0]->y(i*h1) + 1 * grid->Sides()[2]->y(1-i*h1)
                         + 1 * grid->phi1(i*h1) * grid->Sides()[0]->y(0) // Lower left corner point
                         - 1 * grid->phi1(i*h1) * grid->Sides()[3]->y(0) // Upper left corner point
                         + 1 * grid->phi2(i*h1) * grid->Sides()[1]->y(0) // Lower right corner point
                         - 1 * grid->phi2(i*h1) * grid->Sides()[2]->y(0); // Upper right corner point

                             */

}

GFkt GFkt::Laplacian() const {

    GFkt ux = GFkt(*this);
    GFkt uy = GFkt(*this);


    GFkt uxx = GFkt(*this);
    GFkt uyy = GFkt(*this);
    GFkt uxy = GFkt(*this);

    D0xy(&ux, &uy);

    ux.D0xy(&uxx, &uxy);
    uy.D0xy(&uxy, &uyy);

    uxx.u += uyy.u;

    return uxx;

    /*

    int m = grid->M_();
    int n = grid->N_();

    GFkt temp = GFkt(*this);

    Matrix nabla_u(n+1, m+1);

    double laplace[(n+1)*(m+1)];


    for(int i = 0; i <= n; ++i){
        for(int j = 0; j <= m; ++j){

            double leftval_ux;
            double leftval_x;

            double upperval_uy;
            double upperval_y;

            double rightval_ux;
            double rightval_x;

            double lowerval_uy;
            double lowerval_y;

            double currentval_u = u.Matx()[i][j];

            if (i == 0){
                rightval_ux = u.Matx()[i+1][j];
                rightval_x = grid->X_()[j*(n+1)+i+1];

                leftval_ux = u.Matx()[i][j];
                leftval_x = grid->X_()[j*(n+1)+i];
            } else if (i == n){
                rightval_ux = u.Matx()[i][j];
                rightval_x = grid->X_()[j*(n+1)+i];

                leftval_ux = u.Matx()[i-1][j];
                leftval_x = grid->X_()[j*(n+1)+i-1];
            } else {
                rightval_ux = u.Matx()[i+1][j];
                rightval_x = grid->X_()[j*(n+1)+i+1];

                leftval_ux = u.Matx()[i-1][j];
                leftval_x = grid->X_()[j*(n+1)+i-1];
            }


            if (j == 0){
                upperval_uy = u.Matx()[i][j+1];
                upperval_y = grid->Y_()[j*(n+1)+i+(n+1)];

                lowerval_uy = u.Matx()[i][j];
                lowerval_y = grid->Y_()[j*(n+1)+i];
            } else if (j == m){
                upperval_uy = u.Matx()[i][j];
                upperval_y = grid->Y_()[j*(n+1)+i];

                lowerval_uy = u.Matx()[i][j-1];
                lowerval_y = grid->Y_()[j*(n+1)+i-(n+1)];
            } else {
                upperval_uy = u.Matx()[i][j+1];
                upperval_y = grid->Y_()[j*(n+1)+i+(n+1)];

                lowerval_uy = u.Matx()[i][j-1];
                lowerval_y = grid->Y_()[j*(n+1)+i-(n+1)];
            }

            double lv = (rightval_ux + leftval_ux - 2 * currentval_u) / ((rightval_x - leftval_x) * (rightval_x - leftval_x));
            double rv = (upperval_uy + lowerval_uy - 2 * currentval_u) / ((upperval_y - lowerval_y) * (upperval_y - lowerval_y));

            laplace[j*(n+1)+i] = lv + rv;

            //cout << "upperval_uy: " << upperval_uy << endl << "upperval_y: " << upperval_y << endl;
            //cout << "index: " << j*(m+1)+i << endl;
            //cout << "lv: " << lv << endl << "rv: " << rv << endl;
            //cout << "Res: " << (upperval_uy - lowerval_uy) / (upperval_y - lowerval_y) << endl;
        }
    }



    nabla_u.fillMatrix(laplace, (m+1)*(n+1));

    temp.u = nabla_u;

    return temp;
    */
}


void GFkt::printGFkt() const {
    grid->printGrid();
    u.printMatrix();
}
