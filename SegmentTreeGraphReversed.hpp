template<typename Weight>
struct SegmentTreeGraph : vector<vector<pair<int, Weight> > > {
    int sz0;

    SegmentTreeGraph(int n) {
        sz0 = 1;
        while (sz0 < n) sz0 <<= 1;
        (*this).resize(2 * sz0);

        for (int k = sz0 - 1; k > 0; --k) {
            (*this)[2 * k + 0].emplace_back(k, 0);
            (*this)[2 * k + 1].emplace_back(k, 0);
        }
    }

    /* [l, r) -> u */
    void add_edge(int l, int r, int u, const Weight &w) {
        int sz = (*this).size();

        (*this).emplace_back(vector<pair<int, Weight> >());
        (*this).emplace_back(vector<pair<int, Weight> >());

        for (l += sz0, r += sz0; l < r; l >>= 1, r >>= 1) {
            if (l & 1) (*this)[l++].emplace_back(sz, 0);
            if (r & 1) (*this)[--r].emplace_back(sz, 0);
        }

        (*this)[sz].emplace_back(sz + 1, w);
        (*this)[sz + 1].emplace_back(u + sz0, 0);
    }

    int idx(const int &k) const {
        return (k + sz0);
    }
};
