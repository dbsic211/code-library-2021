struct segtree_rupq { 
    // Range update (Add) point query
    int a[4*MAXN];
    void u(int l,int r,int constl,int constr,int idx,int val){
        if(l<=constl&&constr<=r){
            a[idx]+=val;
            return;
        }
        int mid=(constl+constr)>>1;
        if(mid>=l && r>=constl) u(l,r,constl,mid,2*idx+1,val);
        if(constr>=l && r>=mid+1) u(l,r,mid+1,constr,2*idx+2,val);
    }
    int qu(int l,int r,int tar,int idx){
        if(l==r){
            return a[idx];
        }
        int mid=(l+r)>>1;
        if(tar<=mid) return a[idx]+qu(l,mid,tar,2*idx+1);
        else return a[idx]+qu(mid+1,r,tar,2*idx+2);
    }
    public:
    void update(int l, int r, int v) {
        u(l, r, 0, MAXN-1, 0, v);
    }
    int query(int i) {
        return qu(0, MAXN-1, i, 0);
    }
};
