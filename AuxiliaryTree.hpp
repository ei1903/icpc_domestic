struct AuxiliaryTree {
    typedef vector<vector<int> > Graph;

    const Graph graph;
    LowestCommonAncestor lca;

    int n, cnt;
    vector<int> pre_order, vec;

    AuxiliaryTree(const Graph &G) : lca(G), graph(G) {
        n = graph.size();
        pre_order.resize(n);
        cnt = 0;
        dfs(0, -1);
    }

    void dfs(int cur, int par){
        pre_order[cur] = cnt++;
        for(const auto &e: graph[cur]){
            if(par != e){
                dfs(e, cur);
            }
        }
        return;
    }

    // (parent, child)
    vector<pair<int, int> > query(vector<int> &v){
        vector<pair<int, int> > ret;
        int siz = v.size();
        sort(v.begin(), v.end(), [&](int a, int b){ return (pre_order[a] < pre_order[b]); });
        for(int i = 0; i < siz - 1; ++i){
            v.emplace_back(lca.query(v[i], v[i + 1]));
        }
        sort(v.begin(), v.end(), [&](int a, int b){ return (pre_order[a] < pre_order[b]); });
        v.erase(unique(v.begin(), v.end()), v.end());
        siz = v.size();
        for(int i = 0; i < siz - 1; ++i){
            int x = lca.query(v[i], v[i + 1]);
            if(x == v[i]){
                ret.emplace_back(v[i], v[i + 1]);
            }else{
                ret.emplace_back(x, v[i + 1]);
            }
        }
        return (ret);
    }
};