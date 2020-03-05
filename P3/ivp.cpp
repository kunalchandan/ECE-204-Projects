// This file is a test of the IVP solver
//  - two differenatl equaitons are defined:
//      y'(t) = -y(t) with y(0) = 1
//          - solution: exp(-t)
//      y''(t) + y(t) = 0 with y(0) = 1 and y'(0) = 0
//          - solution: cos(t)
//
//  - both of these are time-independent IVPs

#include <iostream>
#include <cmath>

#include "ivp.h"
#include "vec.h"

// Function declarations
int main();
double f1( double t, double y );
vec<2> f2( double t, vec<2> y );


// Function definitions
double f1( double t, double y ) {
    return -y;
}

vec<2> f2( double t, vec<2> y ) {
    return vec<2>{
         y[1],
        -y[0]
    };
}

int main() {
    std::cout.precision( 16 );
    std::clog.precision( 16 );

    ivp<double> y1{ f1, 0.0, 1.0, 0.1, std::make_pair( 1e-5, 0.2 ), 1e-5 };

    for ( double t{0.0}; t < 5.1; t += 0.1 ) {
       std::cout << "y1(" << t << ") = " << y1( t ) << " (= "
	         << std::exp( -t ) << ")" << std::endl;
    }

    ivp<vec<2>> y2{ f2, 0.0, vec<2>{ 1.0, 0.0 }, 0.1,
	            std::make_pair( 1e-5, 0.2 ), 1e-8, vec<2>::norm };

    for ( double t{0.0}; t < 6.29; t += 0.01 ) {
       std::cout << "y2(" << t << ") = " << y2( t )[0] << " (= "
	         << std::cos( t ) << ")" << std::endl;
    }

    double const PI{ acos( -1.0 ) };

    for ( double n{0.0}; n <= 16; ++n ) {
        std::cout << "y2(" << n << "*pi/8) = " << y2( PI*n/8.0 )[0]
		  << " (= " << std::cos( PI*n/8.0 ) << ")" << std::endl;
    }

    return 0;
}
