#include <iostream>
#include "curvebase.hpp"
#include "xvertical.hpp"
#include "yhorizontal.hpp"
#include "nonconstcurve.hpp"
#include "domain.hpp"
#include<cstdio>

using namespace std;


// double func1()



int main()
{


    // Yhorizontal s1 = Yhorizontal(0.0, 5.0, 0.0);
    Xvertical s2 = Xvertical(0.0, 5.0, 5.0);
    Yhorizontal s3 = Yhorizontal(5.0, -10.0, 5.0);
    Xvertical s4 = Xvertical(5.0, 0.0, -10.0);

    Nonconstcurve s1 = Nonconstcurve(-10.0, 5.0); // Not consistent???

    cout << s1.x(0) << endl;

    cout << s1.x(1) << endl;

    cout << s1.y(0) << endl;

    cout << s1.y(1) << endl;



    Domain mydomain = Domain(s1,s2,s3,s4);




    return 0;



    //Yhorizontal ycurve = Yhorizontal(-10.0, 5.0, 3.0);

    Nonconstcurve ycurve = Nonconstcurve(-10.0, 5.0);

    int len = (int) 1/0.01 + 1;
    double p[len];
    double curve[2*len];

    int counter = 0;
    for(double i=0; i<=1.01; i+=0.01){
        p[counter] = i;

        //cout << counter << ", i: " << i << endl;
        counter++;
    }


    counter = 0;
    for(int i=0; i<2*len-1;i+=2){
        curve[i] = ycurve.x(p[counter]);
        curve[i+1] = ycurve.y(p[counter]);
        //cout << ycurve.y(p[counter]) << endl;
        counter+=1;
    }

    FILE *fp;
    fp =fopen("outfile.bin","wb");
    fwrite(curve,sizeof(double),2*len,fp);
    fclose(fp);


    return 0;

    double n=3;
    double m=3;

    double myvec[9];

    for(int i = 0; i < n*m; i++){
        myvec[i] = 5.0;
    }

    for(int i = 0; i < n*m; i++){
        cout << myvec[i] << endl;
    }


    //FILE *fp;
    //fp =fopen("outfile.bin","wb");
    //fwrite(myvec,sizeof(double),m*n,fp);
    //fclose(fp);
    return 0;
}
