#include "ivp.h"

#include <vector>
#include <queue>
#include <tuple>
#include <utility>
#include <cassert>
#include <iostream>
#include <cmath>
#include <algorithm>

/**********************************************************
 * ivp::ivp( ... )
 *
 * This constructor is when the norm takes a parameter
 * that is passed by value (and not by constant reference)
 *  - the 'use_constant_reference_' member
 *    variable is assigned 'false'
 *  - the default value of 'norm_' is 'std::abs'
 **********************************************************/

template <typename T>
ivp<T>::ivp( T f( double t, T y ),
             double t0,
             T y0,
             double h,
             std::pair<double, double> h_range,
             double eps_abs,
             double norm( T y ) ):
f_{ f },
t_vec_(1),
y_vec_(1),
d_vec_(1),
h_{ h },
h_min_{ h_range.first },
h_max_{ h_range.second },
eps_abs_{ eps_abs },
norm_{ .value_ = norm },
use_constant_reference_{ false } {
    assert( h_ > 0 );
    assert( h_min_ > 0 );
    assert( h_max_ >= h_min_ );
    assert( eps_abs_ > 0 );
    t_vec_[0] = t0;
    y_vec_[0] = y0;
    d_vec_[0] = f_( t0, y0 );

}

/**********************************************************
 * ivp::ivp( ... )
 *
 * This constructor is when the norm takes a parameter
 * that is passed by constant reference (and not by value)
 *  - the 'use_constant_reference_' member
 *    variable is assigned 'true'
 **********************************************************/

template <typename T>
ivp<T>::ivp( T f( double t, T y ),
             double t0,
             T y0,
             double h,
             std::pair<double, double> h_range,
             double eps_abs,
             double norm( T const &y ) ):
f_{ f },
t_vec_(1),
y_vec_(1),
d_vec_(1),
h_{ h },
h_min_{ h_range.first },
h_max_{ h_range.second },
eps_abs_{ eps_abs },
norm_{ .constant_reference_ = norm },
use_constant_reference_{ true } {
    assert( h_ > 0 );
    assert( h_min_ > 0 );
    assert( h_max_ >= h_min_ );
    assert( eps_abs_ > 0 );
    t_vec_[0] = t0;
    y_vec_[0] = y0;
    d_vec_[0] = f_( t0, y0 );

}

/**********************************************************
 * T operator()( double t )
 *
 * Given a time 't', this function finds an approximation
 * to y(t):
 *
 *   First it looks at the approximations we have found
 *   so far:  t[0], t[1], ..., t[n - 1].
 *      If t[n - 1] < t, then we use Dormand-Prince to
 *      extend our approximations until we have found
 *      an approximation at a point t[N - 1] such that
 *      t[N - 1] >= 't'.
 *
 *   Next,
 *      If we are lucky and t[k] = 't' for some 
 *      index 'k', we then return the corresponding y[k].
 *      Otherwise, we find an interval t[k - 1] < t < t[k]
 *      and find an interpolating cubic polynomial that
 *      matches both the values and slopes at these two
 *      points and evaluates that polynomial at 't'.
 **********************************************************/

template <typename T>
T ivp<T>::operator() ( double t ) {
    if ( t < t_vec_[0] ) {
        throw std::runtime_error( "Invalid: t < t0" );
    }

    // If vector 't_vec_' contains the t-values for which we have
    // approximations, so if the requested 't' is greater than
    // the most recent t-value approximated (t_vec_.back()), we
    // must continue approximating until we get a t-value equal
    // to or greater than 't'

    if ( t > t_vec_.back() ) {
        approximate_to_t( t );
    }

    // Make sure the last t-value now equals or exceeds 't'
    assert( t_vec_.back() >= t );

    // Deal with the special case that we are asking for the initial value
    //  - this simplifies the subsequent code, even if this is a rare occurance
    if ( t_vec_[0] == t ) {
        return y_vec_[0];
    }

    // Calculate the index of the first element in the range 't_vec_' which compares greater than 't'
    //  thus, t_vec_[k - 1] <= 't' and t_vec_[k] > 't'
    std::ptrdiff_t k{ std::distance(
        t_vec_.begin(), std::upper_bound( t_vec_.begin(), t_vec_.end(), t )
    ) };

    assert( (k > 0) && (k <= t_vec_.size()) );
    assert( ((k == t_vec_.size()) && (t_vec_[k - 1] == t))
         || ((t_vec_[k - 1] <= t) && (t_vec_[k] > t)) );

    // If we are at a point, return the corresponding y-value,
    // otherwise, we must use interpolation

    if ( t_vec_[k - 1] == t ) {
        return y_vec_[k - 1];
    } else {
        return interpolate( t, k );
    }
}

/**********************************************************
 *
 **********************************************************/

template <typename T>
void ivp<T>::approximate_to_t( double t ) {
    std::size_t k{0};

    // We will put the data onto queues,
    // ensuring that each operation is O(1)
    std::queue<double>  q_t{};
    std::queue<T>       q_y{};
    std::queue<T>       q_s{};

    q_t.push( t_vec_.back() );
    q_y.push( y_vec_.back() );
    q_s.push( d_vec_.back() );

    while ( q_t.back() < t ) {
        T s[7]{ q_s.back() };

        double t1, a;
        T z1;
        bool using_h_min;

        do {
            // If 'h_' is smaller than 'h_min_', then use 'h_min_'
            // and terminate this loop
            using_h_min = (h_ <= h_min_);

            if ( using_h_min ) {
                std::clog << " -> using minimum h = " << h_min_ << std::endl;
                h_ = h_min_;
            } else if ( h_ > h_max_ ) {
                std::clog << " -> using maximum h = " << h_max_ << std::endl;
                h_ = h_max_;
            }

            t1 = q_t.back() + h_;

            // The last calculated slope will be the slope used for z1
            T slope;

            for ( std::size_t i{0}; i < 6; ++i ) {
                slope = 0.0;

                for ( std::size_t j{0}; j <= i; ++j ) {
                    slope += TABLEAU[i][j]*s[j];
                }

                s[i + 1] = f_( q_t.back() + h_*STEP[i],
                               q_y.back() + h_*STEP[i]*slope );
            }

            T slope_y{0.0};

            for ( std::size_t i{0}; i < 7; ++i ) {
                slope_y += Y_COEFF[i]*s[i];
            }

            T y1{q_y.back() + h_*slope_y};
            z1 = q_y.back() + h_*slope;
            a = (0.9*use_constant_reference_) ?
                std::pow( eps_abs_*h_/(2.0*norm_.constant_reference_( z1 - y1 )), 0.25 ) :
                std::pow( eps_abs_*h_/(2.0*norm_.value_( z1 - y1 )), 0.25 );

            // Ensure that h_ is changed by a factor greater than two
            if ( a >= 2.0 ) {
                h_ = 2.0*h_;
            } else if ( a <= 0.5 ) {
                h_ = 0.5*h_;
            } else {
                h_ = a*h_;
            }

            if ( (a < 0.9) && !using_h_min ) {
                std::clog << " -> recalculating with a smaller h..." << std::endl;
            }
	} while ( (a < 1) && !using_h_min );

        std::clog << " -> y(" << t1 << ") = " << z1 << std::endl;

        q_t.push( t1 );
        q_y.push( z1 );
        q_s.push( f_( t1, z1 ) );
    }

    assert( (q_t.size() == q_y.size()) && (q_t.size() == q_s.size()) );

    // Create three vectors of the appropriate capacity and copy over
    // the entries from the queues to the corresponding vectors
    std::size_t m{ t_vec_.size() };
    std::size_t n{ q_t.size() - 1 };

    t_vec_.resize( m + n );
    y_vec_.resize( m + n );
    d_vec_.resize( m + n );

    q_t.pop();
    q_y.pop();
    q_s.pop();
    
    for ( std::size_t k{m}; k < m + n; ++k ) {
        t_vec_[k] = q_t.front();
        y_vec_[k] = q_y.front();
        d_vec_[k] = q_s.front();
        q_t.pop();
        q_y.pop();
        q_s.pop();
    }
}

/**********************************************************
 * T interpolate( t, k )
 *
 * Find the interpolating cubic that matches both the
 * values of the surrounding points
 *        (t   , y   )     (t , y )
 *          k-1   k-1        k   k
 * as well as the slopes at these two points:
 *        
 *                           s[k]
 *                          ------o y[k]
 *                      *
 *
 *            /
 *  s[k - 1] /
 *          /
 *         *  y[k - 1]
 *          
 *         |            ^         |
 *         t[k - 1]     t         t[k]
 **********************************************************/

template <typename T>
T ivp<T>::interpolate( double t, std::size_t k ) {
    double delta_t{t_vec_[k] - t_vec_[k - 1]};
    double offset{(t - t_vec_[k - 1])/delta_t};
    T delta_y{y_vec_[k] - y_vec_[k - 1]};

    if ( delta_t == h_min_ ) {
        // We are very likely near a singularity
        //  - do not use cubic interpolation
        //  - instead, use linear interpolation
        return delta_y*offset + y_vec_[k - 1];     
    } else {
        // Use cubic interpolation matching both the values
        // and the derivatives at the two nearest points
        T sum_dy{(d_vec_[k - 1] + d_vec_[k])*delta_t};

        return ((
            (
                -2*delta_y + sum_dy
            )*offset - delta_t*d_vec_[k - 1] - sum_dy + 3*delta_y
        )*offset + d_vec_[k - 1]*delta_t)*offset + y_vec_[k - 1];
    }
}
