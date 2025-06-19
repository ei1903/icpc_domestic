template <class A, class EL, class ER, class C, class O>
void sliding_window_algorithm(int n, const A &add, const EL &erase_left, const ER &erase_right, const C &check, const O &out) {
    int r = 0;
    for (int l = 0; l < n; ++l) {
        while (r < n) {
            if (add(r); check()) r++;
            else { erase_right(r); break; }
        }
        out(l, r);
        erase_left(l);
    }
}

template <class A, class E, class C, class O>
void sliding_window_algorithm(int n, const A &add, const E &erase, const C &check, const O &out) {
    sliding_window_algorithm(n, add, erase, erase, check, out);
}