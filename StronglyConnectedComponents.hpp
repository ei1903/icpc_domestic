template<typename Graph = vector<vector<int> > >
struct StronglyConnectedComponents {
public:
    vector<int> comp;
    Graph dag, g;
    vector<vector<int> > group;

    StronglyConnectedComponents(Graph &g) : g(g) {
        rg = Graph(g.size());
        for (int i = 0; i < g.size(); ++i) {
            for (auto &to : g[i]) {
                rg[to].emplace_back(i);
            }
        }

        comp.assign(g.size(), -1);
        used.assign(g.size(), 0);

        for (int i = 0; i < g.size(); ++i) dfs(i);

        reverse(begin(order), end(order));
        int ptr = 0;

        for (auto i : order) if (comp[i] == -1) rdfs(i, ptr), ++ptr;
        dag = Graph(ptr);

        for (int i = 0; i < g.size(); ++i) {
            for (auto &to : g[i]) {
                int x = comp[i], y = comp[to];
                if (x == y) continue;
                dag[x].emplace_back(y);
            }
        }

        group.resize(ptr);
        for (int i = 0; i < g.size(); ++i) {
            group[comp[i]].emplace_back(i);
        }
    }

    int operator[](int k) const {
        return (comp[k]);
    }

private:
    vector<int> order, used;
    Graph rg;

    void dfs(int idx) {
        if (exchange(used[idx], true)) return;
        for (auto &to : g[idx]) dfs(to);
        order.emplace_back(idx);
    }

    void rdfs(int idx, int cnt) {
        if (comp[idx] != -1) return;
        comp[idx] = cnt;
        for (auto &to : rg[idx]) rdfs(to, cnt);
    }
};