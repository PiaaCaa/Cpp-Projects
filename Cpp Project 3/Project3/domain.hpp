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

public:
    Domain(const Curvebase s1, const Curvebase s2, const Curvebase s3, const Curvebase s4);
    void generate_grid(int n, int m);

};

#endif
