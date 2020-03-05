#include <math.h>
#include <iostream>

template<uint64_t Y> struct utype
{
    typedef typename utype<(Y & (Y - 1)) == 0 ? Y / 2 : (Y & (Y - 1))>::type type;
};

template<> struct utype<0>
{
    typedef std::uint_fast8_t t;
};

template<> struct utype<0x100>
{
    typedef std::uint_fast16_t t;
};

template<> struct utype<0x10000>
{
    typedef std::uint_fast32_t t;
};

template<> struct utype<0x100000000>
{
    typedef std::uint_fast64_t t;
};


template<uint64_t Y> struct stype
{
    typedef typename stype<(Y & (Y - 1)) == 0 ? Y / 2 : (Y & (Y - 1))>::type type;
};

template<> struct stype<0>
{
    typedef std::uint_fast8_t t;
};

template<> struct stype<0x100>
{
    typedef std::uint_fast16_t t;
};

template<> struct stype<0x10000>
{
    typedef std::uint_fast32_t t;
};

template<> struct stype<0x100000000>
{
    typedef std::uint_fast64_t t;
};


template <std::size_t SIG, std::size_t EXP>
class BigFloat
{
    private:
        // Significand
        std::size_t size_sig = SIG;
        typename stype<SIG>::t s;
        // EXPtissa
        std::size_t size_EXP = EXP;
        typename utype<EXP>::t e;
        
    public:
        BigFloat(typename stype<SIG>::t s, typename utype<EXP>::t m);
        // TODO:: operator overloading
        
        BigFloat<SIG,EXP> operator =(BigFloat const &bf);
        
        BigFloat<SIG,EXP> operator +() const;
        BigFloat<SIG,EXP> operator -() const;
        BigFloat<SIG,EXP> operator +(BigFloat const &bf) const;
        BigFloat<SIG,EXP> operator -(BigFloat const &bf) const;
        BigFloat<SIG,EXP> operator *(BigFloat const &bf) const;
        BigFloat<SIG,EXP> operator /(BigFloat const &bf) const;
        
        BigFloat<SIG,EXP> &operator +=(BigFloat const &bf);
        BigFloat<SIG,EXP> &operator -=(BigFloat const &bf);
        BigFloat<SIG,EXP> &operator *=(BigFloat const &bf);
        BigFloat<SIG,EXP> &operator /=(BigFloat const &bf);
};

template <std::size_t SIG, std::size_t EXP>
BigFloat<SIG, EXP>::BigFloat(typename stype<SIG>::t s, typename utype<EXP>::t e) {
    this->s = s;
    this->e = e;
}

template <std::size_t SIG, std::size_t EXP>
BigFloat<SIG, EXP>
BigFloat<SIG, EXP>::operator =(BigFloat const &bf) {
    this->s = bf.s;
    this->e = bf.e;
    this->size_sig = bf.size_sig;
    this->size_exp = bf.size_exp;
    return *this;
}

template <std::size_t SIG, std::size_t EXP>
BigFloat<SIG, EXP> 
BigFloat<SIG, EXP>::operator +() const {
    BigFloat<SIG, EXP> ret = BigFloat<SIG, EXP>(this->s, this->e);
    return ret;
}

template <std::size_t SIG, std::size_t EXP>
BigFloat<SIG, EXP> 
BigFloat<SIG, EXP>::operator -() const {
    BigFloat<SIG, EXP> ret = BigFloat<SIG, EXP>(-this->s, this->e);
    return ret;
}

template <std::size_t SIG, std::size_t EXP>
BigFloat<SIG, EXP> 
BigFloat<SIG, EXP>::operator +(BigFloat const &bf) const {
    // Take the smaller of the two and bit shift down
    BigFloat<SIG, EXP> ret;
    
    if (this->e == bf.e) {
        
    }
    else if (min(this->e, bf.e) == this->e) {
        this->s >> (bf.e - this->e);
        
    }
    else {

    }
}
