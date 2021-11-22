//inv requires bm
//nCr requires inv and precomp
//MAXN and MOD must be defined
//MOD must be defined as long long

long long bm(long long b, long long p) { // bigmod
    if(p==0) return 1;
    long long r = bm(b, p/2);
    if(p&1) return (((r*r) % MOD) * b) % MOD;
    return (r*r) % MOD;
}
long long inv(long long b) { // modinv
    return bm(b, MOD-2);
}
long long f[MAXN];
long long nCr(int n, int r) { // nCr main function, requires precomputation function
    long long ans = f[n]; ans *= inv(f[r]); ans %= MOD;
    ans *= inv(f[n-r]); ans %= MOD; return ans;
}

void precomp() { // factorials for nCr, function MUST BE CALLED
    f[0] = 1;
    for(int i=1; i<MAXN; i++) f[i] = (f[i-1] * i) % MOD;
}
