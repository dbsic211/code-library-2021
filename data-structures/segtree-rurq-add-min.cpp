//MAXN = 2e5 + 10
//Range addition update
//Range minimum query
//Everything is initially 0

struct segtree_rurq { 
    // Range update range query, standard form (addition/minimum)
    //No lazy propagation
    struct node {
        long long upd = 0;
        long long ans = 0;
    } a[4*MAXN];
    long long mod = 0;
    //To be changed
    long long upd_op(long long val1, long long val2) {
        return val1 + val2;
    }
    long long qry_op(long long val1, long long val2) {
        return min(val1, val2);
    }
    //To be remained unchanged
    void u(int l, int r, int constl, int constr, int idx, long long val) {
        if(l <= constl && constr <= r) {
            a[idx].upd = upd_op(a[idx].upd, val);
            a[idx].ans = upd_op(a[idx].ans, val);
            if(mod) {
                a[idx].upd %= mod;
                a[idx].ans %= mod;
            }
            return;
        }
        int mid = (constl+constr) >> 1;
        if(mid<l || r<constl) u(l, r, mid+1, constr, 2*idx+2, val);
        else if(constr<l || r<mid+1) u(l, r, constl, mid, 2*idx+1, val);
        else {
            u(l, r, constl, mid, 2*idx+1, val);
            u(l, r, mid+1, constr, 2*idx+2, val);
        }
        a[idx].ans = upd_op(qry_op(a[2*idx+1].ans, a[2*idx+2].ans), a[idx].upd);
    }
    long long qu(int l, int r, int constl, int constr, int idx) {
        if(l <= constl && constr <= r) return a[idx].ans;
        int mid = (constl+constr) >> 1;
        long long ret;
        if(mid<l || r<constl) {
            ret = upd_op(qu(l, r, mid+1, constr, 2*idx+2), a[idx].upd);
        }
        else if(constr<l || r<mid+1) {
            ret = upd_op(qu(l, r, constl, mid, 2*idx+1), a[idx].upd);
        }
        else {
            ret = upd_op(qry_op(qu(l, r, constl, mid, 2*idx+1), qu(l, r, mid+1, constr, 2*idx+2)), a[idx].upd);
        }
        if(mod) ret %= mod;
        return ret;
    }
    public:
    void set_mod(long long x) {
        mod = x;
    }
    void update(int l, int r, long long v) {
        u(l, r, 0, MAXN-1, 0, v);
    }
    long long query(int l, int r) {
        return qu(l, r, 0, MAXN-1, 0);
    }
};
