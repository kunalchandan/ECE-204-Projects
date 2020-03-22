// This is a test and demonstration of the features of
// the 'vec' class. In this case, all the vectors that
// are defined are 3 dimensional.

#include "vec.h"
#include <iostream>

/********************************
 * MUST BE COMPILED WITH C++ 11 *
 ********************************/

// This is a test file for the 'vec' class

// Function declarations
int main();

// Function definitions
int main() {
    vec<3> u{1, -1, 0};
    vec<3> v{1.2, 1.3, 1.4};
    vec<3> w(1.0);

    std::cout << " u = " <<      u  << std::endl;
    std::cout << "-u = " <<    (-u) << std::endl;
    std::cout << " v = " <<      v  << std::endl;
    std::cout << " w = " <<      w  << std::endl;
    std::cout << "3v = " << (3.0*v) << std::endl;
    std::cout << "3v = " << (v*3.0) << std::endl;
    std::cout << "u + v = " << (u + v) << std::endl;
    std::cout << "u - v = " << (u - v) << std::endl;
    std::cout << "u == v: " << (u == v) << std::endl;
    std::cout << "u != v: " << (u != v) << std::endl;
    std::cout << "u == u: " << (u == u) << std::endl;
    std::cout << "u != u: " << (u != u) << std::endl;

    std::cout << "||u|| = " << u.norm()  << std::endl;
    std::cout << "||u|| = " << vec<3>::norm( u )  << std::endl;

    std::cout << "u * v = " << (u * v) << std::endl;
    std::cout << "u * u = " << (u * u) << std::endl;
    std::cout << "sqrt(u * u) = " << std::sqrt(u * u) << std::endl;

    return 0;
}
