template <class T>
class CumulativeSum2D {
    vector<vector<T>> cumsum;

public:
    CumulativeSum2D() {}
    CumulativeSum2D(const size_t h, const size_t w) : cumsum(h + 2, vector<T>(w + 2)) {}

    void build() {
        const size_t h = cumsum.size(), w = cumsum[0].size();
        for (size_t y = 1; y < h; ++y) {
            for (size_t x = 1; x < w; ++x) {
                cumsum[y][x] += cumsum[y][x - 1] + cumsum[y - 1][x] - cumsum[y - 1][x - 1];
            }
        }
    }

    T sum(size_t sy, size_t sx, size_t gy, size_t gx) const {
        sy++, sx++, gy++, gx++;
        return cumsum[gy][gx] - cumsum[sy - 1][gx] - cumsum[gy][sx - 1] + cumsum[sy - 1][sx - 1];
    }

    void add(size_t y, size_t x, T v) {
        cumsum[y + 1][x + 1] += v;
    }

    void add(size_t sy, size_t sx, size_t gy, size_t gx, T v) {
        add(sy, sx, v);
        add(gy + 1, sx, -v);
        add(sy, gx + 1, -v);
        add(gy + 1, gx + 1, v);
    }

    T sum(size_t y, size_t x) const {
        return cumsum[y + 1][x + 1];
    }

    void assign(const size_t h, const size_t w) {
        cumsum.assign(h + 2, vector<T>(w + 2));
    }

    size_t height() const noexcept {
        return cumsum.size() - 2;
    }

    size_t width() const noexcept {
        return cumsum[0].size() - 2;
    }

    const auto& data() const noexcept {
        return cumsum;
    }
};