#include <cmath>
#include "vec.h"

// You are defining a system of N initial-value problems
//  - the maximum is a system of 12 1st-order IVPs
const std::size_t N{ 12 };   // must be <= 12

// Function declarations
vec<N> f( double t, vec<N> y );
double phase( double f );

// Function definitions
vec<N> f( double t, vec<N> y ) {
    // This is not a good filter...
    //  - the filter must depend on 'fc'
    const double R{1.0};
    const double C{1.0/(2.0*M_PI*R*fc)};
    
    vec<N> ret = vec<N>(0);
    for (int x = 0; x < N-1; x++) {
        ret[x] = (y[x+1]/(R*C)) - (y[x]/(R*C));
    }
    ret[11] = (v(t) - y[11])/(R*C);
    return ret;
}

// Calculate and return the phase shift of the response
// for a function that has a frequency of 'f'
//  - this likely will depend on the critical frequencey 'fc'
double phase( double f ) {
    const double R{1.0};
    const double C{1.0/(2.0*M_PI*R*fc)};

    return (-std::atan( 2*M_PI*f*R*C )*12);
}
