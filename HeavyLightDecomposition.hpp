struct HeavyLightDecomposition {
public:
    vector<vector<int> > g;
    vector<int> sz, in, out, head, rev, par, dep;

    HeavyLightDecomposition(const vector<vector<int> > &G) : g(G) {
        sz.resize(g.size(), 0);
        in.resize(g.size(), 0);
        out.resize(g.size(), 0);
        head.resize(g.size(), 0);
        rev.resize(g.size(), 0);
        par.resize(g.size(), 0);
        dep.resize(g.size(), 0);
        dfs_sz(0, -1, 0);
        dfs_hld(0, -1);
    }

    int la(int v, int k) {
        while (true) {
            int u = head[v];
            if (in[v] - k >= in[u]) return (rev[in[v] - k]);
            k -= in[v] - in[u] + 1;
            v = par[u];
        }
    }

    int lca(int u, int v) const {
        for (;; v = par[head[v]]) {
            if (in[u] > in[v]) swap(u, v);
            if (head[u] == head[v]) return (u);
        }
    }

    int dist(int u, int v) const {
        return (dep[u] + dep[v] - 2 * dep[lca(u, v)]);
    }

    template<typename E, typename F, typename G, typename S>
    E query(int u, int v, const E &ti, const F &f, const G &g, const S &s, bool edge = false) {
        E l = ti, r = ti;
        for (;; v = par[head[v]]) {
            if (in[u] > in[v]) swap(u, v), swap(l, r);
            if (head[u] == head[v]) break;
            l = g(f(in[head[v]], in[v] + 1), l);
        }
        return (s(g(f(in[u] + edge, in[v] + 1), l), r));
    }

    template<typename E, typename F, typename G>
    E query(int u, int v, const E &ti, const F &f, const G &g, bool edge = false) {
        return (query(u, v, ti, f, g, g, edge));
    }

    template<typename G>
    void update(int u, int v, const G &g, bool edge = false) {
        for (;; v = par[head[v]]) {
            if (in[u] > in[v]) swap(u, v);
            if (head[u] == head[v]) break;
            g(in[head[v]], in[v] + 1);
        }
        g(in[u] + edge, in[v] + 1);
    }

    // (parent, child)
    vector<pair<int, int> > compress(vector<int> &remark) {
        auto comp = [&](int a, int b) { return (in[a] < in[b]); };
        sort(begin(remark), end(remark), comp);
        remark.erase(unique(begin(remark), end(remark)), end(remark));
        int K = (int) remark.size();
        for (int k = 1; k < K; ++k) remark.emplace_back(lca(remark[k - 1], remark[k]));
        sort(begin(remark), end(remark), comp);
        remark.erase(unique(begin(remark), end(remark)), end(remark));
        vector<pair<int, int> > es;
        vector<int> st;
        for (auto &k : remark) {
            while (!st.empty() && out[st.back()] <= in[k]) st.pop_back();
            if (!st.empty()) es.emplace_back(st.back(), k);
            st.emplace_back(k);
        }
        return (es);
    }

private:
    void dfs_sz(int cur, int p, int d) {
        dep[cur] = d;
        par[cur] = p;
        sz[cur] = 1;
        if (!g[cur].empty() && g[cur][0] == p) swap(g[cur][0], g[cur].back());
        for (auto &to : g[cur]) {
            if (to == p) continue;
            dfs_sz(to, cur, d + 1);
            sz[cur] += sz[to];
            if (sz[g[cur][0]] < sz[to]) swap(g[cur][0], to);
        }
    }

    void dfs_hld(int cur, int p) {
        static int times = 0;
        in[cur] = times++;
        rev[in[cur]] = cur;
        for (auto &to : g[cur]) {
            if (to == p) continue;
            head[to] = (g[cur][0] == to ? head[cur] : to);
            dfs_hld(to, cur);
        }
        out[cur] = times;
    }
};