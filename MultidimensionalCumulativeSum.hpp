template<class T>
struct MultidimensionalCumulativeSum {
private:
    const int d;
    std::vector<T> cum, mul;
    const std::vector<int> sz;

    int convert(const std::vector<int> &v) {
        int ret = 0;
        for (int i = d - 1; i >= 0; --i) {
            ret += mul[i] * (v[i] + 1);
        }
        return (ret);
    }

    std::vector<int> convert(int k) {
        std::vector<int> ret;
        for (int i = d - 1; i >= 0; --i) {
            ret.emplace_back(k % (sz[i] + 1) - 1);
            k /= (sz[i] + 1);
        }
        std::reverse(ret.begin(), ret.end());
        return (ret);
    }

    void build(int dep, int k) {
        if (dep == d) {
            for (int bit = 1; bit < 1 << d; ++bit) {
                int v = k;
                for (int i = 0; i < d; ++i) {
                    if (bit >> i & 1) {
                        v -= mul[i];
                    }
                }
                if (__builtin_popcount(bit) & 1) {
                    cum[k] += cum[v];
                } else {
                    cum[k] -= cum[v];
                }
            }
        } else {
            for (int i = 1; i <= sz[dep]; ++i) {
                build(dep + 1, k + mul[dep] * i);
            }
        }
    }

public:
    MultidimensionalCumulativeSum() {}
    MultidimensionalCumulativeSum(const std::vector<int> &sz) : d(sz.size()), sz(sz) {
        cum.resize(std::accumulate(sz.begin(), sz.end(), 1, [](const auto a, const auto b) { return (a * (b + 1)); }));
        for (int i = d - 1; i >= 0; --i) {
            if (i == d - 1) {
                mul.emplace_back(1);
            } else {
                mul.emplace_back(mul.back() * (sz[i] + 1));
            }
        }
        std::reverse(mul.begin(), mul.end());
    }

    void build() {
        build(0, 0);
    }

    void add(const std::vector<int> &v, const T &val) {
        cum[convert(v)] += val;
    }

    T get(const std::vector<int> &v) {
        return (cum[convert(v)]);
    }

    T get(const std::vector<int> &l, const std::vector<int> &h) {
        const int k = convert(h);
        T ret = T();
        for (int bit = 0; bit < 1 << d; ++bit) {
            int v = k;
            for (int i = 0; i < d; ++i) {
                if (bit >> i & 1) {
                    v -= mul[i] * (h[i] - l[i] + 1);
                }
            }
            if (__builtin_popcount(bit) & 1) {
                ret -= cum[v];
            } else {
                ret += cum[v];
            }
        }
        return (ret);
    }

    int dimension() const { return (d); }
    const std::vector<int>& size() { return (sz); }
    int size(const int &k) const { return (sz[k]); }
};
