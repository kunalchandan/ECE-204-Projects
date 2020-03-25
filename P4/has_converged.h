////// #include "vec.h"
#include "ivp.h"
#include "data.h"
#include <iostream>
#include <cassert>


// Function declarations
double bracketed_secant(ivp<vec<15>> u, double max_error, double ep_fac=std::pow(10, -8));
double secant_method(ivp<vec<15>> u, double max_error, double ep_fac=std::pow(10, -8));
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
    // Your implementation here (some hints included):
    // - you can call all globally defined functions in 'data.h'
    // and all globally defined constants
    vec<15> initial_state{};
    for (double x = a + ((b-a)/16.0); x < b; x += (b-a)/16.0) {
        initial_state[x] = u0(x);
    }
    // Initialize your initial state vector.
    ivp<vec<15>> u{ f, t0, initial_state, H_INIT, H_RANGE, EPS_ABS, vec<15>::norm };

    // u(3.2) returns a vec<15> with the temperatures at the
    // 15 intermediate points at time 3.2
    double t = 0;
    try {
        double diff = 0;
        t = bracketed_secant(u, max_error);
        diff = t;
        std::cout << " bs " << t;
        t = secant_method(u, max_error);
        std::cout << " sm ";
        diff -= t;
        std:: cout << diff << "    diff  " ; 
    } catch (std::out_of_range o) {
        std::cout << " bs ";
    }
    return t;
}

double bracketed_secant(ivp<vec<15>> u, double max_error, double ep_fac=std::pow(10, -8)) {
    double epsilon = max_error*ep_fac;
    double a{0.0};
    double b{0.0};
    double c{0.0};
    // find lower and upper bound
    while (err_max(u(b), max_error) > 0.0) {
        b += 0.1;
        if (err_max(u(b), max_error) > 0.0) {
            a = b;
            c = b;
        }
    }
    // begin bracketed secant
    double error{err_max(u(c), max_error)};
    uint conv_count = 0;
    while ((error > epsilon) || (error < -epsilon)) {
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
    double epsilon = max_error*std::pow(10, -9);

    double tn = 0.0001;
    double tp = 0.0010;
    double en = err_max(u(tn), max_error);
    double ep = err_max(u(tp), max_error);

    double et;
    while ((ep > epsilon) || (ep < -epsilon)) {
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

double convergence( double max_error ) {
    assert( max_error > 0 );
    double epsilon = max_error*std::pow(10, -7);
    // Your implementation here (some hints included):
    // - you can call all globally defined functions in 'data.h'
    // and all globally defined constants
    vec<15> initial_state{};
    for (double x = a + ((b-a)/16.0); x < b; x += (b-a)/16.0) {
        initial_state[x] = u0(x);
        // std::cout << initial_state[x] << x << " ";
    }
    // std::cout << std::endl;
    // Initialize your initial state vector.
    ivp<vec<15>> u{ f, t0, initial_state, H_INIT, H_RANGE, EPS_ABS, vec<15>::norm };

    // u(3.2) returns a vec<15> with the temperatures at the
    // 15 intermediate points at time 3.2
    
    for (double d = 0.1; d < 4.0; d += 0.01) {
        std::cout << err_max(u(d), 0) << " ";
    }
    return 0.0;
}