#include <iostream>
#include "NFET.h"
using namespace std;

// main
int main()
{

    // prints hello world
    NFET fet(1.8e-6, 3.6e-6, "this_is_a_new_fet");
    fet.generate_curves();

    return 0;
}