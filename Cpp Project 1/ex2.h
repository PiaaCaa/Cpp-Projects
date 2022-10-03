#ifndef EX2_H_INCLUDED
#define EX2_H_INCLUDED


// Defining new type FunctionPointer which is used for ASI function
// Points to a function which takes a double and returns a double
typedef double (*FunctionPointer)(double);

// I function as described by the ASI algorithm
double I(FunctionPointer, double , double );


// I_2 function as described by the ASI algorithm
double I_2(FunctionPointer, double , double );

// Adaptive Simpson Integration algorithm function
double ASI(FunctionPointer, double , double  , double );



#endif // EX2_H_INCLUDED



