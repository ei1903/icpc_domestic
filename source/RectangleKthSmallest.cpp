#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct Mo {
private:
    int n;
    vector<pair<int, int> > ij;

public:
    Mo(int n) : n(n) {}

    // ([0, i), [0, j))
    void insert(int i, int j){
        ij.emplace_back(i, j);
    }

    template<typename II, typename DI, typename IJ, typename DJ, typename O>
    void run(const II &inc_i, const DI &dec_i, const IJ &inc_j, const DJ &dec_j, const O &out){
        int q = (int) ij.size();
        int bs = n / min<int>(n, sqrt(q));
        vector<int> ord(q);
        iota(ord.begin(), ord.end(), 0);
        sort(ord.begin(), ord.end(), [&](int a, int b){
            int ablock = ij[a].first / bs, bblock = ij[b].first / bs;
            if(ablock != bblock) return (ablock < bblock);
            if(ablock & 1) return (ij[a].second > ij[b].second);
            return (ij[a].second < ij[b].second);
        });
        int i = 0, j = 0;
        for(auto idx : ord){
            while(i < ij[idx].first) inc_i(i++, j);
            while(i > ij[idx].first) dec_i(--i, j);
            while(j < ij[idx].second) inc_j(i, j++);
            while(j > ij[idx].second) dec_j(i, --j);
            out(idx);
        }
    }
};

int main() {
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int n, q;
    cin >> n >> q;

    vector<tuple<int, int, int> > cod_xy, cod_yx;
    vector<int> v;

    for (int i = 0; i < n; ++i) {
        int x, y, w;
        cin >> x >> y >> w;
        v.emplace_back(w);
        cod_xy.emplace_back(x, y, w);
    }

    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());

    int sq = 1;
    while (sq * sq < v.size()) sq++;

    for (auto &&[x, y, w] : cod_xy) w = lower_bound(v.begin(), v.end(), w) - v.begin();

    cod_xy.emplace_back(INT_MAX, INT_MAX, INT_MAX);
    cod_yx = cod_xy;

    for (auto &&[x, y, v] : cod_yx) swap(x, y);

    sort(cod_xy.begin(), cod_xy.end());
    sort(cod_yx.begin(), cod_yx.end());

    Mo mo(cod_xy.size());
    vector<int> sign, k(q);

    // 0-indexed
    for (int i = 0; i < q; ++i) {
        int l, r, d, u;
        cin >> l >> r >> d >> u >> k[i];
        ++k[i];
        l = lower_bound(cod_xy.begin(), cod_xy.end(), tuple(l, 0, 0)) - cod_xy.begin();
        d = lower_bound(cod_yx.begin(), cod_yx.end(), tuple(d, 0, 0)) - cod_yx.begin();
        r = lower_bound(cod_xy.begin(), cod_xy.end(), tuple(r, 0, 0)) - cod_xy.begin();
        u = lower_bound(cod_yx.begin(), cod_yx.end(), tuple(u, 0, 0)) - cod_yx.begin();
        mo.insert(l, d);
        mo.insert(l, u);
        mo.insert(r, d);
        mo.insert(r, u);
        sign.emplace_back(1);
        sign.emplace_back(-1);
        sign.emplace_back(-1);
        sign.emplace_back(1);
    }

    vector<int> re(q, 0), cnt(q);

    {
        vector<vector<int> > memo(q, vector<int>(sq));
        vector<int> seg(sq);
        mo.run([&](int i, int j) {
            if (get<1>(cod_xy[i]) < get<0>(cod_yx[j])) {
                seg[get<2>(cod_xy[i]) / sq]++;
            }
        }, [&](int i, int j) {
            if (get<1>(cod_xy[i]) < get<0>(cod_yx[j])) {
                seg[get<2>(cod_xy[i]) / sq]--;
            }
        }, [&](int i, int j) {
            if (get<1>(cod_yx[j]) < get<0>(cod_xy[i])) {
                seg[get<2>(cod_yx[j]) / sq]++;
            }
        }, [&](int i, int j) {
            if (get<1>(cod_yx[j]) < get<0>(cod_xy[i])) {
                seg[get<2>(cod_yx[j]) / sq]--;
            }
        }, [&](int i) {
            for (int j = 0; j < sq; ++j) {
                memo[i >> 2][j] += seg[j] * sign[i];
            }
        });
        for (int i = 0; i < q; ++i) {
            for (int j = 0; j < sq; ++j) {
                if (cnt[i] + memo[i][j] >= k[i]) {
                    re[i] = j * sq;
                    break;
                }
                cnt[i] += memo[i][j];
            }
        }
    }

    {
        vector<vector<int> > memo(q, vector<int>(sq));
        vector<int> seg(sq * sq);
        mo.run([&](int i, int j) {
            if (get<1>(cod_xy[i]) < get<0>(cod_yx[j])) {
                seg[get<2>(cod_xy[i])]++;
            }
        }, [&](int i, int j) {
            if (get<1>(cod_xy[i]) < get<0>(cod_yx[j])) {
                seg[get<2>(cod_xy[i])]--;
            }
        }, [&](int i, int j) {
            if (get<1>(cod_yx[j]) < get<0>(cod_xy[i])) {
                seg[get<2>(cod_yx[j])]++;
            }
        }, [&](int i, int j) {
            if (get<1>(cod_yx[j]) < get<0>(cod_xy[i])) {
                seg[get<2>(cod_yx[j])]--;
            }
        }, [&](int i) {
            for (int j = 0; j < sq; ++j) {
                memo[i >> 2][j] += seg[re[i >> 2] + j] * sign[i];
            }
        });
        for (int i = 0; i < q; ++i) {
            for (int j = 0; j < sq; ++j) {
                if ((cnt[i] += memo[i][j]) >= k[i]) {
                    re[i] = re[i] + j;
                    break;
                }
            }
        }
    }

    for (int i = 0; i < q; ++i) {
        cout << v[re[i]] << '\n';
    }

    return (0);
}

