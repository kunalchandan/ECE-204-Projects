#include <iostream>
#include <cmath>
#include "ivp.h"
#include "vec.h"

// Function declarations
int main();

#include "has_converged.h"

int main() {
    std::cout.precision( 10 );
    std::clog.precision( 16 );
    std::clog.setstate(std::ios_base::failbit);
    for (int x = 0; x < 10; x ++) {
        std::cout << "10^-"<< x << ", " << has_converged(std::pow(10.0, -x)) << std::endl;

    }
    // convergence(1);
}