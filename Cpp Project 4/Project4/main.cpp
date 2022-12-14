#include <iostream>
#include <memory>
#include <cmath>
#include "curvebase.hpp"
#include "xvertical.hpp"
#include "yhorizontal.hpp"
#include "nonconstcurve.hpp"
#include "domain.hpp"
#include "GFkt.hpp"
#include "matrix.hpp"
#include<cstdio>

using namespace std;

// Function u(x,y) as described in the exercise
double func(double x, double y){
    return sin((x*x)/100.0) * cos(x/10.0) + y;

}



int main()
{

    // Defining the domain as described by the exercise
    shared_ptr<Nonconstcurve> s1 = make_shared<Nonconstcurve>(-10.0, 5.0);
    shared_ptr<Xvertical> s2 = make_shared<Xvertical>(0.0, 3.0, 5.0);
    shared_ptr<Yhorizontal> s3 = make_shared<Yhorizontal>(5.0, -10.0, 3.0);
    shared_ptr<Xvertical> s4 = make_shared<Xvertical>(3.0, 0.0, -10.0);


    // Generate domain
    shared_ptr<Domain> mydomain = make_shared<Domain>(s1,s2,s3,s4);

    // Choose size of the grid to be generated
    int N = 50;
    int M = 20;
    mydomain->generate_grid(N,M);

    // Define grid functions, all on the same domain to allow for the operations to work
    GFkt gridfun(mydomain);
    GFkt gridfundx(mydomain);
    GFkt gridfundy(mydomain);


    // Make a matrix and fill it with the function values of u for the given grid points
    Matrix m1(N+1,M+1);

    double v1[(N+1)*(M+1)];
    for(int j=0; j< (M+1); j++){
        for(int i=0; i< (N+1); i++){
            v1[j*(N+1)+i] = func(mydomain->X_()[j*(N+1)+i], mydomain->Y_()[j*(N+1)+i]);
        }
    }
    m1.fillMatrix(v1, (N+1)*(M+1));
    gridfun.setFunction(m1);

    cout << "Gridfunction for u generated!" << endl;

    cout << "---------------" << endl;

    // Calculate the partial derivatives and store them as Gridfunctions gridfundx and gridfundy
    gridfun.D0xy(&gridfundx, &gridfundy);

    // Get the laplacian of u and store it as a Gridfunction gridfunlaplace
    GFkt gridfunlaplace = gridfun.Laplacian();


    cout << "------------" << endl;


    // Save the grid to the file 'grid_out.bin'
    int counter = 0;
    int len = (mydomain->M_()+1)*(mydomain->N_()+1);
    double grid[2*len];
    for(int i=0; i<2*len;i+=2){
        grid[i] = mydomain->X_()[counter];
        grid[i+1] = mydomain->Y_()[counter];
        counter+=1;
    }

    FILE *fp;
    fp =fopen("grid_out.bin","wb");
    fwrite(grid,sizeof(double),2*len,fp);
    fclose(fp);

    cout << "Saved grid to <grid_out.bin>!" << endl;


    // Save discretized u function to the file 'u_out.bin'
    counter = 0;
    len = (mydomain->M_()+1)*(mydomain->N_()+1);
    double gridu[len];
    for(int i=0; i<mydomain->N_()+1;i++){
        for(int j=0; j<mydomain->M_()+1; j++){
            gridu[j*(mydomain->N_()+1)+i] = gridfun.U().Matx()[i][j];
        }
    }

    FILE *fpu;
    fpu =fopen("u_out.bin","wb");
    fwrite(gridu,sizeof(double),len,fpu);
    fclose(fpu);
    cout << "Saved u to <u_out.bin>!" << endl;


    // Save discretized derivative du / dx
    counter = 0;
    len = (mydomain->M_()+1)*(mydomain->N_()+1);
    double griddux[len];
    for(int i=0; i<mydomain->N_()+1;i++){
        for(int j=0; j<mydomain->M_()+1; j++){
            griddux[j*(mydomain->N_()+1)+i] = gridfundx.U().Matx()[i][j];
        }
    }

    FILE *fpdux;
    fpdux =fopen("dux_out.bin","wb");
    fwrite(griddux,sizeof(double),len,fpdux);
    fclose(fpdux);
    cout << "Saved du / dx to <dux_out.bin>!" << endl;



    // Save discretized derivative du / dy
    counter = 0;
    len = (mydomain->M_()+1)*(mydomain->N_()+1);
    double gridduy[len];
    for(int i=0; i<mydomain->N_()+1;i++){
        for(int j=0; j<mydomain->M_()+1; j++){
            gridduy[j*(mydomain->N_()+1)+i] = gridfundy.U().Matx()[i][j];
        }
    }

    FILE *fpduy;
    fpduy =fopen("duy_out.bin","wb");
    fwrite(gridduy,sizeof(double),len,fpduy);
    fclose(fpduy);
    cout << "Saved du / dy to <duy_out.bin>!" << endl;


    // Save discretized Laplacian nabla u
    counter = 0;
    len = (mydomain->M_()+1)*(mydomain->N_()+1);
    double gridlaplace[len];
    for(int i=0; i<mydomain->N_()+1;i++){
        for(int j=0; j<mydomain->M_()+1; j++){
            gridlaplace[j*(mydomain->N_()+1)+i] = gridfunlaplace.U().Matx()[i][j];
        }
    }

    FILE *fplaplace;
    fplaplace =fopen("dlaplace_out.bin","wb");
    fwrite(gridlaplace,sizeof(double),len,fplaplace);
    fclose(fplaplace);
    cout << "Saved nabla u to <dlaplace_out.bin>!" << endl;




    // Save the curvebases to the file 'curve_out.bin'
    double stepsize = 0;
    len = (4*2*100);
    double curves[2*len];

    curves[200] = 1.0;

    for(int i=0; i<2*100;i+=2){
        curves[i] = mydomain->Sides()[0]->x(stepsize);
        curves[i+1] = mydomain->Sides()[0]->y(stepsize);

        curves[i+200] = mydomain->Sides()[1]->x(stepsize);
        curves[i+1+200] = mydomain->Sides()[1]->y(stepsize);

        curves[i+400] = mydomain->Sides()[2]->x(stepsize);
        curves[i+1+400] = mydomain->Sides()[2]->y(stepsize);

        curves[i+600] = mydomain->Sides()[3]->x(stepsize);
        curves[i+1+600] = mydomain->Sides()[3]->y(stepsize);

        stepsize+=(1.0/(100.0));
    }

    FILE *curvefile;
    curvefile =fopen("curve_out.bin","wb");
    fwrite(curves,sizeof(double),2*len,curvefile);
    fclose(curvefile);

    cout << "Saved curvebases to <curve_out.bin>!" << endl;

    return 0;
}
