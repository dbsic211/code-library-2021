//Everything is initially zero

struct segtree_rurq { 
    // Range update range query, standard form 4 (assignment/sum)
    struct node {
        long long upd = 0;
        long long ans = 0;
        bool exist = 0;
    } a[4*MAXN];
    long long mod = 0;
    //To be remained unchanged
    void u(int l, int r, int constl, int constr, int idx, long long val) {
        if(l <= constl && constr <= r) {
            a[idx].upd = val;
            a[idx].ans = val * (constr-constl+1);
            a[idx].exist = 1;
            if(mod) {
                a[idx].upd %= mod;
                a[idx].ans %= mod;
            }
            return;
        }
        int mid = (constl+constr) >> 1;
        //Lazy propagation
        if(a[idx].exist == 1) {
            a[2*idx+1].upd = a[idx].upd;
            a[2*idx+2].upd = a[idx].upd;
            a[idx].upd = 0;
            a[2*idx+1].exist = 1;
            a[2*idx+2].exist = 1;
            a[idx].exist = 0;
            a[2*idx+1].ans = a[2*idx+1].upd * (mid-constl + 1);
            a[2*idx+2].ans = a[2*idx+2].upd * (constr-mid);
            a[idx].ans = a[2*idx+1].ans + a[2*idx+2].ans;
        }
        
        if(mid<l || r<constl) u(l, r, mid+1, constr, 2*idx+2, val);
        else if(constr<l || r<mid+1) u(l, r, constl, mid, 2*idx+1, val);
        else {
            u(l, r, constl, mid, 2*idx+1, val);
            u(l, r, mid+1, constr, 2*idx+2, val);
        }
        a[idx].ans = a[2*idx+1].ans + a[2*idx+2].ans;
        if(mod) a[idx].ans %= mod;
    }
    long long qu(int l, int r, int constl, int constr, int idx) {
        if(l <= constl && constr <= r) return a[idx].ans;
        int mid = (constl+constr) >> 1;
        long long ret;
        if(a[idx].exist == 1) {
            a[2*idx+1].upd = a[idx].upd;
            a[2*idx+2].upd = a[idx].upd;
            a[idx].upd = 0;
            a[2*idx+1].exist = 1;
            a[2*idx+2].exist = 1;
            a[idx].exist = 0;
            a[2*idx+1].ans = a[2*idx+1].upd * (mid-constl + 1);
            a[2*idx+2].ans = a[2*idx+2].upd * (constr-mid);
            a[idx].ans = a[2*idx+1].ans + a[2*idx+2].ans;
        }
        if(mid<l || r<constl) { 
            ret = qu(l, r, mid+1, constr, 2*idx+2);
        }
        else if(constr<l || r<mid+1) {
            ret = qu(l, r, constl, mid, 2*idx+1);
        }
        else {
            ret = qu(l, r, constl, mid, 2*idx+1) + qu(l, r, mid+1, constr, 2*idx+2);
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
