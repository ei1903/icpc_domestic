struct FastSet {
    static constexpr uint32_t B = 64;
    int n, lg;
    vector<vector<uint64_t> > seg;

    FastSet(int _n) : n(++_n) {
        do {
            seg.emplace_back(vector<uint64_t>((_n + B - 1) / B));
            _n = (_n + B - 1) / B;
        } while (_n > 1);
        lg = (int) seg.size();
    }

    bool contain(int k) const {
        return ((seg[0][k / B] >> (k % B) & 1) != 0);
    }

    void insert(int k) {
        for (int h = 0; h < lg; ++h) {
            seg[h][k / B] |= 1ULL << (k % B);
            k /= B;
        }
    }

    void erase(int k) {
        for (int h = 0; h < lg; ++h) {
            seg[h][k / B] &= ~(1ULL << (k % B));
            if (seg[h][k / B]) break;
            k /= B;
        }
    }

    // k以上の最小
    int next(int k) {
        if (k < 0) k = 0;
        if (k >= n) return (-1);
        for (int h = 0; h < lg; ++h) {
            if (k / B == seg[h].size()) break;
            uint64_t d = seg[h][k / B] >> (k % B);
            if (!d) {
                k = k / B + 1;
                continue;
            }
            k += __builtin_ctzll(d);
            for (int g = h - 1; g >= 0; --g) {
                k *= B;
                k += __builtin_ctzll(seg[g][k / B]);
            }
            return (k);
        }
        return (-1);
    }

    // k以下の最大
    int prev(int k) {
        if (k > n) k = n;
        for (int h = 0; h < lg; ++h) {
            if (k < 0) break;
            uint64_t d = seg[h][k / B] << (63 - k % 64);
            if (!d) {
                k = k / B - 1;
                continue;
            }
            k += 63 - __builtin_clzll(d) - (B - 1);
            for (int g = h - 1; g >= 0; --g) {
                k *= B;
                k += 63 - __builtin_clzll(seg[g][k / B]);
            }
            return (k);
        }
        return (-1);
    }
};
