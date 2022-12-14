# include "domain.hpp"
# include <iostream>
# include <cmath>

using namespace std;

// Constructor
Domain::Domain(shared_ptr<Curvebase> s1, shared_ptr<Curvebase> s2, shared_ptr<Curvebase> s3, shared_ptr<Curvebase> s4){

    // Four curvebases make up the Domain
    sides[0] = s1;
    sides[1] = s2;
    sides[2] = s3;
    sides[3] = s4;

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


// Destructor
Domain::~Domain(){
    x_.clear();
    y_.clear();
}

// Consistency check
bool Domain::check_consistency(){
    for(int i = 0; i < 4; i++){
        shared_ptr<Curvebase> current = sides[i];
        shared_ptr<Curvebase> next = sides[(i+1)%4];

        // If current endpoint is not close enough to the next start point, the domain is not well defined
        if(!(abs(current->x(1) - next->x(0)) < 0.1 && abs(current->y(1) - next->y(0)) < 0.1)){
            return false;
        }
    }

    return true;
}

// Generate grid
void Domain::generate_grid(int n, int m){
    // If an old grid already exists, change the sizes of the vectors and overwrite its data with the new grid
    if(m < 1 || n < 1) exit(1);
    if(m_ != m && n_ != n){
        x_.resize((m+1) * (n+1));
        y_.resize((m+1) * (n+1));
    }

    m_ = m;
    n_ = n;

    // Step size between grid points
    double h1 = 1.0 / n;
    double h2 = 1.0 / m;

    for(int i = 0; i <= n; ++i){
        for(int j = 0; j <= m; ++j){

            // x coordinate of grid points
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
        }
    }

    cout << "Grid generated!" << endl;
}

// Print function
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

