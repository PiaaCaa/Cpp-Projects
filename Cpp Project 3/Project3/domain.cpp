# include "domain.hpp"
# include <iostream>
# include <cmath>

using namespace std;

// Constructor
Domain::Domain(Curvebase& s1, Curvebase& s2, Curvebase& s3, Curvebase& s4){

    // Four curvebases make up the Domain
    sides[0] = &s1;
    sides[1] = &s2;
    sides[2] = &s3;
    sides[3] = &s4;

    // Check if the curvebases define a domain
    if(check_consistency()){
        cout << ("Domain successfully generated!") << endl;
    } else {
        sides[0] = nullptr;
        sides[1] = nullptr;
        sides[2] = nullptr;
        sides[3] = nullptr;
        cout << "Domain is not consistend!" << endl;
        exit(1);
    }
}

// Consistency check
bool Domain::check_consistency(){
    for(int i = 0; i < 4; i++){
        Curvebase* current = sides[i];
        Curvebase* next = sides[(i+1)%4];

        // If current endpoint is not close enough to the next start point, the domain is not well defined
        if(!(abs(current->x(1) - next->x(0)) < 0.1 && abs(current->y(1) - next->y(0)) < 0.1)){
            return false;
        }
    }

    return true;
}

void Domain::generate_grid(int n, int m){
    if(m < 1 || n < 1) exit(1);
    if(m_ > 0){
        delete[] x_; delete[] y_;
    }

    x_ = new double[(m+1) * (n+1)];
    y_ = new double[(m+1) * (n+1)];
    m_ = m;
    n_ = n;
    double h1 = 1.0 / n;
    double h2 = 1.0 / m;

    cout << "Eckpunkte x: " <<   sides[0]->x(0) << "; " << sides[3]->x(0) << "; " << sides[1]->x(0) << "; " << sides[2]->x(0) << endl;

    cout << "Eckpunkte y: " <<   sides[0]->y(0) << "; " << sides[3]->y(0) << "; " << sides[1]->y(0) << "; " << sides[2]->y(0) << endl;
    for(int i = 0; i <= n; ++i){
        for(int j = 0; j <= m; ++j){
            /*
            x_[i + j*(n+1)] = phi1(i*h1) * sides[3]->x(1-j*h2) + phi2(i*h1) * sides[1]->x(j*h2)
                             +phi1(j*h2) * sides[0]->x(i*h1) + phi2(j*h2) * sides[2]->x(1-i*h1)
                             -phi1(i*h1) * phi1(j*h2) * sides[0]->x(0)
                             -phi1(i*h1) * phi2(j*h2) * sides[3]->x(0)
                             -phi2(i*h1) * phi1(j*h2) * sides[1]->x(0)
                             -phi2(i*h1) * phi2(j*h2) * sides[2]->x(0);


            y_[i + j*(n+1)] = phi1(i*h1) * sides[3]->y(1-j*h2) + phi2(i*h1) * sides[1]->y(j*h2)
                             +phi1(j*h2) * sides[0]->y(i*h1) + phi2(j*h2) * sides[2]->y(1-i*h1)
                             -phi1(i*h1) * phi1(j*h2) * sides[0]->y(0)
                             -phi1(i*h1) * phi2(j*h2) * sides[3]->y(0)
                             -phi2(i*h1) * phi1(j*h2) * sides[1]->y(0)
                             -phi2(i*h1) * phi2(j*h2) * sides[2]->y(0);
             */

             x_[i + j*(n+1)] = phi1(i*h1) * sides[3]->x(1-j*h2) + phi2(i*h1) * sides[1]->x(j*h2)
                              +phi1(j*h2) * sides[0]->x(i*h1) + phi2(j*h2) * sides[2]->x(1-i*h1)
                              -phi1(i*h1) * phi1(j*h2) * sides[0]->x(0)
                              -phi1(i*h1) * phi2(j*h2) * sides[3]->x(0)
                              -phi2(i*h1) * phi1(j*h2) * sides[1]->x(0)
                              -phi2(i*h1) * phi2(j*h2) * sides[2]->x(0);


            y_[i + j*(n+1)] = phi1(i*h1) * sides[3]->y(1-j*h2) + phi2(i*h1) * sides[1]->y(j*h2)
                             +phi1(j*h2) * sides[0]->y(i*h1) + phi2(j*h2) * sides[2]->y(1-i*h1)
                             -phi1(i*h1) * phi1(j*h2) * sides[0]->y(0)
                             -phi1(i*h1) * phi2(j*h2) * sides[3]->y(0)
                             -phi2(i*h1) * phi1(j*h2) * sides[1]->y(0)
                             -phi2(i*h1) * phi2(j*h2) * sides[2]->y(0);


            cout << "Index: " << i + j*(n+1) << ", x: " << x_[i + j*(n+1)] << ", y:" << y_[i + j*(n+1)] << endl;
            cout << -phi1(i*h1) * phi2(j*h2) * sides[3]->y(0)
                             -phi2(i*h1) * phi1(j*h2) * sides[1]->y(0) << endl;

            // cout <<  phi1(i*h1) * sides[3]->y(1-j*h2) << endl;
            //exit(1);



        }
    }

    cout << "Grid generated!" << endl;
}


void Domain::printGrid(){
    cout << "x:" << endl;
    for(int i = 0; i <= n_; ++i){
        for(int j = 0; j <= m_; ++j){
            cout << x_[i + j*(n_+1)] << "   ";
        }
        cout << endl;
    }

    cout << endl << "y:" << endl;

    for(int i = 0; i <= n_; ++i){
        for(int j = 0; j <= m_; ++j){
            cout << y_[i + j*(n_+1)] << "   ";
        }
        cout << endl;
    }
}

