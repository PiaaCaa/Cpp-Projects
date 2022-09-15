#include <iostream>
#include <cmath>

//TODOO
// check if its better to use integeres since x is an integer
//avoid explicit evaluation of factorial

//TODO use horners scheme in the right way

//horners scheme to calculate exponentials
double horner_exponential(double x, int n){
    if (n == 0 )
        return 1;
    double result = x;
    for (int i = 1; i < n; i++ ){
        result *= x;
    }
    return result;
}

//TODO change to another "implicit?" evaluation
// idea: in the sum one can reuse the other facotials
unsigned int factorial(int n)
{
    if (n == 0){
       return 1;
    }
    return n * factorial(n - 1);
}

double sinTaylor(int N, double x){
    double res = 0;
    for (int i=0; i < N; i++){
        res += horner_exponential(-1, i) *  ((horner_exponential(x,2*i+1))/(factorial(2*i + 1)));

        //std::cout << "pow function: " << pow(x,2*i+1) << " horner: " << horner_exponential(x,2*i+1) << " diff: " << std::abs(pow(x,2*i+1) - horner_exponential(x,2*i+1)) << std::endl;
    }
    return res;
}

//TODO check overflow
double cosTaylor(int N, double x){
    double res = 0;
    for (int i=0; i < N; i++){
        res += horner_exponential(-1, i) *  ((horner_exponential(x,2*i))/(factorial(2*i)));
    }
    return res;
}


double error(){
    double x_s[] = {-1, 1, 2, 3, 5, 10};
    int N_s[] = {1,3,6, 10};

    int num_N = sizeof(N_s)/sizeof(N_s[0]);
    int num_x = sizeof(x_s)/sizeof(x_s[0]);

    //iterate over different x_s
    for (int j = 0; j < num_x; j++){
        //iterate over number of Ns
        for (int i = 0; i< num_N; i++ ){
            double err_sin = std::abs(sin(x_s[j])-sinTaylor(N_s[i],x_s[j]));
            double err_cos = std::abs(cos(x_s[j])-cosTaylor(N_s[i],x_s[j]));
            std::cout << "N: " << N_s[i] << " x: " << x_s[j] << " error sin: " << err_sin << std::endl;
            std::cout << "N: " << N_s[i] << " x: " << x_s[j] << " error cos: " << err_cos << std::endl;
        }
    }
    return 0;
}
