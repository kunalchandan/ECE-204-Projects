////// #include "vec.h"
#include "ivp.h"
#include "data.h"
#include <iostream>
#include <cassert>

/*
Found for Default
10^-0, 0.3699497219
10^-1, 0.6040013553
10^-2, 0.8380529953
10^-3, 1.072104706
10^-4, 1.306156977
10^-5, 1.540212992
10^-6, 1.774303329
10^-7, 2.008800204
10^-8, 2.246967632
10^-9, 2.600516949
*/

// Function declarations
double has_converged( double max_error );
vec<15> f( double t, vec<15> w );
// You will pass 't' to ua(t) and ub(t); for everything else, you
// will use w[1]
// Function definitions

double err_max(vec<15> w, double diff_err) {
    double err_max{0.0};
    for (uint i = 0; i < 15; i++) {
        double err = ua(0) + (((i+1)/16.0)*(ub(0)-ua(0)));
        err = std::fabs(w[i] - err);
        if (err > err_max) {
            err_max = err;
        }
    }
    return std::fabs(err_max) - diff_err;
}

double bracketed_secant(ivp<vec<15>> u, double max_error, double ep_fac=std::pow(10, -8)) {
    double epsilon = max_error*ep_fac;
    double a{0.0};
    double b{0.0};
    double c{0.0};
    // find lower and upper bound
    while (err_max(u(b), max_error) > 0.0) {
        a = b;
        c = b;
        b += 0.1;
    }
    // begin bracketed secant
    double error{err_max(u(c), max_error)};
    uint conv_count = 0;
    while (std::fabs(error) > epsilon) {
        // Prevent infinite loop by increasing size of epsilon
        conv_count++;
        if (conv_count > 10000) {
            return bracketed_secant(u, max_error, ep_fac*2);
        }
        double ea = err_max(u(a), max_error);
        double eb = err_max(u(b), max_error);

        c = (a*eb - b*ea)/(eb - ea);
        error = err_max(u(c), max_error);

        // Update whichever endpoint with same sign
        if (std::signbit(c) == std::signbit(a)) {
            a = c;
        } else {
            b = c;
        }
    }
    return c;
}


double secant_method(ivp<vec<15>> u, double max_error, double ep_fac=std::pow(10, -8)) {
    double epsilon = max_error*ep_fac;

    double tn = 0.0000;
    double tp = 0.0010;
    double en = err_max(u(tn), max_error);
    double ep = err_max(u(tp), max_error);

    double et;
    while (std::fabs(ep) > epsilon) {
        // Solve Secant method
        // Apply rule

        double tt = ((tn*ep) - (tp*en))/(ep - en);
        try {
            if (std::isinf(tt)) {
                throw std::out_of_range("INF");
            } else if (std::isnan(tt)) {
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

double has_converged( double max_error ) {
    assert( max_error > 0 );
    // Your implementation here (some hints included):
    // - you can call all globally defined functions in 'data.h'
    // and all globally defined constants
    vec<15> initial_state{};
    for (double x = a + ((b-a)/16.0), i = 0; i < 15; x += (b-a)/16.0, i++) {
        initial_state[i] = u0(x);
    }
    // Initialize your initial state vector.
    ivp<vec<15>> u{ f, t0, initial_state, H_INIT, H_RANGE, EPS_ABS, vec<15>::norm };

    // u(3.2) returns a vec<15> with the temperatures at the
    // 15 intermediate points at time 3.2
    double t = 0;
    try {
        t = secant_method(u, max_error);
    } catch (std::out_of_range o) {
        t = bracketed_secant(u, max_error);
    }
    return t;
}

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

double convergence( double max_error ) {
    assert( max_error > 0 );
    double epsilon = max_error*std::pow(10, -7);
    // Your implementation here (some hints included):
    // - you can call all globally defined functions in 'data.h'
    // and all globally defined constants
    vec<15> initial_state{};
    for (double x = a + ((b-a)/16.0), i = 0; i < 15; x += (b-a)/16.0, i++) {
        initial_state[i] = u0(x);
    }
    // Initialize your initial state vector.
    ivp<vec<15>> u{ f, t0, initial_state, H_INIT, H_RANGE, EPS_ABS, vec<15>::norm };

    // u(3.2) returns a vec<15> with the temperatures at the
    // 15 intermediate points at time 3.2
    
    for (double d = 0.1; d < 4.0; d += 0.01) {
        std::cout << err_max(u(d), 0) << " ";
    }
    return 0.0;
}