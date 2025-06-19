template <typename T>
class Compress {
    vector<T> xs;

public:
    Compress() = default;

    Compress(const vector<T> &vs) {
        add(vs);
    }

    void add(const vector<T> &vs) {
        copy(vs.begin(), vs.end(), back_inserter(xs));
    }

    void add(const T &x) {
        xs.emplace_back(x);
    }

    void build() {
        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());
    }

    int get(const T &v) const {
        return distance(xs.begin(), lower_bound(xs.begin(), xs.end(), v));
    }

    vector<int> get(const vector<T> &vs) const {
        vector<int> ret;
        transform(vs.begin(), vs.end(), back_inserter(ret), [&](const T &v) { return get(v); });
        return ret;
    }

    std::map<T, int> map() const {
        std::map<T, int> ret;
        for (int i = 0; i < xs.size(); ++i) {
            ret[xs[i]] = i;
        }
        return ret;
    }

    unordered_map<T, int> umap() const {
        unordered_map<T, int> ret;
        for (int i = 0; i < xs.size(); ++i) {
            ret[xs[i]] = i;
        }
        return ret;
    }

    const size_t size() const {
        return xs.size();
    }

    const T &operator[](size_t k) const {
        return xs[k];
    }
};