template<typename A, typename B>
struct SquareRootDecomposition {
    int bs;
    vector<A> a;
    vector<B> b;

    SquareRootDecomposition() = default;
    SquareRootDecomposition(int n, const A& tia = A(), const B& tib = B(), const int lower = 1, const int upper = INT_MAX) : a(n, tia), bs(clamp((int) sqrt(n), lower, upper)), b((n + bs - 1) / bs, tib) {}

    pair<A&, B&> get(int k) {
        return pair<A&, B&>(a[k], b[k / bs]);
    }

    pair<A, B> get(int k) const {
        return pair(a[k], b[k / bs]);
    }

    template<typename F, typename G>
    void query(int l, int r, const F &f, const G &g) {
        for (int i = l; i < min(r, (l + bs) / bs * bs); ++i) {
            f(a[i]);
        }
        for (int i = (l + bs) / bs; i < r / bs; ++i) {
            g(b[i]);
        }
        for (int i = max((l + bs) / bs, r / bs) * bs; i < r; ++i) {
            f(a[i]);
        }
    }
};