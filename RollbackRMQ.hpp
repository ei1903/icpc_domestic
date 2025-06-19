template<typename T>
struct RollbackRMQ {
    int bs;
    T ti;
    vector<T> a, b;
    vector<tuple<int, T, T> > st;

    RollbackRMQ(int n, T ti) : a(n, ti), bs(max(1, (int) sqrt(n))), b((n + bs - 1) / bs, ti), ti(ti) {}
    RollbackRMQ(const vector<T> &a, T ti) : a(a), bs(max(1, (int) sqrt(a.size()))), b((a.size() + bs - 1) / bs, ti), ti(ti) {
        for (int i = 0; i < a.size(); ++i) {
            b[i / bs] = max(b[i / bs], a[i]);
        }
    }

    T get(int k) const {
        return a[k];
    }

    void add(int k, const T &v = 1) {
        assert(v >= 0);
        st.emplace_back(k, a[k], b[k / bs]);
        a[k] += v;
        b[k / bs] = max(b[k / bs], a[k]);
    }

    void update(int k, const T &v) {
        assert(v >= a[k]);
        st.emplace_back(k, a[k], b[k / bs]);
        a[k] = v;
        b[k / bs] = max(b[k / bs], a[k]);
    }

    T query(int l, int r) {
        T ret = T();
        for (int i = l; i < min(r, (l + bs) / bs * bs); ++i) {
            ret = max(ret, a[i]);
        }
        for (int i = (l + bs) / bs; i < r / bs; ++i) {
            ret = max(ret, b[i]);
        }
        for (int i = max((l + bs) / bs, r / bs) * bs; i < r; ++i) {
            ret = max(ret, a[i]);
        }
        return ret;
    }

    int lower_bound(T k) const {
        int bi = 0;
        T maxv = ti;
        while (bi < (int) b.size() - 1 && max(maxv, b[bi]) < k) {
            maxv = max(maxv, b[bi]);
            bi++;
        }
        for (int i = bi * bs; i < a.size(); ++i) {
            maxv = max(maxv, a[i]);
            if (maxv >= k) return i;
        }
        return a.size();
    }

    int upper_bound(T k) const {
        int bi = 0;
        T maxv = ti;
        while (bi < (int) b.size() - 1 && max(maxv, b[bi]) <= k) {
            maxv = max(maxv, b[bi]);
            bi++;
        }
        for (int i = bi * bs; i < a.size(); ++i) {
            maxv = max(maxv, a[i]);
            if (maxv > k) return i;
        }
        return a.size();
    }

    bool undo() {
        if (st.empty()) return false;
        auto [k, ai, bi] = st.back();
        st.pop_back();
        a[k] = ai;
        b[k / bs] = bi;
        return true;
    }

    void snapshot() {
        st.clear();
    }

    void rollback() {
        while (undo());
    }
};