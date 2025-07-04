class Fraction {
public:
    intmax_t numer, denom;

    Fraction() {
        numer = 0;
        denom = 1;
    }
    Fraction(intmax_t n, intmax_t d) {
        if (n == 0) {
            numer = 0;
            denom = 1;
        } else {
            int sign = ((n < 0) == (d < 0) ? 1 : -1);
            n = abs(n), d = abs(d);

            intmax_t g = gcd(n, d);
            numer = sign * n / g;
            denom = d / g;
        }
    }

    template <typename T>
    constexpr explicit operator T() const { return static_cast<T>(numer) / denom; }
};

Fraction operator+(const Fraction &lhs, const Fraction &rhs) {
    Fraction ret
        (lhs.numer * rhs.denom + rhs.numer * lhs.denom,
            lhs.denom * rhs.denom
        );
    return ret;
}
Fraction operator+=(Fraction &lhs, const Fraction &rhs) {
    Fraction ret
        (lhs.numer * rhs.denom + rhs.numer * lhs.denom,
            lhs.denom * rhs.denom
        );
    lhs = ret;
    return lhs;
}
Fraction operator-(const Fraction &lhs, const Fraction &rhs) {
    Fraction ret
        (lhs.numer * rhs.denom - rhs.numer * lhs.denom,
            lhs.denom * rhs.denom
        );
    return ret;
}
Fraction operator-=(Fraction &lhs, const Fraction &rhs) {
    Fraction ret
        (lhs.numer * rhs.denom - rhs.numer * lhs.denom,
            lhs.denom * rhs.denom
        );
    lhs = ret;
    return lhs;
}
Fraction operator*(const Fraction &lhs, const Fraction &rhs) {
    Fraction ret
        (lhs.numer * rhs.numer,
            lhs.denom * rhs.denom
        );
    return ret;
}
Fraction operator*=(Fraction &lhs, const Fraction &rhs) {
    Fraction ret
        (lhs.numer * rhs.numer,
            lhs.denom * rhs.denom
        );
    lhs = ret;
    return lhs;
}
Fraction operator/(const Fraction &lhs, const Fraction &rhs) {
    Fraction ret
        (lhs.numer * rhs.denom,
            lhs.denom * rhs.numer
        );
    return ret;
}
Fraction operator/=(Fraction &lhs, const Fraction &rhs) {
    Fraction ret
        (lhs.numer * rhs.denom,
            lhs.denom * rhs.numer
        );
    lhs = ret;
    return lhs;
}

bool operator<(const Fraction &lhs, const Fraction &rhs) {
    const intmax_t lhs_numer = lhs.numer * rhs.denom;
    const intmax_t rhs_numer = rhs.numer * lhs.denom;
    return lhs_numer < rhs_numer;
}
bool operator>(const Fraction &lhs, const Fraction &rhs) { return rhs < lhs; }
bool operator<=(const Fraction &lhs, const Fraction &rhs) { return !(lhs > rhs); }
bool operator>=(const Fraction &lhs, const Fraction &rhs) { return !(lhs < rhs); }
bool operator==(const Fraction &lhs, const Fraction &rhs) { return !(lhs < rhs) && !(lhs > rhs); }
bool operator!=(const Fraction &lhs, const Fraction &rhs) { return (lhs < rhs) || (lhs > rhs); }

istream& operator>>(istream &is, Fraction &f) {
    is >> f.numer >> f.denom;
    return is;
}
ostream& operator<<(ostream &os, const Fraction &f) {
    if (f.denom == 1) {
        os << f.numer;
    } else {
        os << f.numer << '/' << f.denom;
    }
    return os;
}
