# include "domain.hpp"

Domain::Domain(const Curvebase s1, const Curvebase s2, const Curvebase s3, const Curvebase s4){
    sides[0] = s1;
    sides[1] = s2;
    sides[2] = s3;
    sides[3] = s4;

    // CHECK FOR CONSISTENCY!

    // TODO

    // Question: consistency check hourglass?
    // Question: Orientation?
}


Domain::generate_grid(int n, int m){
    // TODO
}
