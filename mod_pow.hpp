template <typename T>
T mod_pow(T x, unsigned long long n, unsigned int p) {
    T ret = 1;
    while (n > 0) {
        if (n & 1) (ret *= x) %= p;
        (x *= x) %= p;
        n >>= 1;
    }
    return (ret % p);
}
