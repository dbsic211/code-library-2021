//Regular Codeforces Template
//Carries pbds, custom_hash, bigmod, modinv, factorials, nCr up to MAXN, 
//dsu, random number generator, sum of digits of integers, binary addition and subtraction
//With ios::sync_with_stdio(0); cin.tie(0); and #pragma GCC optimize("Ofast")
//MAXN = 3e5 + 10, MOD = 1e9 + 7 by default
//int is defined as long long here, use int32_t or signed for real int

#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
mt19937_64 rng((int)std::chrono::steady_clock::now().time_since_epoch().count());
const int MAXN = 3e5 + 10;
const int MOD = 1e9 + 7;
#define int long long

int rnd(int x, int y) { // random number generator
    int u= uniform_int_distribution<int>(x, y)(rng); return u;
}

void solve(int tc) {
    
}
int32_t main(){
    ios::sync_with_stdio(0); cin.tie(0);
    int t = 1; cin >> t;
    for(int i=1; i<=t; i++) solve(i);
}
