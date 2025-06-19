struct RangeSet {
private:
    set<pair<long long, long long>> s;

public:
    RangeSet() {
        s.emplace(LLONG_MIN, LLONG_MIN);
        s.emplace(LLONG_MAX, LLONG_MAX);
    }

    // [l, u] は被覆されているか
    bool covered(long long l, long long u) const {
        assert(l <= u);
        auto it = prev(s.lower_bound(make_pair(l + 1, l + 1)));
        return it->first <= l && u <= it->second;
    }

    // x は被覆されているか（含まれるか）
    bool covered(long long x) const {
        return covered(x, x);
    }

    // [l, u] が被覆されているならその区間を返す。
    // そうでないなら [LLONG_MIN, LLONG_MIN] を返す。
    auto covered_by(long long l, long long u) const {
        assert(l <= u);
        auto it = prev(s.lower_bound(make_pair(l + 1, l + 1)));
        if (it->first <= l && u <= it->second) return *it;
        return make_pair(LLONG_MIN, LLONG_MIN);
    }

    // x が被覆されている（含まれる）ならその区間を返す。
    // そうでないなら [LLONG_MIN, LLONG_MIN] を返す。
    auto covered_by(long long x) const {
        return covered_by(x, x);
    }

    // [l, u] を追加、要素の増加量を返す。
    long long insert(long long l, long long u) {
        assert(l <= u);
        auto it = prev(s.lower_bound(make_pair(l + 1, l + 1)));
        if (it->first <= l && u <= it->second) return 0;
        long long sum_erased = 0;
        if (it->first <= l && l <= it->second + 1) {
            l = it->first;
            sum_erased += it->second - it->first + 1;
            it = s.erase(it);
        } else {
            it = next(it);
        }
        while (u > it->second) {
            sum_erased += it->second - it->first + 1;
            it = s.erase(it);
        }
        if (it->first - 1 <= u && u <= it->second) {
            sum_erased += it->second - it->first + 1;
            u = it->second;
            s.erase(it);
        }
        s.emplace(l, u);
        return u - l + 1 - sum_erased;
    }

    // x を追加、要素の増加量を返す
    long long insert(long long x) {
        return insert(x, x);
    }

    // [l, r] を削除、要素の減少量を返す
    long long erase(long long l, long long u) {
        assert(l <= u);
        auto it = prev(s.lower_bound(make_pair(l + 1, l + 1)));
        if (it->first <= l && u <= it->second) {
            if (it->first < l) s.emplace(it->first, l - 1);
            if (u < it->second) s.emplace(u + 1, it->second);
            s.erase(it);
            return u - l + 1;
        }
        long long res = 0;
        if (it->first <= l && l <= it->second) {
            res += it->second - l + 1;
            if (it->first < l) s.emplace(it->first, l - 1);
            it = s.erase(it);
        } else {
            it = next(it);
        }
        while (it->second <= u) {
            res += it->second - it->first + 1;
            it = s.erase(it);
        }
        if (it->first <= u && u <= it->second) {
            res += u - it->first + 1;
            if (u < it->second) s.emplace(u + 1, it->second);
            s.erase(it);
        }
        return res;
    }

    // x を削除、要素の減少量を返す
    long long erase(long long x) {
        return erase(x, x);
    }

    // 区間の総数
    size_t size() const {
        return s.size() - 2;
    }

    // x 以上で含まれない最小要素
    long long mex(long long x = 0) const {
        auto it = prev(s.lower_bound(make_pair(x + 1, x + 1)));
        if (it->first <= x && x <= it->second) {
            return it->second + 1;
        } else {
            return x;
        }
    }

    auto data() const {
        auto res = s;
        res.erase(make_pair(LLONG_MIN, LLONG_MIN));
        res.erase(make_pair(LLONG_MAX, LLONG_MAX));
        return res;
    }
};