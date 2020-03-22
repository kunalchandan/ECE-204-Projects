#pragma once

#include <vector>
#include <utility>

// Class declarations
template <typename T>
class ivp;

// Class definitions
template <typename T>
class ivp {
    public:
        ivp( T f( double t, T y ),
             double t0, T y0,
             double h,
             std::pair<double, double> h_range,
             double eps_abs,
             double norm( T y ) = std::abs );

        ivp( T f( double t, T y ),
             double t0, T y0,
             double h,
             std::pair<double, double> h_range,
             double eps_abs,
             double norm( T const &y ) );

        T operator()( double t );

    private:
        T (*f_)( double t, T y );
        std::vector<double> t_vec_;
        std::vector<T>      y_vec_;
        std::vector<T>      d_vec_;
        double h_;
        double const h_min_;
        double const h_max_;
        double const eps_abs_;

        // 'norm' is either function pointer where the argument
        // is either passed by value or passed by constant reference
        union {
            double (*value_)( T y_ );
            double (*constant_reference_)( T const &y_ );
        } norm_;

        bool use_constant_reference_;

        double static const STEP[6];
        double static const TABLEAU[6][6];
        double static const Y_COEFF[7];

        T interpolate( double t, std::size_t k );
        void approximate_to_t( double t );
};

template <typename T>
double const ivp<T>::STEP[6]{1.0/5.0, 3.0/10.0, 4.0/5.0, 8.0/9.0, 1.0, 1.0};

template <typename T>
double const ivp<T>::TABLEAU[6][6]{
    {   1.0},
    {   1.0/4.0,        3.0/4},
    {  11.0/9.0,      -14.0/3.0,     40.0/9.0},
    {4843.0/1458.0, -3170.0/243.0, 8056.0/729.0,  -53.0/162.0},
    {9017.0/3168.0,  -355.0/33.0, 46732.0/5247.0,  49.0/176.0, -5103.0/18656.0},
    {  35.0/384.0,      0.0,        500.0/1113.0, 125.0/192.0, -2187.0/6784.0, 11.0/84.0}
};

template <typename T>
double const ivp<T>::Y_COEFF[7]{
      5179.0/57600.0,
         0.0,
      7571.0/16695.0,
       393.0/640.0,
    -92097.0/339200.0,
       187.0/2100.0,
         1.0/40.0
};

#include "ivp.tpp"
