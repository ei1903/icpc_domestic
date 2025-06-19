struct RollbackMo {
private:
    int n;
    vector<pair<int, int> > lr;

public:
    RollbackMo(int n) : n(n) {}

    void insert(int l, int r){
        lr.emplace_back(l, r);
    }

    template<typename AL, typename AR, typename EL, typename I, typename O>
    void run(const AL &add_left, const AR &add_right, const EL &erase_left, const I &init, const O &out){
        int q = (int) lr.size();
        int bs = n / min<int>(n, sqrt(q));
        vector<int> ord(q);
        iota(ord.begin(), ord.end(), 0);
        sort(ord.begin(), ord.end(), [&](int a, int b){
            int ablock = lr[a].first / bs, bblock = lr[b].first / bs;
            if(ablock != bblock) return (ablock < bblock);
            return (lr[a].second < lr[b].second);
        });
        for (int i = 0, bn = 0; i < q; ++bn) {
            init();
            int r, mid, idx;
            r = mid = bs * (bn + 1);
            while (i < q && lr[idx = ord[i]].first / bs == bn) {
                while (r < lr[idx].second) add_right(r++);
                for (int j = min(mid, lr[idx].second) - 1; j >= lr[idx].first; --j) {
                    add_left(j);
                }
                out(idx);
                for (int j = lr[idx].first; j < min(mid, lr[idx].second); ++j) {
                    erase_left(j);
                }
                i++;
            }
        }
    }

    template<typename A, typename EL, typename I, typename O>
    void run(const A &add, const EL &erase_left, const I &init, const O &out){
        run(add, add, erase_left, init, out);
    }
};