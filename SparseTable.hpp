template<typename T>
struct SparseTable{
    vector<T> a;
    vector<vector<int> > table;
    vector<int> log_table;

    SparseTable(){};

    SparseTable(vector<T> &v) : a(v){
        int log_n = 0;
        int siz = v.size();

        while((1 << log_n) <= siz) ++log_n;
        int n = 1 << log_n;

        table.resize(n, vector<int>(log_n));
        a.resize(n);
        log_table.resize(siz + 1);

        for(int i = 0; i < siz; ++i){
            table[i][0] = i;
        }

        for(int k = 1; k < log_n; ++k){
            for(int i = 0; i + (1 << k) <= n; ++i){
                if(a[table[i][k - 1]] < a[table[i + (1 << k - 1)][k - 1]]){
                    table[i][k] = table[i][k - 1];
                }else{
                    table[i][k] = table[i + (1 << k - 1)][k - 1];
                }
            }
        }

        for(int i = 2; i < siz + 1; ++i){
            log_table[i] = log_table[i >> 1] + 1;
        }
    }

    void build(vector<T> &v){
        a = v;
        int log_n = 0;
        int siz = v.size();

        while((1 << log_n) <= siz) ++log_n;
        int n = 1 << log_n;

        table.resize(n, vector<int>(log_n));
        a.resize(n);
        log_table.resize(siz + 1);

        for(int i = 0; i < siz; ++i){
            table[i][0] = i;
        }

        for(int k = 1; k < log_n; ++k){
            for(int i = 0; i + (1 << k) <= n; ++i){
                if(a[table[i][k - 1]] < a[table[i + (1 << k - 1)][k - 1]]){
                    table[i][k] = table[i][k - 1];
                }else{
                    table[i][k] = table[i + (1 << k - 1)][k - 1];
                }
            }
        }

        for(int i = 2; i < siz + 1; ++i){
            log_table[i] = log_table[i >> 1] + 1;
        }
    }

    inline int query_idx(int l, int r) const{
        int log_n = log_table[r - l];
        if(a[table[l][log_n]] < a[table[r - (1 << log_n)][log_n]]){
            return (table[l][log_n]);
        }else{
            return (table[r - (1 << log_n)][log_n]);
        }
    }

    inline T query_val(int l, int r) const{
        return (a[query_idx(l, r)]);
    }
};