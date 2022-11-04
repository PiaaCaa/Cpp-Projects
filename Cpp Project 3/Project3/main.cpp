#include <iostream>
#include "curvebase.hpp"
#include "xvertical.hpp"
#include "yhorizontal.hpp"

using namespace std;


// double func1()



int main()
{
    cout << "Hello world!" << endl;

    Xvertical t = Xvertical(1,2,3);

    t.printXvertical();


    Yhorizontal t2 = Yhorizontal(1,2,3);
    t2.printYhorizontal();

    return 0;
}
