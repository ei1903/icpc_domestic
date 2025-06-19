template<class T>
struct MultidimensionalArray {
private:
    const int d;
    std::vector<T> a;
    std::vector<int> mul;
    const std::vector<int> sz;

    int convert(const std::vector<int> &v) {
        int ret = 0;
        for (int i = d - 1; i >= 0; --i) {
            ret += mul[i] * v[i];
        }
        return (ret);
    }

public:
    MultidimensionalArray() {}
    MultidimensionalArray(const std::vector<int> &sz) : d(sz.size()), sz(sz) {
        a.resize(std::accumulate(sz.begin(), sz.end(), 1, [](const auto a, const auto b) { return (a * b); }));
        for (int i = d - 1; i >= 0; --i) {
            if (i == d - 1) {
                mul.emplace_back(1);
            } else {
                mul.emplace_back(mul.back() * sz[i + 1]);
            }
        }
        std::reverse(mul.begin(), mul.end());
    }

    inline T &operator[](const std::vector<int> &v) {
        return a[convert(v)];
    }

    inline T operator[](const std::vector<int> &v) const {
        return a[convert(v)];
    }

    int dimension() const { return (d); }
    const std::vector<int>& size() { return (sz); }
    int size(const int &k) const { return (sz[k]); }
};