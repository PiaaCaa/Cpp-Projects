# include "domain.hpp"
# include <iostream>
# include <cmath>

using namespace std;

Domain::Domain(Curvebase& s1, Curvebase& s2, Curvebase& s3, Curvebase& s4){

    sides[0] = &s1;
    sides[1] = &s2;
    sides[2] = &s3;
    sides[3] = &s4;

    if(check_consistency()){
        cout << ("Domain successfully generated!") << endl;
    } else {
        sides[0] = nullptr;
        sides[1] = nullptr;
        sides[2] = nullptr;
        sides[3] = nullptr;
        cout << "Domain is not consistend!" << endl;
        exit(1);
        //throw "Domain is not well defined by the given curvebases!";
    }
    // CHECK FOR CONSISTENCY!

    // TODO

    // Question: consistency check hourglass?
    // Question: Orientation?
}


bool Domain::check_consistency(){
    for(int i = 0; i < 4; i++){
        Curvebase* current = sides[i];
        Curvebase* next = sides[(i+1)%4];

        if(!(abs(current->x(1) - next->x(0)) < 0.1 && abs(current->y(1) - next->y(0)) < 0.1)){
            return false;
        }
    }

    return true;
}

void Domain::generate_grid(int n, int m){
    // TODO
}
