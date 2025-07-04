template <class Iterator>
auto run_length_encoding(Iterator begin, Iterator end) {
    using value_type = typename iterator_traits<Iterator>::value_type;

    vector<pair<value_type, intmax_t>> ret;
    ret.reserve(distance(begin, end));

    intmax_t cnt = 1;
    Iterator prev_begin;
    for (prev_begin = begin++; begin != end; prev_begin = begin++) {
        if (*prev_begin == *begin) {
            cnt++;
        } else {
            ret.emplace_back(*prev_begin, cnt);
            cnt = 1;
        }
    }
    ret.emplace_back(*prev_begin, cnt);

    return ret;
}
