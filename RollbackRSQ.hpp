template<typename T>
struct RollbackRSQ {
    int bs;
    vector<T> a, b;
    vector<pair<int, T> > st;

    RollbackRSQ(int n) : a(n), bs(max(1, (int) sqrt(n))), b((n + bs - 1) / bs) {}
    RollbackRSQ(const vector<T> &a) : a(a), bs(max(1, (int) sqrt(a.size()))), b((a.size() + bs - 1) / bs) {
        for (int i = 0; i < a.size(); ++i) {
            b[i / bs] += a[i];
        }
    }

    T get(int k) const {
        return a[k];
    }

    void add(int k, const T &v = 1) {
        st.emplace_back(k, a[k]);
        a[k] += v;
        b[k / bs] += v;
    }

    void update(int k, const T &v) {
        st.emplace_back(k, a[k]);
        b[k / bs] += v - a[k];
        a[k] = v;
    }

    T query(int l, int r) const {
        T ret = T();
        for (int i = l; i < min(r, (l + bs) / bs * bs); ++i) {
            ret += a[i];
        }
        for (int i = (l + bs) / bs; i < r / bs; ++i) {
            ret += b[i];
        }
        for (int i = max((l + bs) / bs, r / bs) * bs; i < r; ++i) {
            ret += a[i];
        }
        return ret;
    }

    T query(int r) const {
        return query(0, r);
    }

    int lower_bound(T k) const {
        int bi = 0;
        T sum = 0;
        while (bi < (int) b.size() - 1 && sum + b[bi] < k) {
            sum += b[bi];
            bi++;
        }
        for (int i = bi * bs; i < a.size(); ++i) {
            sum += a[i];
            if (sum >= k) return i;
        }
        return a.size();
    }

    int upper_bound(T k) const {
        int bi = 0;
        T sum = 0;
        while (bi < (int) b.size() - 1 && sum + b[bi] <= k) {
            sum += b[bi];
            bi++;
        }
        for (int i = bi * bs; i < a.size(); ++i) {
            sum += a[i];
            if (sum > k) return i;
        }
        return a.size();
    }

    bool undo() {
        if (st.empty()) return false;
        auto [k, v] = st.back();
        st.pop_back();
        b[k / bs] += v - a[k];
        a[k] = v;
        return true;
    }

    void snapshot() {
        st.clear();
    }

    void rollback() {
        while (undo());
    }
};