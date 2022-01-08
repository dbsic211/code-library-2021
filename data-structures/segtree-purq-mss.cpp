struct segtree_purq {
    //point update range query version 4
    //Supports:
    //Point update (add)
    //Range sum queries
    //prefix "maximum sum suffix" queries
    struct node {
        long long sum = 0;
        long long mss = 0; 
        long long idx;
    };
    vector<node> a;
    int stok;
    void bu(int l, int r, int idx) {
        if(l == r) {
            a[idx].idx = l;
            return;
        }
        int mid = (l + r) >> 1;
        bu(l, mid, 2*idx+1);
        bu(mid+1, r, 2*idx+2);
        a[idx].idx = a[2*idx+1].idx;
    }
    void u(int l, int r, int tar, int idx, long long val) {
        if(l == r) {
            a[idx].sum += val;
            a[idx].mss = max(0ll, a[idx].sum);
            a[idx].idx = (a[idx].sum >= 0 ? l : -1);
            return;
        }
        int mid = (l + r) >> 1;
        if(tar <= mid) u(l, mid, tar, 2*idx+1, val);
        else u(mid+1, r, tar, 2*idx+2, val);
        a[idx].sum = a[2*idx+1].sum + a[2*idx+2].sum;
        a[idx].mss = max(a[2*idx+2].mss, a[2*idx+1].mss + a[2*idx+2].sum);
        a[idx].idx = (a[2*idx+1].mss + a[2*idx+2].sum > a[2*idx+2].mss ?
                      a[2*idx+1].idx : a[2*idx+2].idx);
    }
    long long qu1(int l, int r, int constl, int constr, int idx) {
        if(l <= constl && constr <= r) return a[idx].sum;
        int mid = (constl + constr) >> 1;
        if(mid < l || r < constl) {
            return qu1(l, r, mid+1, constr, 2*idx+2);
        }
        else if(constr < l || r < mid+1) {
            return qu1(l, r, constl, mid, 2*idx+1);
        }
        else {
            return qu1(l, r, constl, mid, 2*idx+1) + qu1(l, r, mid+1, constr, 2*idx+2);
        }
    }
    pair<pair<long long, int>, long long> qu2(int r, int constl, int constr, int idx) {
        if(constr <= r) {
            return {{a[idx].mss, a[idx].idx}, a[idx].sum};
        }
        int mid = (constr + constl) >> 1;
        if(r < constl) return qu2(r, mid+1, constr, 2*idx+2);
        else if(r < mid+1) return qu2(r, constl, mid, 2*idx+1);
        else {
            pair<pair<long long, int>, long long> rel = qu2(r, constl, mid, 2*idx+1);
            pair<pair<long long, int>, long long> rer = qu2(r, mid+1, constr, 2*idx+2);
            pair<pair<long long, int>, long long> res;
            if(rer.second + rel.first.first > rer.first.first) {
                res.first.first = rer.second + rel.first.first;
                res.first.second = rel.first.second;
            }
            else {
                res.first.first = rer.first.first;
                res.first.second = rer.first.second;
            }
            res.second = rel.second + rer.second;
            return res;
        }
    }
    public:
    void resize(int k) {
        stok = k;
        a.resize(4*k + 10);
        bu(1, stok, 0);
    }
    void update(int i, long long v) {
        u(1, stok, i, 0, v);
    }
    long long query_sum(int l, int r) {
        return qu1(l, r, 1, stok, 0);
    }
    long long query_mss(int r) {
        return qu2(r, 1, stok, 0).first.first;
    }
    long long query_mss_index(int r) {
        return qu2(r, 1, stok, 0).first.second;
    }
};
