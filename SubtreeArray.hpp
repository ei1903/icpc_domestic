template<int ROOT = 0, bool EDGE = false>
struct SubtreeArray {
private:
    vector<vector<int> > tree;
    vector<int> v, l, r, parent, depth;

    void dfs(int cur, int par, int dep) {
        l[cur] = v.size();
        parent[cur] = par;
        depth[cur] = dep;
        if (!EDGE) v.emplace_back(cur);
        for (int to : tree[cur]) {
            if (to == par) continue;
            if (EDGE) v.emplace_back(to);
            dfs(to, cur, dep + 1);
        }
        r[cur] = v.size();
    }

public:
    SubtreeArray(const vector<vector<int> > &tree) : tree(tree), l(tree.size()), r(tree.size()), parent(tree.size()), depth(tree.size()) {
        dfs(ROOT, -1, 0);
    }

    int getDepth(int u) {
        return depth[u];
    }

    int getNode(int u, int v) {
        return parent[u] == v ? u : v;
    }

    vector<int> getArray() {
        return v;
    }

    pair<int, int> getRange(int v) {
        return make_pair(l[v], r[v]);
    }

    size_t size() {
        return v.size();
    }

    int operator[](int i) {
        return v[i];
    }
};