template<typename Weight>
struct KRangeGraphRP : vector<vector<pair<int, Weight> > > {
    int n;
    const int k;

    KRangeGraphRP(int n, int k) : n(n), k(k) {
        (*this).resize(n * 3);
        for (int i = 0; i + 1 < n; ++i) {
            (*this)[i].emplace_back(i + n, Weight());
            (*this)[i].emplace_back(i + n * 2, Weight());
            if ((i + 1) % k != 0) {
                (*this)[i + n].emplace_back(i + n + 1, Weight());
                (*this)[i + n * 2 + 1].emplace_back(i + n * 2, Weight());
            }
        }
    }

    /* [l, r) -> u */
    void add_edge(int l, int r, int u, const Weight &w) {
        (*this)[l + n * 2].emplace_back(u, w);
        (*this)[r - 1 + n].emplace_back(u, w);
    }

    int idx(const int &k) const {
        return (k);
    }
};