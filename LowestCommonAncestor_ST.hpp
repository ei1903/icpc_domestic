struct LowestCommonAncestor{
    typedef vector<vector<int> > Graph;

    int n;
    const Graph graph;
    vector<int> depth, idx, first_pos;
    SparseTable<int> st;

    LowestCommonAncestor(const Graph &G) : graph(G){
        n = graph.size();
        first_pos.resize(n, 1 << 30);
        build();
    }

    void build(int s = 0){
        dfs(s, -1, 0);
        st.build(depth);
        return;
    }

    void dfs(int cur, int par, int dep){
        first_pos[cur] = idx.size();
        depth.emplace_back(dep);
        idx.emplace_back(cur);
        for(const auto &e: graph[cur]){
            if(e != par){
                dfs(e, cur, dep + 1);
                depth.emplace_back(dep);
                idx.emplace_back(cur);
            }
        }
        return;
    }

    inline int query(int u, int v) const{
        u = first_pos[u];
        v = first_pos[v];
        if(u > v) swap(u, v);
        return (idx[st.query_idx(u, v + 1)]);
    }

    int dist(int v){
        return (depth[first_pos[v]]);
    }

    int dist(int u, int v){
        return (depth[first_pos[u]] + depth[first_pos[v]] - 2 * depth[first_pos[query(u, v)]]);
    }
};