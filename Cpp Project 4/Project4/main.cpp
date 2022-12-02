#include <iostream>
#include <memory>
#include "curvebase.hpp"
#include "xvertical.hpp"
#include "yhorizontal.hpp"
#include "nonconstcurve.hpp"
#include "domain.hpp"
#include "GFkt.hpp"
#include "matrix.hpp"
#include<cstdio>

using namespace std;



int main()
{

    shared_ptr<Yhorizontal> s1 = make_shared<Yhorizontal>(0.0, 5.0, 0.0);
    shared_ptr<Xvertical> s2 = make_shared<Xvertical>(0.0, 5.0, 5.0);
    shared_ptr<Yhorizontal> s3 = make_shared<Yhorizontal>(5.0, 0.0, 5.0);
    shared_ptr<Xvertical> s4 = make_shared<Xvertical>(5.0, 0.0, 0.0);

    // Generate domain
    shared_ptr<Domain> mydomain = make_shared<Domain>(s1,s2,s3,s4);

    mydomain->generate_grid(2,2);

    //mydomain->printGrid();

    GFkt gridfun(mydomain);
    GFkt gridfun2(mydomain);

    Matrix m1(3,3);
    Matrix m2(3,3);

    double v1[9] = {1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0};
    double v2[9] = {10.0,11.0,12.0,13.0,14.0,15.0,16.0,17.0,18.0};

    m1.fillMatrix(v1,9);
    m2.fillMatrix(v2,9);

    //m1.printMatrix();
    //m2.printMatrix();

    cout << "---------------" << endl;

    gridfun.u = m1;
    gridfun2.u = m2;



    //GFkt res = gridfun + gridfun2;
    GFkt res = gridfun * 3.0;
    res.printGFkt();



    return 0;
    /*
    // Generate four curves that define the grid
    shared_ptr<Nonconstcurve> s1 = make_shared<Nonconstcurve>(-10.0, 5.0);
    shared_ptr<Xvertical> s2 = make_shared<Xvertical>(0.0, 3.0, 5.0);
    shared_ptr<Yhorizontal> s3 = make_shared<Yhorizontal>(5.0, -10.0, 3.0);
    shared_ptr<Xvertical> s4 = make_shared<Xvertical>(3.0, 0.0, -10.0);

    // Generate domain
    Domain mydomain = Domain(s1,s2,s3,s4);

    // Generate grid with size of 50x20
    mydomain.generate_grid(50,20);


    cout << "------------" << endl;


    // Save the grid to the file 'grid_out.bin'
    int counter = 0;

    int len = (mydomain.M_()+1)*(mydomain.N_()+1);
    double grid[2*len];
    for(int i=0; i<2*len;i+=2){
        grid[i] = mydomain.X_()[counter];
        grid[i+1] = mydomain.Y_()[counter];
        counter+=1;
    }

    FILE *fp;
    fp =fopen("grid_out.bin","wb");
    fwrite(grid,sizeof(double),2*len,fp);
    fclose(fp);



    // Save the curvebases to the file 'curve_out.bin'
    double stepsize = 0;
    len = (4*2*100);
    double curves[2*len];

    curves[200] = 1.0;

    for(int i=0; i<2*100;i+=2){
        curves[i] = mydomain.Sides()[0]->x(stepsize);
        curves[i+1] = mydomain.Sides()[0]->y(stepsize);

        curves[i+200] = mydomain.Sides()[1]->x(stepsize);
        curves[i+1+200] = mydomain.Sides()[1]->y(stepsize);

        curves[i+400] = mydomain.Sides()[2]->x(stepsize);
        curves[i+1+400] = mydomain.Sides()[2]->y(stepsize);

        curves[i+600] = mydomain.Sides()[3]->x(stepsize);
        curves[i+1+600] = mydomain.Sides()[3]->y(stepsize);

        stepsize+=(1.0/(100.0));
    }

    FILE *curvefile;
    curvefile =fopen("curve_out.bin","wb");
    fwrite(curves,sizeof(double),2*len,curvefile);
    fclose(curvefile);

    cout << "Grid saved to 'grid_out.bin'!" << endl;

    return 0;
    */
}
