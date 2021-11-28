//To be prepared: MAXN, adj[MAXN]

int dep[MAXN];
pair<int, int> p[20][2 * MAXN]; // beware of memory usage here
vector<int> e; // euler tour array
void dfs(int node, int prev, int d) {
    if(prev == -1) {
        cur = 0; // make sure cur is reset
        e.clear();
    }
    dep[node] = d;
    e.push_back(node);
    
    for(int x : adj[node]) {
        if(x != prev) {
            dfs(x, node, d + 1);
            e.push_back(node);
        }
    }
}

int l[MAXN], r[MAXN]; // leftmost and rightmost occurrence of node i in euler tour
int lca(int x, int y) { // lca's index between node x and node y. Modify line 33 to make this return the lca's depth instead.
    int m1 = min(l[x], l[y]);
    int m2 = max(r[x], r[y]);
    int k = 32 - __builtin_clz(m2-m1+1) - 1;
    pair<int, int> q = min(p[k][m1], p[k][m2 - (1<<k) + 1]);
    return q.second;
}

int dist(int x, int y) { // Distance between nodes x and y
    return dep[x] + dep[y] - 2 * dep[lca(x, y)];
}

void solve(int tc) {
    //dfs required
    //start of template
    for(int i=0; i<e.size(); i++) {
        p[0][i] = {dep[e[i]], e[i]};
    }
    for(int i=1; i<20; i++) {
        for(int j=0; j<e.size(); j++) {
            if(j + (1<<i) - 1 >= e.size()) continue;
            p[i][j] = min(p[i-1][j], p[i-1][j+(1<<(i-1))]);
        }
    }
    for(int i=e.size()-1; i>=0; i--) l[e[i]] = i;
    for(int i=0; i<e.size(); i++) r[e[i]] = i;
    //end, function lca and dist can be used starting here
    
}
