template <class T, class C = long long>
class CompressedCumulativeSum2D {
private:
    vector<C> ys, xs;
    vector<vector<T> > cumsum;
    vector<tuple<C, C, T> > queries;

public:
    CompressedCumulativeSum2D() = default;

    void build() {
        sort(ys.begin(), ys.end());
        ys.erase(unique(ys.begin(), ys.end()), ys.end());
        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());
        cumsum.assign(ys.size() + 1, vector<T>(xs.size() + 1, T()));
        for (auto [y, x, v] : queries) {
            cumsum[lower_bound(ys.begin(), ys.end(), y) - ys.begin() + 1][lower_bound(xs.begin(), xs.end(), x) - xs.begin() + 1] += v;
        }
        accumulate();
    }

    void accumulate() {
        for (int i = 1; i < cumsum.size(); ++i) {
            for (int j = 1; j < cumsum[i].size(); ++j) {
                cumsum[i][j] += cumsum[i][j - 1];
            }
        }
        for (int i = 1; i < cumsum.size(); ++i) {
            for (int j = 1; j < cumsum[i].size(); ++j) {
                cumsum[i][j] += cumsum[i - 1][j];
            }
        }
    }

    void add(C y, C x, T v) {
        queries.emplace_back(y, x, v);
        ys.emplace_back(y);
        xs.emplace_back(x);
    }

    // ([sy, gy), [sx, gx))
    void add(C sy, C sx, C gy, C gx, T v) {
        add(sy, sx, v);
        add(gy, sx, -v);
        add(sy, gx, -v);
        add(gy, gx, v);
    }

    // ([-inf, y), [-inf, x))
    T sum(C y, C x) {
        return cumsum[upper_bound(ys.begin(), ys.end(), y - 1) - ys.begin()][upper_bound(xs.begin(), xs.end(), x - 1) - xs.begin()];
    }

    // ([sy, gy), [sx, gx))
    T sum(C sy, C sx, C gy, C gx) {
        return sum(gy, gx) - sum(gy, sx) - sum(sy, gx) + sum(sy, sx);
    }

    vector<tuple<C, C, C, C, T> > rle() {
        vector<tuple<C, C, C, C, T> > ret;
        if (ys.empty() || xs.empty()) {
            ret.emplace_back(numeric_limits<C>::lowest(), numeric_limits<C>::lowest(), numeric_limits<C>::max(), numeric_limits<C>::max(), T());
            return ret;
        }
        for (int i = 0; i < cumsum.size(); ++i) {
            for (int j = 0; j < cumsum[i].size(); ++j) {
                ret.emplace_back(
                    i == 0 ? numeric_limits<C>::lowest() : ys[i - 1],
                    j == 0 ? numeric_limits<C>::lowest() : xs[j - 1],
                    i + 1 == cumsum.size() ? numeric_limits<C>::max() : ys[i],
                    j + 1 == cumsum[i].size() ? numeric_limits<C>::max() : xs[j],
                    cumsum[i][j]
                );
            }
        }
        return ret;
    }
};