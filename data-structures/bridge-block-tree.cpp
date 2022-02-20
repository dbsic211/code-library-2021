//C++ bridge-block tree from general graph
//Multiple edges and self loops allowed
//Complexity: O(N log N) with multiple edges and self loops
//Complexity: O(N) without the above

//adj2 is the bridge block tree
//Access a node by set_of(i)
//is_bridge[{a, b}] returns whether edge (a, b) is a bridge in the graph
//o[{a, b}] returns the number of appearances of edge (a, b) in the graph

#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 10;
const int MOD = 1e9 + 7;
#define int long long
 
vector<int> adj[MAXN];
int tin[MAXN], tout[MAXN], low[MAXN], vis[MAXN], tim = 0;
map<pair<int, int>, bool> is_bridge;
map<pair<int, int>, int> o;
void dfs(int node, int prv) {
  tin[node] = ++tim;
  int mi = 1e9;
  vis[node] = 1;
  for(int x: adj[node]) {
    if(!vis[x]) {
      dfs(x, node);
      mi = min(mi, low[x]);
      if(low[x] > tin[node] && o[{x, node}] == 1) {
        is_bridge[{x, node}] = is_bridge[{node, x}] = 1;
      }
    }
  }
  tout[node] = ++tim;
  low[node] = tin[node];
  for(int x: adj[node]) {
    if(tin[x] < tin[node] && tout[x] == 0 && tin[x] > 0 && x != prv) {
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
  int n, m;
  cin >> n >> m;
  for(int i=1; i<=n; i++) {
    dsu[i] = i;
  }
  for(int i=1; i<=m; i++) {
    int a, b;
    cin >> a >> b;
    o[{a, b}]++; o[{b, a}]++;
    if(a == b) continue;
    if(o[{a, b}] > 1) continue;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  for(int i=1; i<=n; i++) {
    if(!vis[i]) dfs(i, -1);
  }
  for(int i=1; i<=n; i++) {
    for(int x: adj[i]) {
      if(!is_bridge[{i, x}] || o[{i, x}] > 1) {
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
