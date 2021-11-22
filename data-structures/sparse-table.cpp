//Sparse table template along with efficient c++ log2.
//MAXN must be defined beforehand. If MAXN >= 2^20 when first dimension should increase.

int fastlog(int x) {
    return 32 - __builtin_clz(x) - 1;
}
long long st[20][MAXN];

long long op(long long x, long long y) {
    return max(x, y);
}

long long query(int l, int r) {
    int k = fastlog(r-l+1);
    return op(st[k][l], st[k][r-(1<<k)+1]);
}

void build(int n, long long a[]) {
    for(int i=1; i<=n; i++) st[0][i] = a[i];
    for(int i=1; i<20; i++) {
        for(int j=1; j<=n; j++) {
            if(j + (1<<i) - 1 <= n) {
                st[i][j] = op(st[i-1][j], st[i-1][j+(1<<(i-1))]);
            }
        }
    }
}
