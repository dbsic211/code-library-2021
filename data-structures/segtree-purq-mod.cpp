struct segtree_purq {
    struct node {
        long long mx = 0;
        long long sum = 0;
    } a[4*MAXN];

    void u1(int l, int r, int tar, int idx, long long val) {
        if(l == r) {
            a[idx].mx = a[idx].sum = val;
            return;
        }
        int mid = (l+r) >> 1;
        if(tar <= mid) u1(l, mid, tar, 2*idx+1, val);
        else u1(mid+1, r, tar, 2*idx+2, val);
        a[idx].mx = max(a[2*idx+1].mx, a[2*idx+2].mx);
        a[idx].sum = a[2*idx+1].sum + a[2*idx+2].sum;
    }

    void u2(int l, int r, int constl, int constr, int idx, long long val) {
        if(l <= constl && constr <= r) {
            if(a[idx].mx < val) {
                return;
            }
            if(constl == constr) {
                a[idx].mx %= val;
                a[idx].sum %= val;
                return;
            }
            int mid = (constl + constr) >> 1;
            u2(l, r, constl, mid, 2*idx+1, val);
            u2(l, r, mid+1, constr, 2*idx+2, val);
            a[idx].mx = max(a[2*idx+1].mx, a[2*idx+2].mx);
            a[idx].sum = a[2*idx+1].sum + a[2*idx+2].sum;
            return;
        }
        int mid = (constl + constr) >> 1;
        if(mid < l || r < constl) u2(l, r, mid+1, constr, 2*idx+2, val);
        else if(constr < l || r < mid+1) u2(l, r, constl, mid, 2*idx+1, val);
        else {
            u2(l, r, constl, mid, 2*idx+1, val);
            u2(l, r, mid+1, constr, 2*idx+2, val);
        }
        a[idx].mx = max(a[2*idx+1].mx, a[2*idx+2].mx);
        a[idx].sum = a[2*idx+1].sum + a[2*idx+2].sum;
    }

    long long qu(int l, int r, int constl, int constr, int idx) {
        if(l <= constl && constr <= r) return a[idx].sum;
        int mid = (constl + constr) >> 1;
        if(mid < l || r < constl) return qu(l, r, mid+1, constr, 2*idx+2);
        if(constr < l || r < mid+1) return qu(l, r, constl, mid, 2*idx+1);
        return qu(l, r, constl, mid, 2*idx+1) + qu(l, r, mid+1, constr, 2*idx+2);
    }
    public:
    void point_set(int i, long long v) {
        u1(0, MAXN-1, i, 0, v);
    }
    void range_mod(int l, int r, long long v) {
        u2(l, r, 0, MAXN-1, 0, v);
    }
    long long range_sum(int l, int r) {
        return qu(l, r, 0, MAXN-1, 0);
    }
};
