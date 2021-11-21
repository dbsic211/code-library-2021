//MAXN must be defined

int dsu[MAXN]; 
int set_of(int u) {
    if(dsu[u] == u) return u;
    return dsu[u] = set_of(dsu[u]);
}
void union_(int u, int v) {
    dsu[set_of(u)] = set_of(v);
}
