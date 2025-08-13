
template<typename T>
struct Fenwick {
    int n;
    vector<T> bit;

    Fenwick(int n) : n(n) {
        bit.assign(n + 1, 0);
    }

    // add x to index i
    void add(int i, T x) {
        while (i <= n) {
            bit[i] += x;
            i += i & -i;
        }
    }

    // add x to range [l, r]
    void range_add(int l, int r, T x) {
        add(l, x);
        add(r + 1, -x);
    }

    // get value at index i
    T point_query(int i) {
        T res = 0;
        while (i > 0) {
            res += bit[i];
            i -= i & -i;
        }
        return res;
    }
};