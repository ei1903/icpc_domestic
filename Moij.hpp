struct Mo {
private:
    int n;
    vector<pair<int, int> > ij;

public:
    Mo(int n) : n(n) {}

    // ([0, i), [0, j))
    void insert(int i, int j){
        ij.emplace_back(i, j);
    }

    template<typename II, typename DI, typename IJ, typename DJ, typename O>
    void run(const II &inc_i, const DI &dec_i, const IJ &inc_j, const DJ &dec_j, const O &out){
        int q = (int) ij.size();
        int bs = n / min<int>(n, sqrt(q));
        vector<int> ord(q);
        iota(ord.begin(), ord.end(), 0);
        sort(ord.begin(), ord.end(), [&](int a, int b){
            int ablock = ij[a].first / bs, bblock = ij[b].first / bs;
            if(ablock != bblock) return (ablock < bblock);
            if(ablock & 1) return (ij[a].second > ij[b].second);
            return (ij[a].second < ij[b].second);
        });
        int i = 0, j = 0;
        for(auto idx : ord){
            while(i < ij[idx].first) inc_i(i++, j);
            while(i > ij[idx].first) dec_i(--i, j);
            while(j < ij[idx].second) inc_j(i, j++);
            while(j > ij[idx].second) dec_j(i, --j);
            out(idx);
        }
    }
};