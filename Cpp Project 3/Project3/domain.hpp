#include "curvebase.hpp"
#ifndef DOMAIN_HPP
#define DOMAIN_HPP


class Domain{

private:
    Curvebase* sides[4];

    double* x_ = nullptr;
    double* y_ = nullptr;

    // Question: Phi?

    int n_;
    int m_;

    bool check_consistency();

    double phi1(double s){return 1-s;};
    double phi2(double s){return s;};

public:
    Domain(Curvebase& s1, Curvebase& s2, Curvebase& s3, Curvebase& s4);
    void generate_grid(int n, int m);
};

#endif
