#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 5e3 + 10;
vector<pair<int, pair<int,int> > > adj[MAXN]; //cost, flow
unordered_map<int, int> cor[MAXN];
void addedge(int u, int v, int w ,int c){
    cor[u][adj[u].size()] = adj[v].size();
    cor[v][adj[v].size()] = adj[u].size();
    adj[u].push_back({v, {w, c}});
    adj[v].push_back({u, {-w, 0}});
}
signed main() {
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    for(int i=0; i<m; i++){
        int u, v, w, c; cin >> u >> v >> c >> w;
        addedge(u, v, w, c);
    }
    int mincost = 0, maxflow = 0;
    while(1){
        queue<int> q;
        int dist[n+1];
        for(int i=1; i<=n; i++) dist[i] = INT_MAX;
        dist[s] = 0;
        bool in[n+1];
        for(int i=1; i<=n; i++) in[i] = 0;
        q.push(s);
        in[s] = 1;
        pair<int, int> pre[n+1];
        while(q.size()){
            int f = q.front(); q.pop();
            in[f] = 0;
            for(int j=0; j<adj[f].size(); j++){
                if(adj[f][j].second.second > 0 && dist[adj[f][j].first] > dist[f] + adj[f][j].second.first){
                    dist[adj[f][j].first] = dist[f] + adj[f][j].second.first;
                    if(!in[adj[f][j].first]) q.push(adj[f][j].first);
                    pre[adj[f][j].first] = {f, j};
                }
            }
        }
        if(dist[t] == INT_MAX) break;
        int e = INT_MAX;
        int cur = t;
        while(cur != s){
            e = min(e, adj[pre[cur].first][pre[cur].second].second.second);
            cur = pre[cur].first;
        }
        cur = t;
        while(cur != s){
            adj[pre[cur].first][pre[cur].second].second.second -= e;
            adj[cur][cor[pre[cur].first][pre[cur].second]].second.second += e;
            cur = pre[cur].first;
        }
        mincost += dist[t] * e;
        maxflow += e;
    }
    cout << maxflow << ' ' << mincost << endl;
}
