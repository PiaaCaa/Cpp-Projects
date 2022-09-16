#ifndef EX2_H_INCLUDED
#define EX2_H_INCLUDED


//double f(double );
typedef double (*FunctionPointer)(double);
double I(FunctionPointer, double , double );
double I_2(FunctionPointer, double , double );
double ASI(FunctionPointer, double , double  , double );



#endif // EX2_H_INCLUDED



