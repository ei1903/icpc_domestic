struct UnionFindUndo {
    vector<int> data;
    vector<pair<int, int> > history;

    UnionFindUndo(int sz) {
        data.assign(sz, -1);
    }

    bool unite(int x, int y) {
        x = find(x), y = find(y);
        history.emplace_back(x, data[x]);
        history.emplace_back(y, data[y]);
        if(x == y) return (false);
        if(data[x] > data[y]) swap(x, y);
        data[x] += data[y];
        data[y] = x;
        return (true);
    }

    int find(int k) {
        if(data[k] < 0) return (k);
        return (find(data[k]));
    }

    int size(int k) {
        return (-data[find(k)]);
    }

    bool same(int u, int v) {
        return (find(u) == find(v));
    }

    void undo() {
        data[history.back().first] = history.back().second;
        history.pop_back();
        data[history.back().first] = history.back().second;
        history.pop_back();
    }

    void snapshot() {
        while(history.size()) history.pop_back();
    }

    void rollback() {
        while(history.size()) undo();
    }
};