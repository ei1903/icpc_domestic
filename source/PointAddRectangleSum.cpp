#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>

using namespace std;

#define all(x) begin(x),end(x)
using ll = long long;
constexpr int INF = INT_MAX;

struct IoSetup {
    IoSetup() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
        cerr << fixed << setprecision(10);
    }
} iosetup;

struct Scanner {
    public:
    explicit Scanner(FILE *fp) : fp(fp) {}

    template <typename T, typename... E>
    void read(T &t, E &...e) {
        read_single(t);
        read(e...);
    }

    private:
    static constexpr size_t line_size = 1 << 16;
    static constexpr size_t int_digits = 20;
    char line[line_size + 1] = {};
    FILE *fp = nullptr;
    char *st = line;
    char *ed = line;

    void read() {}

    static inline bool is_space(char c) { return c <= ' '; }

    void reread() {
        ptrdiff_t len = ed - st;
        memmove(line, st, len);
        char *tmp = line + len;
        ed = tmp + fread(tmp, 1, line_size - len, fp);
        *ed = 0;
        st = line;
    }

    void skip_space() {
        while (true) {
            if (st == ed) reread();
            while (*st && is_space(*st)) ++st;
            if (st != ed) return;
        }
    }

    template <typename T, enable_if_t<is_integral<T>::value, int> = 0>
    void read_single(T &s) {
        skip_space();
        if (st + int_digits >= ed) reread();
        bool neg = false;
        if (is_signed<T>::value && *st == '-') {
            neg = true;
            ++st;
        }
        typename make_unsigned<T>::type y = *st++ - '0';
        while (*st >= '0') {
            y = 10 * y + *st++ - '0';
        }
        s = (neg ? -y : y);
    }

    template <typename T, enable_if_t<is_same<T, string>::value, int> = 0>
    void read_single(T &s) {
        s = "";
        skip_space();
        while (true) {
            char *base = st;
            while (*st && !is_space(*st)) ++st;
            s += string(base, st);
            if (st != ed) return;
            reread();
        }
    }

    template <typename T>
    void read_single(vector<T> &s) {
        for (auto &d : s) read(d);
    }
};

struct Printer {
    public:
    explicit Printer(FILE *fp) : fp(fp) {}

    ~Printer() { flush(); }

    template <bool f = false, typename T, typename... E>
    void write(const T &t, const E &...e) {
        if (f) write_single(' ');
        write_single(t);
        write<true>(e...);
    }

    template <typename... T>
    void writeln(const T &...t) {
        write(t...);
        write_single('\n');
    }

    void flush() {
        fwrite(line, 1, st - line, fp);
        st = line;
    }

    private:
    FILE *fp = nullptr;
    static constexpr size_t line_size = 1 << 16;
    static constexpr size_t int_digits = 20;
    char line[line_size + 1] = {};
    char *st = line;

    template <bool f = false>
    void write() {}

    void write_single(const char &t) {
        if (st + 1 >= line + line_size) flush();
        *st++ = t;
    }

    template <typename T, enable_if_t<is_integral<T>::value, int> = 0>
    void write_single(T s) {
        if (st + int_digits >= line + line_size) flush();
        st += to_chars(st, st + int_digits, s).ptr - st;
    }

    void write_single(const string &s) {
        for (auto &c : s) write_single(c);
    }

    void write_single(const char *s) {
        while (*s != 0) write_single(*s++);
    }

    template <typename T>
    void write_single(const vector<T> &s) {
        for (size_t i = 0; i < s.size(); i++) {
            if (i) write_single(' ');
            write_single(s[i]);
        }
    }
};

struct Mo {
private:
    int n;
    vector<pair<int, int> > ij;

public:
    Mo(int n) : n(n) {}

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

template<typename T>
struct RSQ {
    int bs;
    vector<T> a, b;

    RSQ(int n) : a(n), bs(max(1, (int) sqrt(n))), b((n + bs - 1) / bs) {}
    RSQ(const vector<T> &a) : a(a), bs(max(1, (int) sqrt(a.size()))), b((a.size() + bs - 1) / bs) {}

    T get(int k) const {
        return a[k];
    }

    void add(int k, const T &v = 1) {
        b[k / bs] += v;
        a[k] += v;
    }

    void update(int k, const T &v) {
        b[k / bs] += v - a[k];
        a[k] = v;
    }

    T query(int l, int r) {
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

    T query(int r) {
        return query(0, r);
    }
};

int main(){
    Scanner in(stdin);
    Printer out(stdout);

    int n, q;
    in.read(n, q);

    vector<tuple<int, int, int> > cod;
    vector<int> ws(n + q);

    for (int i = 0; i < n; ++i) {
        int x, y;
        in.read(x, y, ws[i]);
        cod.emplace_back(x, y, i);
    }

    vector<ll> res(q);
    vector<int> sign, query_idx;
    vector<tuple<int, int, int, int, int> > queries;

    for (int i = 0; i < q; ++i) {
        int com;
        in.read(com);

        if (com == 0) {
            int x, y;
            in.read(x, y, ws[n + i]);
            cod.emplace_back(x, y, n + i);
            queries.emplace_back(com, x, y, n + i, int());
        } else {
            int l, d, r, u;
            in.read(l, d, r, u);
            queries.emplace_back(com, l, d, r, u);
            query_idx.emplace_back(i);
        }
    }

    cod.emplace_back(INF, INF, INF);
    auto cod_xy = cod;
    auto cod_yx = cod;

    for (auto &&[x, y, v] : cod_yx) swap(x, y);

    sort(all(cod_xy));
    sort(all(cod_yx));

    Mo mo(cod.size());
    RSQ<ll> rsq(n + q);

    for (auto [com, l, d, r, u] : queries) {
        if (com == 1) {
            l = lower_bound(all(cod_xy), tuple(l, 0, 0)) - cod_xy.begin();
            d = lower_bound(all(cod_yx), tuple(d, 0, 0)) - cod_yx.begin();
            r = lower_bound(all(cod_xy), tuple(r, 0, 0)) - cod_xy.begin();
            u = lower_bound(all(cod_yx), tuple(u, 0, 0)) - cod_yx.begin();
            mo.insert(l, d);
            mo.insert(l, u);
            mo.insert(r, d);
            mo.insert(r, u);
            sign.emplace_back(1);
            sign.emplace_back(-1);
            sign.emplace_back(-1);
            sign.emplace_back(1);
        }
    }

    mo.run([&](int i, int j) {
        if (get<1>(cod_xy[i]) < get<0>(cod_yx[j])) {
            rsq.add(get<2>(cod_xy[i]), ws[get<2>(cod_xy[i])]);
        }
    }, [&](int i, int j) {
        if (get<1>(cod_xy[i]) < get<0>(cod_yx[j])) {
            rsq.add(get<2>(cod_xy[i]), -ws[get<2>(cod_xy[i])]);
        }
    }, [&](int i, int j) {
        if (get<1>(cod_yx[j]) < get<0>(cod_xy[i])) {
            rsq.add(get<2>(cod_yx[j]), ws[get<2>(cod_yx[j])]);
        }
    }, [&](int i, int j) {
        if (get<1>(cod_yx[j]) < get<0>(cod_xy[i])) {
            rsq.add(get<2>(cod_yx[j]), -ws[get<2>(cod_yx[j])]);
        }
    }, [&](int i) {
        res[query_idx[i / 4]] += rsq.query(n + query_idx[i / 4]) * sign[i];
    });

    for (int i = 0; i < q; ++i) {
        if (get<0>(queries[i]) == 1) {
            out.writeln(res[i]);
        }
    }

    return (0);
}
