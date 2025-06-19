struct ModHash {
    static const uint32_t M0 = 1000000007;
    static const uint32_t M1 = 1000000009;
    static const uint32_t M2 = 998244353;
    static const uint32_t M3 = 998244853;
    static const uint32_t M4 = 924844033;

    using T0 = modint<M0>;
    using T1 = modint<M1>;
    using T2 = modint<M2>;
    using T3 = modint<M3>;
    using T4 = modint<M4>;

    using T = tuple<T0, T1, T2, T3, T4>;

    T v;

    ModHash() {}
    ModHash(const int64_t x) : v(x, x, x, x, x) {}

    ModHash &operator+=(const ModHash &x) {
        get<0>(v) += get<0>(x.v);
        get<1>(v) += get<1>(x.v);
        get<2>(v) += get<2>(x.v);
        get<3>(v) += get<3>(x.v);
        get<4>(v) += get<4>(x.v);
        return *this;
    }

    ModHash &operator-=(const ModHash &x) {
        get<0>(v) -= get<0>(x.v);
        get<1>(v) -= get<1>(x.v);
        get<2>(v) -= get<2>(x.v);
        get<3>(v) -= get<3>(x.v);
        get<4>(v) -= get<4>(x.v);
        return *this;
    }

    ModHash &operator*=(const ModHash &x) {
        get<0>(v) *= get<0>(x.v);
        get<1>(v) *= get<1>(x.v);
        get<2>(v) *= get<2>(x.v);
        get<3>(v) *= get<3>(x.v);
        get<4>(v) *= get<4>(x.v);
        return *this;
    }

    ModHash &operator/=(const ModHash &x) {
        get<0>(v) /= get<0>(x.v);
        get<1>(v) /= get<1>(x.v);
        get<2>(v) /= get<2>(x.v);
        get<3>(v) /= get<3>(x.v);
        get<4>(v) /= get<4>(x.v);
        return *this;
    }

    ModHash operator-() const { return ModHash() - *this; }

    ModHash operator+(const ModHash &x) const { return ModHash(*this) += x; }

    ModHash operator-(const ModHash &x) const { return ModHash(*this) -= x; }

    ModHash operator*(const ModHash &x) const { return ModHash(*this) *= x; }

    ModHash operator/(const ModHash &x) const { return ModHash(*this) /= x; }

    bool operator==(const ModHash &x) const {
        return get<0>(v) == get<0>(x.v) && get<1>(v) == get<1>(x.v) && get<2>(v) == get<2>(x.v) && get<3>(v) == get<3>(x.v) && get<4>(v) == get<4>(x.v);
    }
};