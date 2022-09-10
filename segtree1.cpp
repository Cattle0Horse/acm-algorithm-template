#include<bits/stdc++.h>
using namespace std;
//线段树无标记单点修改
// the idx is from 0 to n-1
class segtree {
public:
    struct node {
        // don't forget to set default value (used for leaves)
        ... a = ...;

        void apply(int l, int r, ... v) {
            // make v become data in modify
            ...

            /*
            sum += (r - l + 1) * v;
            add += v;
            */
        }
        void init(... v){
            // in build_tree init
            // sum=v;
        }
    };

    node unite(const node &a, const node &b) const {
        node res;
        // res.sum = a.sum + b.sum;
        ...
        return res;
    }

    // about x: left son is x+1 , right son is x+((mid-l+1)<<1) ;
    int n;
    vector<node> tree;
    inline void push_up(int x, int z) { tree[x] = unite(tree[x + 1], tree[z]); }
    void build(int x, int l, int r) {
        if (l == r) {
            return;
        }
        int y = (l + r) >> 1;
        int z = x + ((y - l + 1) << 1);
        build(x + 1, l, y);
        build(z, y + 1, r);
        push_up(x, z);
    }

    template <typename M>
    void build(int x, int l, int r, const vector<M> &v) {
        if (l == r) {
            tree[x].init(v[l]);
            return;
        }
        int y = (l + r) >> 1;
        int z = x + ((y - l + 1) << 1);
        build(x + 1, l, y, v);
        build(z, y + 1, r, v);
        push_up(x, z);
    }

    node get(int x, int l, int r, int ll, int rr) {
        if (ll <= l && r <= rr) {
            return tree[x];
        }
        int y = (l + r) >> 1;
        int z = x + ((y - l + 1) << 1);
        node res{};
        if (rr <= y)
            res = get(x + 1, l, y, ll, rr);
        else {
            if (ll > y)
                res = get(z, y + 1, r, ll, rr);
            else
                res = unite(get(x + 1, l, y, ll, rr), get(z, y + 1, r, ll, rr));
        }
        push_up(x, z);
        return res;
    }

    template <typename M>
    void modify(int x, int l, int r, int ll, int rr, const M & v) {
        if (ll <= l && r <= rr) {
            tree[x].apply(l, r, v);
            return;
        }
        int y = (l + r) >> 1;
        int z = x + ((y - l + 1) << 1);
        if (ll <= y) modify(x + 1, l, y, ll, rr, v);
        if (rr > y) modify(z, y + 1, r, ll, rr, v);
        push_up(x, z);
    }

    segtree(int _n) : n(_n) {
        assert(n > 0);
        tree.resize(2 * n - 1);
        build(0, 0, n - 1);
    }

    template <typename M>
    segtree(const vector<M> &v) {
        n = v.size();
        assert(n > 0);
        tree.resize(2 * n - 1);
        build(0, 0, n - 1, v);
    }

    node get(int ll, int rr) {
        assert(0 <= ll && ll <= rr && rr <= n - 1);
        return get(0, 0, n - 1, ll, rr);
    }

    node get(int p) {
        assert(0 <= p && p <= n - 1);
        return get(0, 0, n - 1, p, p);
    }

    template <typename M>
    void modify(int ll, int rr, const M & v) {
        assert(0 <= ll && ll <= rr && rr <= n - 1);
        modify(0, 0, n - 1, ll, rr, v);
    }

};  // root's idx is 0 and the begin of vector is also 0;
// don't forget idx is from 0 to n-1 (equal [--x,--y]) when ask;