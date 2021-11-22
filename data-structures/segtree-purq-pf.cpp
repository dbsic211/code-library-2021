//Property Frequency Segtree (segtree-purq-pf)
//Segtree supporting minimum and number of minimums
//General form: [property] and frequency of [property] in range
//Assume the update operation is :=
//Assume the query operatiion is min

//Property must only apply to one index only (e.g. minimum single element in range)
//All elements are automatically set to 0 at the start of segtree

struct segtree_purq_pf {
    bool init = 0;
    pair<long long, int> a[4*MAXN];
    void upd_op(int idx, long long val) {
        a[idx] = {val, 1};            //Assign operation
    }    
    long long query_op(long long val1, long long val2) {
        return min(val1, val2);       //Min operation
    }
    //To be remained unchanged by default
    void u(int l, int r, int tar, int idx, long long val) {
        if(l == r) {
            upd_op(idx, val);
            return;
        }
        int mid = (l+r) >> 1;
        if(tar <= mid) u(l, mid, tar, 2*idx+1, val);
        else u(mid+1, r, tar, 2*idx+2, val);
        long long res = query_op(a[2*idx+1].first, a[2*idx+2].first);
        if(res != a[2*idx+1].first) {
            a[idx] = a[2*idx+2];
        }
        else if(res != a[2*idx+2].first) {
            a[idx] = a[2*idx+1];
        }
        else {
            a[idx] = {a[2*idx+1].first, a[2*idx+1].second + a[2*idx+2].second};
        }
    }
    pair<long long, int> qu(int l, int r, int constl, int constr, int idx) {
        if(l <= constl && constr <= r) return a[idx];
        int mid = (constl+constr) >> 1;
        if(mid < l || r < constl) return qu(l, r, mid+1, constr, 2*idx+2);
        if(constr < l || r < mid+1) return qu(l, r, constl, mid, 2*idx+1);
        pair<long long, int> lhs = qu(l, r, constl, mid, 2*idx+1);
        pair<long long, int> rhs = qu(l, r, mid+1, constr, 2*idx+2);
        long long res = query_op(lhs.first, rhs.first);
        if(res != lhs.first) {
            return rhs;
        }
        else if(res != rhs.first) {
            return lhs;
        }
        else {
            return {lhs.first, lhs.second + rhs.second};
        }
    }
    public:
    //Convenience functions
    void update(int i, int v) {
        if(!init) {
            init = 1;
            for(int i=0; i<MAXN; i++) u(0, MAXN-1, i, 0, 0);
        }
        u(0, MAXN-1, i, 0, v);
    }
    pair<long long, int> query(int l, int r) {
        if(!init) {
            init = 1;
            for(int i=0; i<MAXN; i++) u(0, MAXN-1, i, 0, 0);
        }
        return qu(l, r, 0, MAXN-1, 0);
    }
};
