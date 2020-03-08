#include <iostream>
#include <cmath>
#include "ivp.h"
#include "vec.h"

// The critical frequency
double const fc{ 0.5 };

// Function declarations
int main();
double v( double t );

#include "lowpass.h"

// Input signal
double v( double t ) {
    return std::sin(t) + std::sin(10*t);
}

int main() {
    std::cout.precision( 6 );
    std::clog.precision( 16 );
    // std::cout.setstate(std::ios_base::failbit);

    // 'y(t)[0]' is assumed to be the output signal at time 't'
    //  - initial state is all zeros
    ivp<vec<N>> y{ f, 0.0, vec<N>{}, 0.05,
	           std::make_pair( 1e-5, 0.1 ), 1e-5, vec<N>::norm };

    double t_max{ 20.0 };
    double step{ 0.1 };

    // Calculate this once, so that it finds an approximation
    // for all values on the interval [0, t_max]
    y( t_max );

    // std::cout.clear();
    // Print out the t-values
    std::cout << "ts = [0.0";
    for ( double t{step}; t < t_max + 0.5*step; t += step ) {
       std::cout << " " << t;
    }
    std::cout << "];" << std::endl;

    // Print out the response (i.e., y(t[k])[0])
    std::cout << "ys = [0.0";
    for ( double t{step}; t < t_max + 0.5*step; t += step ) {
       std::cout << " " << y(t)[0];
    }
    std::cout << "];" << std::endl;

    std::cout << "phase = " << phase( 1.0/(2.0*M_PI) ) << ";" << std::endl;

    return 0;
}
