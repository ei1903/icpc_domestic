template< typename T >
struct SegmentTree {
    int n, sz;
    vector< T > seg;

    const T ti;

    SegmentTree() = default;

    explicit SegmentTree(int n, const T &ti) : n(n), ti(ti) {
        sz = 1;
        while(sz < n) sz <<= 1;
        seg.assign(2 * sz, ti);
    }

    template<typename F>
    void access(int l, int r, const F &f) {
        for(l += sz, r += sz; l < r; l >>= 1, r >>= 1) {
            if(l & 1) f(seg[l++]);
            if(r & 1) f(seg[--r]);
        }
    }

    template<typename F>
    void access(int k, const F &f) {
        k += sz;
        do {
            f(seg[k]);
        } while (k >>= 1);
    }

    template<typename F>
    void access(const F &f) {
        for (int i = sz * 2 - 1; i > 0; --i) {
            f(seg[i]);
        }
    }

    T operator[](const int &k) {
        return get(k);
    }
};

template< typename T >
SegmentTree< T > get_segment_tree(int N, const T &ti) {
    return SegmentTree{N, ti};
}