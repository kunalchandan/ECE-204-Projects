#include <cassert>
#include <iostream>
#include <cmath>

template <std::size_t N>
vec<N>::vec() {
    for ( std::size_t k{0}; k < N; ++k ) {
        entries[k] = 0.0;
    }
}

template <std::size_t N>
vec<N>::vec( double s ) {
    for ( std::size_t k{0}; k < N; ++k ) {
        entries[k] = s;
    }
}

template <std::size_t N>
vec<N>::vec( vec<N> const &v ) {
    for ( std::size_t k{0}; k < N; ++k ) {
        entries[k] = v.entries[k];
    }
}

template <std::size_t N>
vec<N>::vec( std::initializer_list<double> init ) {
    std::size_t k{0};

    for ( std::initializer_list<double>::iterator itr{init.begin()}; itr != init.end(); ++itr ) {
        entries[k] = *itr;
        ++k;
    }

    assert( k <= N );

    for ( ; k < N; ++k ) {
        entries[k] = 0.0;
    }
}

template <std::size_t N>
vec<N> vec<N>::operator =( vec<N> const &v ) {
    for ( std::size_t k{0}; k < N; ++k ) {
        entries[k] = v.entries[k];
    }

    return *this;
}

template <std::size_t N>
vec<N> &vec<N>::operator *=( double s ) {
    for ( std::size_t k{0}; k < N; ++k ) {
        entries[k] *= s;
    }

    return *this;
}

template <std::size_t N>
vec<N> vec<N>::operator *( double s ) const {
    vec<N> ret;

    for ( std::size_t k{0}; k < N; ++k ) {
        ret.entries[k] = entries[k]*s;
    }

    return ret;
}

template <std::size_t N>
vec<N> &vec<N>::operator +=( vec const &v ) {
    for ( std::size_t k{0}; k < N; ++k ) {
        entries[k] += v.entries[k];
    }

    return *this;
}

template <std::size_t N>
vec<N> vec<N>::operator +( vec const &v ) const {
    vec<N> ret;

    for ( std::size_t k{0}; k < N; ++k ) {
        ret.entries[k] = entries[k] + v.entries[k];
    }

    return ret;
}

template <std::size_t N>
vec<N> &vec<N>::operator -=( vec const &v ) {
    for ( std::size_t k{0}; k < N; ++k ) {
        entries[k] -= v.entries[k];
    }

    return *this;
}

template <std::size_t N>
vec<N> vec<N>::operator -( vec const &v ) const {
    vec<N> ret;

    for ( std::size_t k{0}; k < N; ++k ) {
        ret.entries[k] = entries[k] - v.entries[k];
    }

    return ret;
}

template <std::size_t N>
vec<N> vec<N>::operator +() const {
    vec<N> ret;

    for ( std::size_t k{0}; k < N; ++k ) {
        ret.entries[k] = entries[k];
    }

    return ret;
}
template <std::size_t N>
vec<N> vec<N>::operator -() const {
    vec<N> ret;

    for ( std::size_t k{0}; k < N; ++k ) {
        ret.entries[k] = -entries[k];
    }

    return ret;
}

template <std::size_t N>
double vec<N>::operator * ( vec const &v ) const {
    double ret{0.0};

    for ( std::size_t k{0}; k < N; ++k ) {
        ret += entries[k] * v.entries[k];
    }

    return ret;
}

template <std::size_t N>
double &vec<N>::operator []( std::size_t k ) {
    return entries[k];
}

template <std::size_t N>
double vec<N>::operator []( std::size_t k ) const {
    return entries[k];
}

template <std::size_t N>
bool vec<N>::operator ==( vec const &v ) const {
    for ( std::size_t k{0}; k < N; ++k ) {
        if ( v.entries[k] != entries[k] ) {
            return false;
        }
    }

    return true;
}

template <std::size_t N>
bool vec<N>::operator !=( vec const &v ) const {
    for ( std::size_t k{0}; k < N; ++k ) {
        if ( v.entries[k] != entries[k] ) {
            return true;
        }
    }

    return false;
}

template <std::size_t N>
double vec<N>::norm() const {
    double ret{ 0.0 };

    for ( std::size_t k{0}; k < N; ++k ) {
        ret += entries[k]*entries[k];
    }

    return std::sqrt( ret );
}

template <std::size_t M>
vec<M> operator *( double s, vec<M> const &v ) {
    return v * s;
}

template <std::size_t M>
std::ostream &operator<<( std::ostream &out, vec<M> const &v ) {
    out << "[";

    if ( M != 0 ) {
        out << v[0];

        for ( std::size_t k{1}; k < M; ++k ) {
            out << ", " << v[k];
        }
    }
   
    out << "]";

    return out;
}

template <std::size_t N>
double vec<N>::norm( vec<N> const &v ) {
    return v.norm();
}
