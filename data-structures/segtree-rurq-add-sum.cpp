//const int MAXN = 2e5 + 10;

struct segtree_rurq { 
    // Range update range query, standard form 2 (addition/sum)
    struct node {
        long long upd = 0;
        long long ans = 0;
    } a[4*MAXN];
    long long mod = 0;
    //To be remained unchanged
    void u(int l, int r, int constl, int constr, int idx, long long val) {
        if(l <= constl && constr <= r) {
            a[idx].upd += val;
            a[idx].ans += val * (constr-constl + 1);
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
        a[idx].ans = a[idx].upd * (constr-constl+1) + a[2*idx+1].ans + a[2*idx+2].ans;
        if(mod) a[idx].ans %= mod;
    }
    long long qu(int l, int r, int constl, int constr, int idx) {
        if(l <= constl && constr <= r) return a[idx].ans;
        int mid = (constl+constr) >> 1;
        long long ret;
        int lb = max(l, constl);
        int rb = min(r, constr);
        if(mid<l || r<constl) { 
            ret = a[idx].upd * (rb - lb + 1) + qu(l, r, mid+1, constr, 2*idx+2);
        }
        else if(constr<l || r<mid+1) {
            ret = a[idx].upd * (rb - lb + 1) + qu(l, r, constl, mid, 2*idx+1), a[idx].upd;
        }
        else {
            ret = a[idx].upd * (rb - lb + 1) + qu(l, r, constl, mid, 2*idx+1) + qu(l, r, mid+1, constr, 2*idx+2);
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
