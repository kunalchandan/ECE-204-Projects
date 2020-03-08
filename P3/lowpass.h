#include <cmath>
#include "vec.h"

// You are defining a system of N initial-value problems
//  - the maximum is a system of 12 1st-order IVPs
const std::size_t N{ 12 };   // must be <= 12
const vec<N> coeffs = {
    1.00000000000000,
    7.66129757675302,
    29.3477402547921,
    74.0762151660211,
    136.874998035601,
    194.718685858251,
    218.468729173037,
    194.718685871588,
    136.874998054604,
    74.0762151618200,
    29.3477402733912,
    7.66129757966929,
};

// Function declarations
vec<N> f( double t, vec<N> y );
double phase( double f );

// Function definitions
vec<N> f( double t, vec<N> y ) {
    // This is not a good filter...
    //  - the filter must depend on 'fc'
    const double R{1.0};
    const double C{1.0/(2.0*M_PI*R*fc)};
    const double WC{2.0*M_PI*fc};
    
    // vec<N> w = vec<N>(0);

    ////////// 12th order Cascaded RC circuit //////////
    // for (int x = 0; x < N-1; x++) {
    //     w[x] = (y[x+1]/(R*C)) - (y[x]/(R*C));
    // }
    // w[N-1] = (v(t) - y[N-1])/(R*C);
    ////////////////////////////////////////////////////

    ///////////// 2th Butterworth circuit //////////////
    // vec<N> w = {
    //     y[1],
    //     (v(t)*std::pow(WC, 2)) + (-1*y[0]*std::pow(WC, 2)) + (-1*std::sqrt(2)*y[1]*WC)
    // };
    ////////////////////////////////////////////////////
    vec<N> w = vec<N>();
    for (int x = 0; x < N-1; x++) {
        w[x] = y[x+1];
    }
    // Calculate last one
    w[11] = v(t) * std::pow(WC, N);
    for (int x = 0; x < N; x++) {
        w[11] -= coeffs[x] * y[x] * std::pow(WC, N-x);
    }
    return w;
}

// Calculate and return the phase shift of the response
// for a function that has a frequency of 'f'
//  - this likely will depend on the critical frequencey 'fc'
double phase( double f ) {
    const double R{1.0};
    const double C{1.0/(2.0*M_PI*R*fc)};

    return (-std::atan( 2*M_PI*f*R*C )*12);
}
