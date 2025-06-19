class FastPrimeFactorization {
private:
    vector<int> min_factor;

public:
    FastPrimeFactorization() = default;

    FastPrimeFactorization(int n) : min_factor(n + 1) {
        iota(min_factor.begin(), min_factor.end(), 0);

        for(int i = 2; i * i <= n; ++i){
            if(min_factor[i] < i) continue;
            for(int j = i * i; j <= n; j += i){
                if(min_factor[j] == j) min_factor[j] = i;
            }
        }
    }

    map<int, int> query(int n) {
        map<int, int> ret;
        while(n > 1){
            ret[min_factor[n]]++;
            n /= min_factor[n];
        }
        return (ret);
    }
};