struct UnionFind{
    int n;
    vector<int> data;

    UnionFind(int sz) : n(sz), data(sz, -1){}

    bool unite(int x, int y){
        x = find(x), y = find(y);
        if(x == y) return (false);
        if(data[x] > data[y]) swap(x, y);
        data[x] += data[y];
        data[y] = x;
        return (true);
    }

    int find(int k){
        if(data[k] < 0) return (k);
        return (data[k] = find(data[k]));
    }

    int size(int k){
        return (-data[find(k)]);
    }

    bool same(int x, int y){
        return (find(x) == find(y));
    }

    vector<vector<int> > groups(){
        vector<int> leader_buf(n), group_size(n);
        for(int i = 0; i < n; ++i){
            leader_buf[i] = find(i);
            group_size[leader_buf[i]]++;
        }
        vector<vector<int> > res(n);
        for(int i = 0; i < n; ++i){
            res[i].reserve(group_size[i]);
        }
        for(int i = 0; i < n; ++i){
            res[leader_buf[i]].emplace_back(i);
        }
        res.erase(
            remove_if(res.begin(), res.end(),
                      [&](const vector<int>& v){ return (v.empty()); }),
            res.end());
        return (res);
    }
};