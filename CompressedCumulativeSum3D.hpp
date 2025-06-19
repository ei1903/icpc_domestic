template <class T, class C = long long>
class CompressedCumulativeSum3D {
private:
    vector<C> zs, ys, xs;
    vector<vector<vector<T> > > cumsum;
    vector<tuple<C, C, C, T> > queries;

public:
    CompressedCumulativeSum3D() = default;

    void build() {
        sort(zs.begin(), zs.end());
        zs.erase(unique(zs.begin(), zs.end()), zs.end());
        sort(ys.begin(), ys.end());
        ys.erase(unique(ys.begin(), ys.end()), ys.end());
        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());
        cumsum.assign(zs.size() + 1, vector<vector<T> >(ys.size() + 1, vector<T>(xs.size() + 1, T())));
        for (auto [z, y, x, v] : queries) {
            cumsum[lower_bound(zs.begin(), zs.end(), z) - zs.begin() + 1][lower_bound(ys.begin(), ys.end(), y) - ys.begin() + 1][lower_bound(xs.begin(), xs.end(), x) - xs.begin() + 1] += v;
        }
        accumulate();
    }

    void accumulate() {
        for (int i = 1; i < cumsum.size(); ++i) {
            for (int j = 1; j < cumsum[i].size(); ++j) {
                for (int k = 1; k < cumsum[i][j].size(); ++k) {
                    cumsum[i][j][k] += cumsum[i][j][k - 1];
                }
            }
        }
        for (int i = 1; i < cumsum.size(); ++i) {
            for (int j = 1; j < cumsum[i].size(); ++j) {
                for (int k = 1; k < cumsum[i][j].size(); ++k) {
                    cumsum[i][j][k] += cumsum[i][j - 1][k];
                }
            }
        }
        for (int i = 1; i < cumsum.size(); ++i) {
            for (int j = 1; j < cumsum[i].size(); ++j) {
                for (int k = 1; k < cumsum[i][j].size(); ++k) {
                    cumsum[i][j][k] += cumsum[i - 1][j][k];
                }
            }
        }
    }

    void add(C z, C y, C x, T v) {
        queries.emplace_back(z, y, x, v);
        zs.emplace_back(z);
        ys.emplace_back(y);
        xs.emplace_back(x);
    }

    // ([sz, gz), [sy, gy), [sx, gx))
    void add(C sz, C sy, C sx, C gz, C gy, C gx, T v) {
        add(sz, sy, sx, v);
        add(gz, sy, sx, -v);
        add(sz, gy, sx, -v);
        add(sz, sy, gx, -v);
        add(gz, gy, sx, v);
        add(gz, sy, gx, v);
        add(sz, gy, gx, v);
        add(gz, gy, gx, -v);
    }

    // ([-inf, z), [-inf, y), [-inf, x))
    T sum(C z, C y, C x) {
        return cumsum[upper_bound(zs.begin(), zs.end(), z - 1) - zs.begin()][upper_bound(ys.begin(), ys.end(), y - 1) - ys.begin()][upper_bound(xs.begin(), xs.end(), x - 1) - xs.begin()];
    }

    // ([sz, gz), [sy, gy), [sx, gx))
    T sum(C sz, C sy, C sx, C gz, C gy, C gx) {
        return sum(gz, gy, gx) - sum(sz, gy, gx) - sum(gz, sy, gx) - sum(gz, gy, sx) + sum(sz, sy, gx) + sum(sz, gy, sx) + sum(gz, sy, sx) - sum(sz, sy, sx);
    }

    vector<tuple<C, C, C, C, C, C, T> > rle() {
        vector<tuple<C, C, C, C, C, C, T> > ret;
        if (zs.empty() || ys.empty() || xs.empty()) {
            ret.emplace_back(
                numeric_limits<C>::lowest(),
                numeric_limits<C>::lowest(),
                numeric_limits<C>::lowest(),
                numeric_limits<C>::max(),
                numeric_limits<C>::max(),
                numeric_limits<C>::max(),
                T()
            );
            return ret;
        }
        for (int i = 0; i < cumsum.size(); ++i) {
            for (int j = 0; j < cumsum[i].size(); ++j) {
                for (int k = 0; k < cumsum[i][j].size(); ++k) {
                    ret.emplace_back(
                        i == 0 ? numeric_limits<C>::lowest() : zs[i - 1],
                        j == 0 ? numeric_limits<C>::lowest() : ys[j - 1],
                        k == 0 ? numeric_limits<C>::lowest() : xs[k - 1],
                        i + 1 == cumsum.size() ? numeric_limits<C>::max() : zs[i],
                        j + 1 == cumsum[i].size() ? numeric_limits<C>::max() : ys[j],
                        k + 1 == cumsum[i][j].size() ? numeric_limits<C>::max() : xs[k],
                        cumsum[i][j][k]
                    );
                }
            }
        }
        return ret;
    }
};