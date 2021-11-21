//inv requires bm
//nCr requires inv and precomp
//MAXN and MOD must be defined

int bm(int b, int p) { // bigmod
    if(p==0) return 1;
    int r = bm(b, p/2);
    if(p&1) return (((r*r) % MOD) * b) % MOD;
    return (r*r) % MOD;
}
int inv(int b) { // modinv
    return bm(b, MOD-2);
}
int f[MAXN];
int nCr(int n, int r) { // nCr main function, requires precomputation function
    int ans = f[n]; ans *= inv(f[r]); ans %= MOD;
    ans *= inv(f[n-r]); ans %= MOD; return ans;
}

void precomp() { // factorials for nCr, function MUST BE CALLED
    f[0] = 1;
    for(int i=1; i<MAXN; i++) f[i] = (f[i-1] * i) % MOD;
}
