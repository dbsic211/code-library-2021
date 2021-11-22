//Segment tree template, point update range query

//The default for update is assign (:=) operation. Can be modified to +=, ^=, ...
//The default for query is sum (+=) operation. Can be modified to *=, ^=, ... or other operations
struct segtree_purq {
    long long a[4*MAXN] = {};
    void upd_op(int idx, long long val) {
        a[idx] = val;            //Assign operation
    }    
    long long query_op(long long val1, long long val2) {
        return val1 + val2;      //Add operation
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
        a[idx] = query_op(a[2*idx+1], a[2*idx+2]);
    }
    long long qu(int l, int r, int constl, int constr, int idx) {
        if(l <= constl && constr <= r) return a[idx];
        int mid = (constl+constr) >> 1;
        if(mid < l || r < constl) return qu(l, r, mid+1, constr, 2*idx+2);
        if(constr < l || r < mid+1) return qu(l, r, constl, mid, 2*idx+1);
        return query_op(qu(l, r, constl, mid, 2*idx+1), qu(l, r, mid+1, constr, 2*idx+2));
    }
    public:
    //Convenience functions
    void update(int i, int v) {
        u(0, MAXN-1, i, 0, v);
    }
    long long query(int l, int r) {
        return qu(l, r, 0, MAXN-1, 0);
    }
};
