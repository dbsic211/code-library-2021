#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 10;
const int MOD = 1e9 + 7;
#define int long long
vector<int> adj[MAXN];
int tin[MAXN], tout[MAXN], tim = 0;
map<pair<int, int>, bool> is_bridge;
void dfs(int node) {
  tin[node] = ++tim;
  int mi = 1e9;
  for(int x: adj[node]) {
    if(!vis[x]) {
      dfs(x);
      mi = min(mi, low[x]);
      if(low[x] > tin[node]) {
        is_bridge[{x, node}] = is_bridge[{node, x}] = 1;
      }
    }
  }
  tout[node] = ++tim;
  //Calculating low[node]
  low[node] = tin[node];
  for(int x: adj[node]) {
    if(tin[x] < tin[node] && tout[node] == 0 && tin[x] > 0) {
      low[node] = min(low[node], tin[x]);
    }
  }
  low[node] = min(low[node], mi);
}
int dsu[MAXN];
int set_of(int u) {
  if(dsu[u] == u) return u;
  return dsu[u] = set_of(dsu[u]);
}
void union_(int u, int v) {
  dsu[set_of(u)] = set_of(v);
}
vector<int> adj2[MAXN];
void solve(int tc) {
  int n, m, p;
  cin >> n >> m;
  for(int i=1; i<=n; i++) {
    dsu[i] = i;
  }
  for(int i=1; i<=m; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  dfs(1);
  for(int i=1; i<=n; i++) {
    for(int x: adj[i]) {
      if(!is_bridge[{i, x}]) {
        if(set_of(i) != set_of(x)) {
          union_(i, x);
        }
      }
    }
  }
  map<pair<int, int>, bool> alr;
  for(int i=1; i<=n; i++) {
    for(int x: adj[i]) {
      if(set_of(i) != set_of(x) && !alr[{set_of(i), set_of(x)}]) {
        alr[{set_of(i), set_of(x)}] = alr[{set_of(x), set_of(i)}] = 1;
        adj2[set_of(i)].push_back(set_of(x));
        adj2[set_of(x)].push_back(set_of(i));
      }
    }
  }
  //adj2 is the bridge-block tree of the graph
  
}

int32_t main(){
  ios::sync_with_stdio(0); cin.tie(0);
  int t = 1;// cin >> t;
  for(int i=1; i<=t; i++) solve(i);
}  
