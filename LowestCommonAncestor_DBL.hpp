struct LowestCommonAncestor{
    int n;
    const vector<vector<int> > g;
    vector<vector<int> > table;
    vector<int> depth;
    int logk;

    LowestCommonAncestor(const vector<vector<int> > &G) : g(G){
        n = g.size();
        logk = 32 - __builtin_clz(g.size());
        table.assign(logk, vector<int>(n, -1));
        depth.assign(n, -1);
        build();
    }

    void build(int s = 0, bool isforest = false){
        if(isforest){
            for(int i = 0; i < n; ++i){
                if(depth[i] == -1){
                    dfs(i, -1, 0);
                }
            }
        }else{
            dfs(s, -1, 0);
        }
        for(int k = 0; k < logk - 1; ++k){
            for(int i = 1; i <= n - 1; ++i){
                if(table[k][i] == -1){
                    table[k + 1][i] = -1;
                }else{
                    table[k + 1][i] = table[k][table[k][i]];
                }
            }
        }
    }

    void dfs(int now, int pre, int dep){
        table[0][now] = pre;
        depth[now] = dep;
        for(const auto& to: g[now]){
            if(to != pre){
                dfs(to, now, dep + 1);
            }
        }
    }

    int query(int u, int v){
        if(depth[u] < depth[v]) swap(u, v);
        for(int k = logk - 1; k >= 0; --k){
            if(depth[u] - depth[v] & 1 << k){
                u = table[k][u];
            }
        }
        if(u == v) return (u);
        for(int k = logk - 1; k >= 0; --k){
            if(table[k][u] != table[k][v]){
                u = table[k][u];
                v = table[k][v];
            }
        }
        return (table[0][u]);
    }

    int dist(int u, int v){
        return (depth[u] + depth[v] - 2 * depth[query(u, v)]);
    }
};