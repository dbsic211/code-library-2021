//lcp[i]: longest common prefix between the suffix in (i-1)-th position in suffix array
//                                  and the suffix in i-th position in suffix array

//lcp is only initialized starting from index 1

//Use query(l+1, r) for l-th position to r-th position queries
int st[16][MAXN];
int query(int l, int r) {
    int k = 32 - __builtin_clz(r-l+1) - 1;
    return min(st[k][l], st[k][r-(1<<k)+1]);
}
void solve(int tc) {
    int n; cin >> n;
    string s; cin >> s;
    s += "$";
    n = s.size();
    int l = log2(n-1) + 1;
    pair<char, int> p[n];
    for(int i=0; i<n; i++) {
        p[i] = {s[i], i};
    }
    sort(p, p+n);
    pair<pair<int, int>, int> suf[n];
    for(int i=0; i<n; i++){
        if(i == 0) suf[i].first.first = 0;
        else if(p[i].first != p[i-1].first) suf[i].first.first = suf[i-1].first.first + 1;
        else suf[i].first.first = suf[i-1].first.first;
        suf[i].second = p[i].second;
    }
    int pos[n];
    for(int i=0; i<l; i++){
        for(int j=0; j<n; j++){
            pos[suf[j].second] = j;
        }
        for(int j=0; j<n; j++){
            suf[j].first.second = suf[pos[(suf[j].second + (1<<i)) % n]].first.first;
        }
        //radix sort
        int cnt[n], pos[n]; pair<pair<int,int>,int> res[n];
        for(int j=0; j<n; j++) cnt[j] = 0;
        for(int j=0; j<n; j++) cnt[suf[j].first.second]++;
        pos[0] = 0;
        for(int j=1; j<n; j++) pos[j] = pos[j-1] + cnt[j-1];
        for(int j=0; j<n; j++){
            res[pos[suf[j].first.second]] = suf[j];
            pos[suf[j].first.second]++;
        }
        for(int j=0; j<n; j++) suf[j] = res[j];
        for(int j=0; j<n; j++) cnt[j] = 0;
        for(int j=0; j<n; j++) cnt[suf[j].first.first]++;
        pos[0] = 0;
        for(int j=1; j<n; j++) pos[j] = pos[j-1] + cnt[j-1];
        for(int j=0; j<n; j++){
            res[pos[suf[j].first.first]] = suf[j];
            pos[suf[j].first.first]++;
        }
        for(int j=0; j<n; j++) suf[j] = res[j];
        int hlp[n];
        for(int j=0; j<n; j++){
            if(j == 0) hlp[j] = 0;
            else if(suf[j].first != suf[j-1].first) hlp[j] = hlp[j-1] + 1;
            else hlp[j] = hlp[j-1];
        }
        for(int j=0; j<n; j++){
            suf[j].first = {hlp[j], 0};
        }
    }
    for(int i=0; i<n; i++) pos[suf[i].second] = i;
    int lcp[n];
    int k = 0;
    for(int i=0; i<n-1; i++){
        while(s[i + k] == s[suf[pos[i] - 1].second + k]) k++;
        lcp[pos[i]] = k;
        k = max(k-1, 0);
    }
    for(int i=1; i<n; i++) st[0][i] = lcp[i];
    for(int i=1; i<16; i++) {
        for(int j=1; j<n; j++) {
            if(j+(1<<i)-1<n) {
                st[i][j] = min(st[i-1][j], st[i-1][j+(1<<(i-1))]);
            }
        }
    }
}
