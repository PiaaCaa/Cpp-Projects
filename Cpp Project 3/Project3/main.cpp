#include <iostream>
#include "curvebase.hpp"
#include "xvertical.hpp"
#include "yhorizontal.hpp"
#include "nonconstcurve.hpp"
#include "domain.hpp"
#include<cstdio>

using namespace std;



int main()
{

    // Generate four curves that define the grid
    Nonconstcurve s1 = Nonconstcurve(-10.0, 5.0);
    Xvertical s2 = Xvertical(0.0, 3.0, 5.0);
    Yhorizontal s3 = Yhorizontal(5.0, -10.0, 3.0);
    Xvertical s4 = Xvertical(3.0, 0.0, -10.0);

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
}
