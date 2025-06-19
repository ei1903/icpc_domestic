pair<long long, long long> crt(const vector<long long> &b, const vector<long long> &m) {
    long long r = 0, M = 1;
    for (int i = 0; i < b.size(); ++i) {
        long long p, q;
        long long d = extgcd(M, m[i], p, q);
        if ((b[i] - r) % d != 0) return make_pair(0, -1);
        long long tmp = (b[i] - r) / d * p % (m[i] / d);
        r += M * tmp;
        M *= m[i] / d;
    }
    return make_pair((r % M + M) % M, M);
}
