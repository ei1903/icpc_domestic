template<typename Weight>
struct DoubleSegmentTreeGraph : vector<vector<pair<int, Weight> > > {
    int sz0;

    DoubleSegmentTreeGraph(int n) {
        sz0 = 1;
        while (sz0 < n) sz0 <<= 1;
        (*this).resize(4 * sz0);

        for (int k = 0; k < sz0; ++k) {
            (*this)[k + sz0].emplace_back(k + sz0 * 3, 0);
        }

        for (int k = sz0 - 1; k > 0; --k) {
            (*this)[k].emplace_back(2 * k + 0, 0);
            (*this)[k].emplace_back(2 * k + 1, 0);

            (*this)[2 * k + 0 + sz0 * 2].emplace_back(k + sz0 * 2, 0);
            (*this)[2 * k + 1 + sz0 * 2].emplace_back(k + sz0 * 2, 0);
        }
    }

    /* [l1, r1) -> [l2, r2) */
    void add_edge(int l1, int r1, int l2, int r2, const Weight &w) {
        int sz = (*this).size();

        (*this).emplace_back(vector<pair<int, Weight> >());
        (*this).emplace_back(vector<pair<int, Weight> >());

        for (l1 += sz0, r1 += sz0; l1 < r1; l1 >>= 1, r1 >>= 1) {
            if (l1 & 1) (*this)[l1++ + sz0 * 2].emplace_back(sz, 0);
            if (r1 & 1) (*this)[--r1 + sz0 * 2].emplace_back(sz, 0);
        }

        (*this)[sz].emplace_back(sz + 1, w);

        for (l2 += sz0, r2 += sz0; l2 < r2; l2 >>= 1, r2 >>= 1) {
            if (l2 & 1) (*this)[sz + 1].emplace_back(l2++, 0);
            if (r2 & 1) (*this)[sz + 1].emplace_back(--r2, 0);
        }
    }

    int idx(const int &k) const {
        return (k + sz0);
    }
};