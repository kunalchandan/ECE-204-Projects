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
    double h = (b-a)/16;
    for (uint i = 0; i < 15; i ++) {
        if (i == 0) {
            dw[i] = kappa*(ua(t)  - (2*w[i]) + w[i+1]);
        } else if (i <= 13) {
            dw[i] = kappa*(w[i-1] - (2*w[i]) + w[i+1]);
        } else {
            dw[i] = kappa*(w[i-1] - (2*w[i]) + ub(t));
        }
        dw[i] = dw[i]/h/h;
    }
    return dw;
}

double err_max(vec<15> w, double diff_err) {
    double err_max{0.0};
    uint index = 0;
    for (uint i = 0; i < 15; i++) {
        double err = ua(0) + (((i+1)/16.0)*(ub(0)-ua(0)));
        err = std::fabs(w[i] - err);
        if (err > err_max) {
            err_max = err;
            index = i;
        }
    }
    return err_max - diff_err;
}

double has_converged( double max_error ) {
    assert( max_error > 0 );
    double epsilon = max_error*std::pow(10, -7);
    // Your implementation here (some hints included):
    // - you can call all globally defined functions in 'data.h'
    // and all globally defined constants
    vec<15> initial_state{};
    // Initialize your initial state vector.
    ivp<vec<15>> u{ f, t0, initial_state, H_INIT, H_RANGE, EPS_ABS, vec<15>::norm };

    // u(3.2) returns a vec<15> with the temperatures at the
    // 15 intermediate points at time 3.2
    
    double tn = 0.0001;
    double tp = 0.0010;
    double en = err_max(u(tn), max_error);
    double ep = err_max(u(tp), max_error);

    double et;
    while ((ep > max_error + epsilon) || (ep < max_error - epsilon)) {
        // Solve Secant method
        // Apply rule

        double tt = ((tn*ep) - (tp*en))/(ep - en);
        try {
            // std::cout << "mep " << tt << "  err " << ep.first << std::endl;
            if (tt != tt) {
                return tp;
            }
            et = err_max(u(tt), max_error);
        } catch (std::runtime_error r) {
            return tp;
        }
        tn = tp;
        tp = tt;
        en = ep;
        ep = et;
    }
    return tp;
}

double convergence( double max_error ) {
    assert( max_error > 0 );
    double epsilon = max_error*std::pow(10, -7);
    // Your implementation here (some hints included):
    // - you can call all globally defined functions in 'data.h'
    // and all globally defined constants
    vec<15> initial_state{};
    // Initialize your initial state vector.
    ivp<vec<15>> u{ f, t0, initial_state, H_INIT, H_RANGE, EPS_ABS, vec<15>::norm };

    // u(3.2) returns a vec<15> with the temperatures at the
    // 15 intermediate points at time 3.2
    
    for (double d = 0.1; d < 4.0; d += 0.01) {
        std::cout << err_max(u(d), 0) << " ";
    }
    return 0.0;
}