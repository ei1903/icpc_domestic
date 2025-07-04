class SmartSieve {
    intmax_t L, R, M;
    vector<intmax_t> small; // 小さい篩 [2, sqrt(R))
    vector<vector<intmax_t>> large; // 大きい篩 [L, R)
    vector<intmax_t> aux; // aux[i] := large[i] の素因数の積

public:
    SmartSieve(intmax_t L, intmax_t R) : L(L), R(R), M(sqrt(R) + 1) {
        small.resize(M);
        iota(small.begin(), small.end(), 0);
        large.resize(R - L);
        aux.assign(R - L, 1);

        for (intmax_t i = 2; i * i < R; ++i) {
            if (small[i] < i) continue;

            for (intmax_t j = i * i; j < M; j += i) {
                if (small[j] == j) small[j] = i;
            }

            for (intmax_t j = (L + i - 1) / i * i; j < R; j += i) {
                intmax_t k = j;
                do {
                    if (aux[j - L] * aux[j - L] > R) break;

                    large[j - L].emplace_back(i);
                    aux[j - L] *= i;
                    k /= i;
                } while (k % i == 0);
            }
        }
    }

    bool isPrime(intmax_t n) const {
        assert(L <= n && n < R);
        if (n < M) return (2 <= n && small[n] == n);
        return (aux[n - L] == 1);
    }

    map<intmax_t, intmax_t> primeFactor(intmax_t n) {
        assert(L <= n && n < R);
        map<intmax_t, intmax_t> ret;
        for (const auto& e: large[n - L]) ret[e]++;
        n /= aux[n - L];
        if (n >= M) {
            ret[n]++;
            return ret;
        }
        while (n > 1) {
            ret[small[n]]++;
            n /= small[n];
        }
        return ret;
    }
};