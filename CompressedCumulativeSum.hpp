template <class T, class C = long long>
class CompressedCumulativeSum {
private:
    vector<C> xs;
    vector<T> cumsum;
    vector<pair<C, T> > queries;

public:
    CompressedCumulativeSum() = default;

    void build() {
        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());
        cumsum.assign(xs.size() + 1, T());
        for (auto [k, v] : queries) {
            cumsum[lower_bound(xs.begin(), xs.end(), k) - xs.begin() + 1] += v;
        }
        accumulate();
    }

    void accumulate() {
        for (int i = 1; i < cumsum.size(); ++i) {
            cumsum[i] += cumsum[i - 1];
        }
    }

    void add(C k, T v) {
        queries.emplace_back(k, v);
        xs.emplace_back(k);
    }

    // [l, r)
    void add(C l, C r, T v) {
        add(l, v);
        add(r, -v);
    }

    // [-inf, r)
    T sum(C r) {
        return cumsum[upper_bound(xs.begin(), xs.end(), r - 1) - xs.begin()];
    }

    // [l, r)
    T sum(C l, C r) {
        return sum(r) - sum(l);
    }

    vector<tuple<C, C, T> > rle() {
        vector<tuple<C, C, T> > ret;
        if (xs.empty()) {
            ret.emplace_back(numeric_limits<C>::lowest(), numeric_limits<C>::max(), T());
            return ret;
        }
        for (int i = 0; i < cumsum.size(); ++i) {
            ret.emplace_back(
                i == 0 ? numeric_limits<C>::lowest() : xs[i - 1],
                i + 1 == cumsum.size() ? numeric_limits<C>::max() : xs[i],
                cumsum[i]
            );
        }
        return ret;
    }
};