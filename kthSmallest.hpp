template <int MAX_LOG, class T, class F>
vector<int> kthSmallest(const int q, const vector<T> &k, const F &f) {
    vector<int> ret(q);
    vector<T> cnt(q);

    for (int i = MAX_LOG - 1; i >= 0; --i) {
        vector<T> seg(1 << (MAX_LOG - i)), memo(q);
        f(
            [&](int val, T c = 1) { seg[val >> i] += c; },
            [&](int idx, T p = 1) { memo[idx] += seg[(ret[idx] >> i)] * p; }
        );
        for (int j = 0; j < q; ++j) {
            if (cnt[j] + memo[j] < k[j]) {
                ret[j] += (1 << i);
                cnt[j] += memo[j];
            }
        }
    }
    return ret;
}