template <class T>
class CumulativeSum3D {
private:
    vector<vector<vector<T> > > cumsum;

public:
    CumulativeSum3D() = default;
    CumulativeSum3D(const size_t h, const size_t w, const size_t d) : cumsum(h + 2, vector<vector<T> >(w + 2, vector<T>(d + 2))) {}

    void build() {
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

    void add(size_t z, size_t y, size_t x, T v) {
        cumsum[z + 1][y + 1][x + 1] += v;
    }

    // ([sz, gz), [sy, gy), [sx, gx))
    void add(size_t sz, size_t sy, size_t sx, size_t gz, size_t gy, size_t gx, T v) {
        add(sz, sy, sx, v);
        add(gz, sy, sx, -v);
        add(sz, gy, sx, -v);
        add(sz, sy, gx, -v);
        add(gz, gy, sx, v);
        add(gz, sy, gx, v);
        add(sz, gy, gx, v);
        add(gz, gy, gx, -v);
    }

    // ([0, z), [0, y), [0, x))
    T sum(size_t z, size_t y, size_t x) {
        return cumsum[z][y][x];
    }

    // ([sz, gz), [sy, gy), [sx, gx))
    T sum(size_t sz, size_t sy, size_t sx, size_t gz, size_t gy, size_t gx) {
        sz++, sy++, sx++, gz++, gy++, gx++;
        return sum(gz, gy, gx) - sum(sz, gy, gx) - sum(gz, sy, gx) - sum(gz, gy, sx) + sum(sz, sy, gx) + sum(sz, gy, sx) + sum(gz, sy, sx) - sum(sz, sy, sx);
    }
};