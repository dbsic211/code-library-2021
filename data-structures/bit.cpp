struct bit {
    long long a[MAXN];
    public:
    void add(int x, long long v) {
        for(;x<MAXN;x+=x&-x) {
            a[x] += v;
        }
    }
    long long sum(int x) {
        long long ans = 0;
        for(;x;x-=x&-x) ans += a[x];
        return ans;
    }
};
