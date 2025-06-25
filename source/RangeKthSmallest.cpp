#include <bits/stdc++.h>

using namespace std;

const int MAX_LOG = 18;

int main(){
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int n, q;
    cin >> n >> q;

    vector<int> a(n);

    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    auto v = a;

    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());

    for (auto &&e : a) e = lower_bound(v.begin(), v.end(), e) - v.begin();

    vector<int> l(q), r(q), k(q);
    vector<vector<pair<int, int> > > qi(n + 1);

    for (int i = 0; i < q; ++i) {
        cin >> l[i] >> r[i] >> k[i];
        ++k[i];
        qi[l[i]].emplace_back(i, -1);
        qi[r[i]].emplace_back(i, 1);
    }

    vector<int> x(q), cnt(q);

    for (int i = MAX_LOG - 1; i >= 0; --i) {
        vector<int> seg(1 << (MAX_LOG - i));
        vector<int> memo(q);
        for (int j = 1; j <= n; ++j) {
            seg[a[j - 1] >> i]++;
            for (auto [idx, sign] : qi[j]) {
                memo[idx] += seg[(x[idx] >> i)] * sign;
            }
        }
        for (int j = 0; j < q; ++j) {
            if (cnt[j] + memo[j] < k[j]) {
                x[j] += (1 << i);
                cnt[j] += memo[j];
            }
        }
    }

    for (int i = 0; i < q; ++i) {
        cout << v[x[i]] << '\n';
    }

    return (0);
}