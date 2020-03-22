#include <iostream>
#include <cmath>
#include "ivp.h"
#include "vec.h"

// Function declarations
int main();

#include "has_converged.h"

int main() {
    std::cout.precision( 6 );
    std::clog.precision( 16 );
    std::clog.setstate(std::ios_base::failbit);
    std::cout << "mep " << has_converged(std::pow(10.0, -6)) << std::endl;

}