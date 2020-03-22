#include "vec.h"
#include "ivp.h"
#include "data.h"
#include <iostream>
#include <cassert>


// Function declarations
double has_converged( double max_error );
vec<15> f( double t, vec<15> w );
// You will pass 't' to ua(t) and ub(t); for everything else, you
// will use w[1]
// Function definitions

vec<15> f( double t, vec<15> w ) {
    vec<15> dw{0};
    for (uint i = 0; i < 15; i ++) {
        if (i == 0) {
            dw[i] = kappa*(ua(t)  - (2*w[i]) + w[i+1]);
        } else if (i < 14) {
            dw[i] = kappa*(w[i-1] - (2*w[i]) + w[i+1]);
        } else {
            dw[i] = kappa*(w[i-1] - (2*w[i]) + ub(t));
        }
        dw[i] = dw[i]*16*16;
    }
    return dw;
}

std::pair<double, uint> err_max(vec<15> w) {
    double err_max{0.0};
    uint index = 0;
    for (uint i = 0; i < 15; i++) {
        double err = ua(0) + (((i+1)/16.0)*(ub(0)-ua(0)));
        std::cout << err << " ";
        err = std::fabs(w[i] - err);
        if (err > err_max) {
            err_max = err;
            index = i;
        }
    }
    std::cout << std::endl;
    return std::make_pair(err_max, index);
}

double has_converged( double max_error ) {
    assert( max_error > 0 );
    double epsilon = max_error*std::pow(10, -3);
    // Your implementation here (some hints included):
    // - you can call all globally defined functions in 'data.h'
    // and all globally defined constants
    vec<15> initial_state{};
    // Initialize your initial state vector.
    ivp<vec<15>> u{ f, t0, initial_state, H_INIT, H_RANGE, EPS_ABS, vec<15>::norm };

    // u(3.2) returns a vec<15> with the temperatures at the
    // 15 intermediate points at time 3.2
    
    double t = 0.0;
    std::pair<double, uint> p = err_max(u(t));
    while ((p.first > max_error + epsilon) || (p.first < max_error - epsilon)) {
        // solve e^{-kappa*t} = target
        p = err_max(u(t));
        double target = ua(0) + ((p.second/16.0)*ub(0));
        t += (std::log(u(t)[p.second] + target) - std::log(max_error))/(kappa);
        std::cout << "mep " << t << std::endl;
    }
    return t;
}
