#pragma once

#include <iostream>

// This is a linear algebra vector class, not the std::vector class
//  - the vectors are fixed in their dimension

// Class declaration
template <std::size_t N>
class vec;

// Class definition
template <std::size_t N>
class vec {
    public:
        vec();
        vec( double s );
        vec( vec const &v );
        vec( std::initializer_list<double> init );
        // No move constructors necessary
        //  - no dynamically allocated memory
        // No destructor required
        //  - all memory allocated at compile time

        vec operator =( vec const &v );
        // No move operator necessary

        vec operator +() const;
        vec operator -() const;

        vec &operator *=( double s );
        vec  operator * ( double s ) const;
        vec &operator +=( vec const &v );
        vec  operator + ( vec const &v ) const;
        vec &operator -=( vec const &v );
        vec  operator - ( vec const &v ) const;

        // We will use vector-vector multiplication for the inner product
        double operator * ( vec const &v ) const;

        double &operator []( std::size_t k );
        double operator []( std::size_t k ) const;

        bool operator ==( vec const &v ) const;
        bool operator !=( vec const &v ) const;

        double norm() const;

        static double norm( vec<N> const & v );

    template <std::size_t M>
    friend vec<M> operator *( double s, vec<M> const &v );

    template <std::size_t M>
    friend std::ostream &operator<<( std::ostream &out, vec<M> const &v );

    private:
        double entries[N];
};

#include "vec.tpp"
