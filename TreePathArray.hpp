struct TreePathArray {
private:
    vector<vector<int> > tree;
    vector<int> v, pos, parent, depth;

    void dfs(int cur, int par, int dep) {
        pos[cur] = v.size();
        parent[cur] = par;
        depth[cur] = dep;
        for (int to : tree[cur]) {
            if (to == par) continue;
            v.emplace_back(to);
            dfs(to, cur, dep + 1);
        }
        v.emplace_back(cur);
    }

public:
    TreePathArray(const vector<vector<int> > &tree) : tree(tree), pos(tree.size()), parent(tree.size()), depth(tree.size()) {
        dfs(0, -1, 0);
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

    pair<int, int> getRange(int u, int v) {
        return minmax(pos[u], pos[v]);
    }

    size_t size() {
        return v.size();
    }

    int operator[](int i) {
        return v[i];
    }
};