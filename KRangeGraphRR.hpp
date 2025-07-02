template<typename Weight>
struct KRangeGraphRR : vector<vector<pair<int, Weight> > > {
    int n;
    const int k;

    KRangeGraphRR(int n, int k) : n(n), k(k) {
        (*this).resize(n * 5);
        for (int i = 0; i + 1 < n; ++i) {
            (*this)[i + n].emplace_back(i, Weight());
            (*this)[i + n * 2].emplace_back(i, Weight());
            (*this)[i].emplace_back(i + n * 3, Weight());
            (*this)[i].emplace_back(i + n * 4, Weight());
            if ((i + 1) % k != 0) {
                (*this)[i + n].emplace_back(i + n + 1, Weight());
                (*this)[i + n * 2 + 1].emplace_back(i + n * 2, Weight());
                (*this)[i + n * 3].emplace_back(i + n * 3 + 1, Weight());
                (*this)[i + n * 4 + 1].emplace_back(i + n * 4, Weight());
            }
        }
    }

    /* [l1, r1) -> [l2, r2) */
    void add_edge(int l1, int r1, int l2, int r2, const Weight &w) {
        (*this)[l1 + n * 4].emplace_back(l2 + n, w);
        (*this)[r1 - 1 + n * 3].emplace_back(r2 - 1 + n * 2, w);
    }

    int idx(const int &k) const {
        return (k);
    }
};