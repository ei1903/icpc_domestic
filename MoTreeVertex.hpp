struct MoTreeVertex {
private:
    vector<vector<int> > g, parent;
    vector<int> vs, in;

    vector<int> left, right, order, lca, dep;
    vector<bool> v;
    int width;
    int nl, nr, ptr;

    void dfs(int idx, int depth, int par){
        in[idx] = (int)vs.size();
        dep[idx] = depth;
        parent[0][idx] = par;
        vs.emplace_back(idx);
        for(auto &to : g[idx]){
            if(to == par) continue;
            dfs(to, depth + 1, idx);
            vs.emplace_back(to);
        }
    }

    int getlca(int u, int v){
        if(dep[u] > dep[v]) swap(u, v);
        for(int k = 0; k < parent.size(); ++k){
            if(((dep[v] - dep[u]) >> k) & 1){
                v = parent[k][v];
            }
        }
        if(u == v) return (u);
        for(int k = (int) parent.size() - 1; k >= 0; --k){
            if(parent[k][u] != parent[k][v]){
                u = parent[k][u];
                v = parent[k][v];
            }
        }
        return (parent[0][u]);
    }

public:
    MoTreeVertex(const vector<vector<int> > &G) : g(G), width((int) sqrt(2 * (int) G.size() - 1)), nl(0), nr(0), ptr(0), in(G.size()), dep(G.size()), v(G.size()){
        const auto lg = (int) (log2(G.size()) + 1);
        parent.resize(lg, vector<int>(G.size()));
        vs.reserve(2 * G.size() - 1);
        dfs(0, 0, -1);
        for(int k = 0; k + 1 < parent.size(); ++k){
            for(int i = 0; i < parent[k].size(); ++i){
                if(parent[k][i] == -1) parent[k + 1][i] = -1;
                else parent[k + 1][i] = parent[k][parent[k][i]];
            }
        }
    }

    void insert(int x, int y){
        if(in[x] > in[y]) swap(x, y);
        left.emplace_back(in[x] + 1);
        right.emplace_back(in[y] + 1);
        lca.emplace_back(getlca(x, y));
    }

    template<typename A, typename D, typename O>
    void run(const A &add, const D &del, const O &out){
        order.resize(left.size());
        iota(begin(order), end(order), 0);
        sort(begin(order), end(order), [&](int a, int b){
            int ablock = left[a] / width, bblock = left[b] / width;
            if(ablock != bblock) return (ablock < bblock);
            if(ablock & 1) return (right[a] < right[b]);
            return (right[a] > right[b]);
        });

        auto distribute = [&](int vertex){
            v[vertex].flip();
            if(v[vertex]) add(vertex);
            else del(vertex);
        };

        for(int i = 0; i < order.size(); ++i){
            if(i > 0) distribute(lca[order[i - 1]]); 
            const auto id = order[i];
            while(nl > left[id]) distribute(vs[--nl]);
            while(nr < right[id]) distribute(vs[nr++]);
            while(nl < left[id]) distribute(vs[nl++]);
            while(nr > right[id]) distribute(vs[--nr]);
            distribute(lca[id]); 
            out(id);
        }
        return;
    }
};