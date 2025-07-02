template<typename Weight>
struct KRangeGraphPR : vector<vector<pair<int, Weight> > > {
    int n;
    const int k;

    KRangeGraphPR(int n, int k) : n(n), k(k) {
        (*this).resize(n * 3);
        for (int i = 0; i + 1 < n; ++i) {
            (*this)[i + n].emplace_back(i, Weight());
            (*this)[i + n * 2].emplace_back(i, Weight());
            if ((i + 1) % k != 0) {
                (*this)[i + n].emplace_back(i + n + 1, Weight());
                (*this)[i + n * 2 + 1].emplace_back(i + n * 2, Weight());
            }
        }
    }

    /* u -> [l, r) */
    void add_edge(int u, int l, int r, const Weight &w) {
        (*this)[u].emplace_back(l + n, w);
        (*this)[u].emplace_back(r - 1 + n * 2, w);
    }

    int idx(const int &k) const {
        return (k);
    }
};