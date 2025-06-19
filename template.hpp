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

// {f(i) | i in [begin, left) ∪ (right, rbegin]}
template<class It, class F>
pair<It, reverse_iterator<It> > bsearch(It begin, It end, const F &f) {
    auto rbegin = reverse_iterator(end), rend = reverse_iterator(begin);
    if (begin == end) return make_pair(end, rend);
    It left; reverse_iterator<It> right;
    if (f(*begin)) {
        auto l = begin, r = end;
        while (r - l > 1) {
            auto mid = l + (r - l) / 2;
            if (f(*mid)) l = mid; else r = mid;
        }
        left = r;
    } else left = begin;
    if (f(*rbegin)) {
        auto l = rbegin, r = rend;
        while (r - l > 1) {
            auto mid = l + (r - l) / 2;
            if (f(*mid)) l = mid; else r = mid;
        }
        right = r;
    } else right = rbegin;
    return make_pair(left, right);
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

template <class T> void bye(T x){ cout << x << '\n'; exit(0); }

constexpr int dx[] = {1,0,-1,0,1,1,-1,-1,0};
constexpr int dy[] = {0,1,0,-1,1,-1,-1,1,0};

int main(){
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    cout.setf(ios_base::fixed);
    cout.precision(12);

    return (0);
}