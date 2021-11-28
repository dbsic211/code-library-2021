//Segment tree beats: version 1 
//range min-with, range sum, range max

//Size is NOT DEFINED please define it yourself by .resize()

//1e6 operations -> 2.5 seconds

struct segtree_beats {
    struct node {
        long long sum = 0;
        long long ma = 0;
        long long se = -1e9;
        int cntma = 0;
        long long upd = -1e9;
    };
    vector<node> a;
    int stok;
    void pushtag(int idx, long long val) {
        if(a[idx].ma <= val) return;
        a[idx].sum -= a[idx].cntma * (a[idx].ma - val);
        a[idx].ma = a[idx].upd = val;
    }
    void pushdown(int idx) {
        if(a[idx].upd == -1e9) return;
        pushtag(2*idx+1, a[idx].upd);
        pushtag(2*idx+2, a[idx].upd);
        a[idx].upd = -1e9;
    }
    void pushup(int idx) {
        a[idx].sum = a[2*idx+1].sum + a[2*idx+2].sum;
        a[idx].ma = max(a[2*idx+1].ma, a[2*idx+2].ma);
        a[idx].se = (
            a[2*idx+1].ma == a[2*idx+2].ma ? 
            max(a[2*idx+1].se, a[2*idx+2].se) : 
            (a[2*idx+1].ma < a[2*idx+2].ma ? 
             max(a[2*idx+1].ma, a[2*idx+2].se) :
             max(a[2*idx+1].se, a[2*idx+2].ma))
        );
        a[idx].cntma = (
            a[idx].ma != a[2*idx+1].ma ? 
            a[2*idx+2].cntma : 
            (a[idx].ma != a[2*idx+2].ma ? 
             a[2*idx+1].cntma : 
             a[2*idx+1].cntma + a[2*idx+2].cntma)
        );
    }
    void build(int l, int r, int idx) {
        a[idx].upd = -1e9;
        if(l == r) {
            a[idx].sum = a[idx].ma = 1e10;
            a[idx].cntma = 1;
            a[idx].se = -1e9;
            return;
        }
        int mid = (l+r) >> 1;
        build(l, mid, 2*idx+1);
        build(mid+1, r, 2*idx+2);
        pushup(idx);
    }
    void u(int l,int r, long long constl, long long constr, int idx, long long val) {
        int mid = (constl + constr) >> 1;
        if(val >= a[idx].ma) return;
        if(l <= constl && constr <= r) {
            if(val > a[idx].se) {
                a[idx].sum -= a[idx].cntma * (a[idx].ma - val);
                a[idx].ma = val;
                a[idx].upd = val;
                return;
            }
            pushdown(idx);
            if(mid < l || r < constl) u(l, r, mid+1, constr, 2*idx+2, val);
            else if(constr < l || r < mid+1) u(l, r, constl, mid, 2*idx+1, val);
            else {
                u(l, r, constl, mid, 2*idx+1, val);
                u(l, r, mid+1, constr, 2*idx+2, val);
            }
            pushup(idx);
            return;
        }
        pushdown(idx);
        if(mid < l || r < constl) u(l, r, mid+1, constr, 2*idx+2, val);
        else if(constr < l || r < mid+1) u(l, r, constl, mid, 2*idx+1, val);
        else {
            u(l, r, constl, mid, 2*idx+1, val);
            u(l, r, mid+1, constr, 2*idx+2, val);
        }
        pushup(idx);
    }
    long long qum(int l, int r, long long constl, long long constr, int idx) {
        if(l <= constl && constr <= r) return a[idx].ma;
        pushdown(idx);
        int mid = (constl+constr) >> 1;
        if(mid < l || r < constl) return qum(l, r, mid+1, constr, 2*idx+2);
        if(constr < l || r < mid+1) return qum(l, r, constl, mid, 2*idx+1);
        return max(
            qum(l, r, constl, mid, 2*idx+1),
            qum(l, r, mid+1, constr, 2*idx+2)
        );
    }
    long long qus(int l, int r, long long constl, long long constr, int idx) {
        if(l <= constl && constr <= r) return a[idx].sum;
        pushdown(idx);
        int mid = (constl+constr) >> 1;
        if(mid < l || r < constl) return qus(l, r, mid+1, constr, 2*idx+2);
        if(constr < l || r < mid+1) return qus(l, r, constl, mid, 2*idx+1);
        return qus(l, r, constl, mid, 2*idx+1) + qus(l, r, mid+1, constr, 2*idx+2);
    }
    bool done = 0;
    public:
    void min_with(int l, int r, long long x) {
        if(!done) {
            build(0, stok, 0);
            done = 1;
        }
        u(l, r, 0, stok, 0, x);
    }
    long long query_max(int l, int r) {
        if(!done) {
            build(0, stok, 0);
            done = 1;
        }
        return qum(l, r, 0, stok, 0);
    }
    long long query_sum(int l, int r) {
        if(!done) {
            build(0, stok, 0);
            done = 1;
        }
        return qus(l, r, 0, stok, 0);
    }
    void resize(int k) {
        a.resize(4*k + 10);
        stok = k;
        if(!done) {
            build(0, stok, 0);
            done = 1;
        }
    }
};
