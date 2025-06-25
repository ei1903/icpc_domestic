#include <bits/extc++.h>

using namespace std;

#define rep(i,n) for(int i=0;i<(n);++i)
#define reps(i,n) for(int i=1;i<=(n);++i)
#define all(x) begin(x),end(x)
#define updiv(a, b) (((a) + (b) - 1) / (b))
using ll = long long;
using ull = unsigned long long;
constexpr int INF  = 0x3f3f3f3f;
constexpr long long LINF = 0x3f3f3f3f3f3f3f3fLL;
constexpr int mod1 = 1000000007;
constexpr int mod2 = 998244353;

template <class Func>
class FixPoint : Func {
public:
    explicit constexpr FixPoint(Func&& f) noexcept : Func(forward<Func>(f)) {}

    template <class... Args>
    constexpr decltype(auto) operator()(Args&&... args) const {
        return Func::operator()(*this, std::forward<Args>(args)...);
    }
};

template <class Func>
static inline constexpr decltype(auto) makeFixPoint(Func&& f) noexcept {
    return FixPoint<Func>{forward<Func>(f)};
}

template <class T, class It = decltype(std::begin(std::declval<T>()))>
inline constexpr auto Indexed(T&& iterable) {
    struct Iterator {
        size_t index;
        It it;
        constexpr bool operator!= (const Iterator& other) const { return it != other.it; }
        constexpr void operator++() { ++index; ++it; }
        constexpr void operator--() { --index; --it; }
        constexpr auto operator*() const { return std::tie(index, *it); }
    };
    struct IterableWrapper {
        T iterable;
        constexpr auto begin() { return Iterator{ 0, std::begin(iterable) }; }
        constexpr auto end() { return Iterator{ std::size(iterable), std::end(iterable) }; }
    };
    return IterableWrapper{ std::forward<T>(iterable) };
}

template<class T, class U> istream& operator>>(istream& is, pair<T, U>& p){ is >> p.first >> p.second; return (is); }
template<class T, class U> ostream& operator<<(ostream& os, pair<T, U>& p){ os << p.first << ' ' << p.second; return (os); }
template<class T> istream& operator>>(istream& is, vector<T>& v){ for (auto &&e : v) is >> e; return (is); }
template<class T> ostream& operator<<(ostream& os, vector<T>& v){ for (auto &&e : v) os << e << ' '; return (os); }

template<class T> inline const T& max(const vector<T> &v) { return *max_element(v.begin(), v.end()); }
template<class T> inline const T& min(const vector<T> &v) { return *min_element(v.begin(), v.end()); }
template<class T> inline T mex(vector<T> v) {
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    for (T i = 0; i < (T) v.size(); ++i) if (v[i] != i) return i;
    return v.size();
}
template<class T> inline T mex(initializer_list<T> l) { return mex(vector<T>(l)); }

template <class A, class B> inline bool chmax(A &a, const B &b) { return b > a && (a = b, true); }
template <class A, class B> inline bool chmin(A &a, const B &b) { return b < a && (a = b, true); }

template <class T> using max_heap = priority_queue<T>;
template <class T> using min_heap = priority_queue<T, vector<T>, greater<T> >;
template <class A, class B> using umap = unordered_map<A, B>;
template <class T> using uset = unordered_set<T>;

template <class T> using Max_Heap = __gnu_pbds::priority_queue<T, less<T>, __gnu_pbds::rc_binomial_heap_tag>;
template <class T> using Min_Heap = __gnu_pbds::priority_queue<T, greater<T>, __gnu_pbds::rc_binomial_heap_tag>;
template <class T> using Set = __gnu_pbds::tree<T, __gnu_pbds::null_type, less<T>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;
template <class K, class V> using Umap = __gnu_pbds::gp_hash_table<K, V>;
template <class T> using Rope = __gnu_cxx::rope<T>;
using Trie = __gnu_pbds::trie<string, __gnu_pbds::null_type, __gnu_pbds::trie_string_access_traits<>, __gnu_pbds::pat_trie_tag, __gnu_pbds::trie_prefix_search_node_update>;

template <class T> void bye(T x){ cout << x << '\n'; exit(0); }

constexpr int dx[] = {1,0,-1,0,1,1,-1,-1,0};
constexpr int dy[] = {0,1,0,-1,1,-1,-1,1,0};

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
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    cout.setf(ios_base::fixed);
    cout.precision(12);

    int n, q;
    cin >> n >> q;

    vector<tuple<int, int, int> > cod;

    for (int i = 0; i < n; ++i) {
        int x, y, v;
        cin >> x >> y >> v;
        --v;
        cod.emplace_back(x, y, v);
    }

    cod.emplace_back(INF, INF, INF);

    auto cod_xy = cod;
    auto cod_yx = cod;

    for (auto &&[x, y, v] : cod_yx) swap(x, y);

    sort(all(cod_xy));
    sort(all(cod_yx));

    vector<ll> res(q);
    vector<int> com, t(q);
    Mo mo(n);

    for (int i = 0; i < q; ++i) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2 >> t[i];
        --t[i];
        x1 = lower_bound(all(cod_xy), tuple(x1, 0, 0)) - cod_xy.begin();
        y1 = lower_bound(all(cod_yx), tuple(y1, 0, 0)) - cod_yx.begin();
        x2 = upper_bound(all(cod_xy), tuple(x2, INF, INF)) - cod_xy.begin();
        y2 = upper_bound(all(cod_yx), tuple(y2, INF, INF)) - cod_yx.begin();
        mo.insert(x1, y1);
        mo.insert(x1, y2);
        mo.insert(x2, y1);
        mo.insert(x2, y2);
        com.emplace_back(1);
        com.emplace_back(-1);
        com.emplace_back(-1);
        com.emplace_back(1);
    }

    RSQ<ll> sum(n), cnt(n);

    mo.run([&](int i, int j) {
        if (get<1>(cod_xy[i]) < get<0>(cod_yx[j])) {
            sum.add(get<2>(cod_xy[i]), get<2>(cod_xy[i]));
            cnt.add(get<2>(cod_xy[i]), 1);
        }
    }, [&](int i, int j) {
        if (get<1>(cod_xy[i]) < get<0>(cod_yx[j])) {
            sum.add(get<2>(cod_xy[i]), -get<2>(cod_xy[i]));
            cnt.add(get<2>(cod_xy[i]), -1);
        }
    }, [&](int i, int j) {
        if (get<1>(cod_yx[j]) < get<0>(cod_xy[i])) {
            sum.add(get<2>(cod_yx[j]), get<2>(cod_yx[j]));
            cnt.add(get<2>(cod_yx[j]), 1);
        }
    }, [&](int i, int j) {
        if (get<1>(cod_yx[j]) < get<0>(cod_xy[i])) {
            sum.add(get<2>(cod_yx[j]), -get<2>(cod_yx[j]));
            cnt.add(get<2>(cod_yx[j]), -1);
        }
    }, [&](int i) {
        int lc = cnt.query(t[i / 4]);
        ll ls = sum.query(t[i / 4]);
        res[i / 4] += ((long long) lc * t[i / 4] - ls + sum.query(n) - ls - (long long) (cnt.query(n) - lc) * t[i / 4]) * com[i];
    });

    for (auto e : res) {
        cout << e << '\n';
    }

    return (0);
}