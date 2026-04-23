#include <iostream>
#include <stdexcept>

struct divided_by_zero final : std::exception {
public:
    divided_by_zero()   = default;
    ~divided_by_zero()  = default;
    const char *what() const noexcept override { return "Divided by zero!"; };
};

template <typename _Tp>
inline _Tp gcd(_Tp x, _Tp y) {
    while (y) {
        x %= y;
        std::swap(x, y);
    }
    return x;
}

template <typename _Tp>
inline _Tp abs_val(_Tp x) {
    return x < _Tp(0) ? -x : x;
}

template <typename _Tp>
struct fraction {
private:
    _Tp numerator;
    _Tp denominator;
    
    void normalize() {
        if (denominator == _Tp(0)) {
            throw divided_by_zero();
        }
        
        // Handle sign: ensure denominator is always positive
        if (denominator < _Tp(0)) {
            numerator = -numerator;
            denominator = -denominator;
        }
        
        // Reduce to simplest form
        if (numerator == _Tp(0)) {
            denominator = _Tp(1);
        } else {
            _Tp g = gcd(abs_val(numerator), abs_val(denominator));
            numerator /= g;
            denominator /= g;
        }
    }

public:
    fraction() : numerator(_Tp(0)), denominator(_Tp(1)) {}
    
    fraction(_Tp x) : numerator(x), denominator(_Tp(1)) {}
    
    fraction(_Tp x, _Tp y) : numerator(x), denominator(y) {
        normalize();
    }
    
    fraction operator + (const fraction &other) const {
        _Tp new_num = numerator * other.denominator + other.numerator * denominator;
        _Tp new_den = denominator * other.denominator;
        return fraction(new_num, new_den);
    }
    
    fraction operator - (const fraction &other) const {
        _Tp new_num = numerator * other.denominator - other.numerator * denominator;
        _Tp new_den = denominator * other.denominator;
        return fraction(new_num, new_den);
    }
    
    fraction operator * (const fraction &other) const {
        _Tp new_num = numerator * other.numerator;
        _Tp new_den = denominator * other.denominator;
        return fraction(new_num, new_den);
    }
    
    fraction operator / (const fraction &other) const {
        if (other.numerator == _Tp(0)) {
            throw divided_by_zero();
        }
        _Tp new_num = numerator * other.denominator;
        _Tp new_den = denominator * other.numerator;
        return fraction(new_num, new_den);
    }
    
    fraction operator ^ (long long exp) const {
        if (exp == 0) {
            return fraction(_Tp(1));
        }
        
        if (exp < 0) {
            if (numerator == _Tp(0)) {
                throw divided_by_zero();
            }
            // For negative exponent, flip numerator and denominator
            fraction inverted(denominator, numerator);
            return inverted ^ (-exp);
        }
        
        // Fast power algorithm for positive exponent
        fraction result(_Tp(1));
        fraction base = *this;
        
        while (exp > 0) {
            if (exp & 1) {
                result *= base;
            }
            base *= base;
            exp >>= 1;
        }
        
        return result;
    }
    
    fraction &operator += (const fraction &other) {
        *this = *this + other;
        return *this;
    }
    
    fraction &operator -= (const fraction &other) {
        *this = *this - other;
        return *this;
    }
    
    fraction &operator *= (const fraction &other) {
        *this = *this * other;
        return *this;
    }
    
    fraction &operator /= (const fraction &other) {
        *this = *this / other;
        return *this;
    }
    
    fraction &operator ^= (long long exp) {
        *this = *this ^ exp;
        return *this;
    }
    
    explicit operator double() const {
        return static_cast<double>(numerator) / static_cast<double>(denominator);
    }
    
    explicit operator bool() const {
        return numerator != _Tp(0);
    }
    
    template <typename T>
    friend bool operator == (const fraction<T> &a, const fraction<T> &b) {
        return a.numerator == b.numerator && a.denominator == b.denominator;
    }
    
    template <typename T>
    friend bool operator < (const fraction<T> &a, const fraction<T> &b) {
        return a.numerator * b.denominator < b.numerator * a.denominator;
    }
    
    template <typename T>
    friend std::ostream & operator << (std::ostream &os, const fraction<T> &f) {
        os << f.numerator << "/" << f.denominator;
        return os;
    }
};
