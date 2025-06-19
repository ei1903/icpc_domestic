template<typename Weight>
struct SegmentTreeGraph : vector<vector<pair<int, Weight> > > {
    int sz0;

    SegmentTreeGraph(int n) {
        sz0 = 1;
        while (sz0 < n) sz0 <<= 1;
        (*this).resize(2 * sz0);

        for (int k = sz0 - 1; k > 0; --k) {
            (*this)[k].emplace_back(2 * k + 0, 0);
            (*this)[k].emplace_back(2 * k + 1, 0);
        }
    }

    /* u -> [l, r) */
    void add_edge(int u, int l, int r, const Weight &w) {
        int sz = (*this).size();

        (*this).emplace_back(vector<pair<int, Weight> >());
        (*this).emplace_back(vector<pair<int, Weight> >());

        (*this)[u + sz0].emplace_back(sz, 0);
        (*this)[sz].emplace_back(sz + 1, w);

        for (l += sz0, r += sz0; l < r; l >>= 1, r >>= 1) {
            if (l & 1) (*this)[sz + 1].emplace_back(l++, 0);
            if (r & 1) (*this)[sz + 1].emplace_back(--r, 0);
        }
    }

    int idx(const int &k) const {
        return (k + sz0);
    }
};
