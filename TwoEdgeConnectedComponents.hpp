struct TwoEdgeConnectedComponents {
public:
    using Graph = vector<vector<int> >;

    Graph g, tree;
    vector<vector<int> > group;
    vector<int> ord, low, comp;
    vector<pair<int, int> > bridge;

    explicit TwoEdgeConnectedComponents(const Graph &G) : g(G), used(G.size()), ord(G.size()), low(G.size()), comp(G.size(), -1) {
        int k = 0;
        for (int i = 0; i < g.size(); ++i) {
            if (!used[i]) k = dfs1(i, k, -1);
        }
        k = 0;
        for (int i = 0; i < g.size(); ++i) {
            if (comp[i] == -1) dfs2(i, -1, k);
        }
        group.resize(k);
        for (int i = 0; i < g.size(); ++i) {
            group[comp[i]].emplace_back(i);
        }
        tree.resize(k);
        for (auto &e : bridge) {
            tree[comp[e.first]].emplace_back(comp[e.second]);
            tree[comp[e.second]].emplace_back(comp[e.first]);
        }
    }

    explicit TwoEdgeConnectedComponents() = default;

private:
    vector<bool> used;

    int dfs1(int idx, int k, int par) {
        used[idx] = true;
        ord[idx] = k++;
        low[idx] = ord[idx];
        int cnt = 0;
        bool one = true;
        for (auto &to : g[idx]) {
            if (to == par && exchange(one, false)) continue;
            if (!used[to]) {
                ++cnt;
                k = dfs1(to, k, idx);
                low[idx] = min(low[idx], low[to]);
                if (ord[idx] < low[to]) bridge.emplace_back(idx, to);
            } else {
                low[idx] = min(low[idx], ord[to]);
            }
        }
        return (k);
    }

    void dfs2(int idx, int par, int &k) {
        if (par >= 0 && ord[par] >= low[idx]) comp[idx] = comp[par];
        else comp[idx] = k++;
        for (auto &to : g[idx]) {
            if (comp[to] == -1) dfs2(to, idx, k);
        }
    }
};
