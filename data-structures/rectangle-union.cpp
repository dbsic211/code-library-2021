#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 200412;

struct node {
  int sum = 0, len = 0;
} st[4*MAXN];
int huh[MAXN];
void u(int l, int r, int constl, int constr, int idx, int val) {
  if(l<=constl && constr<=r) {
    st[idx].sum += val;
    if(st[idx].sum > 0) {
      st[idx].len = huh[constr] - huh[constl - 1];
    }
    else if(constl != constr) {
      st[idx].len = st[2*idx+1].len + st[2*idx+2].len;;
    }
    else {
      st[idx].len = 0;
    }
    return;
  }
  int mid = (constl+constr) >> 1;
  if(mid <l || r< constl) u(l, r, mid+1, constr, 2*idx+2, val);
  else if(constr<l || r<mid+1 ) u(l, r, constl, mid, 2*idx+1, val);
  else {
    u(l, r, constl, mid, 2*idx+1, val);
    u(l, r, mid+1, constr, 2*idx+2, val);
  }
  if(st[idx].sum > 0) {
    st[idx].len = huh[constr] - huh[constl - 1];
  }
  else {
    st[idx].len = st[2*idx+1].len + st[2*idx+2].len;
  }
}

void update(int l, int r, int v) {
  u(l, r, 0, MAXN-1, 0, v);
}
int query() {
  return st[0].len;
}

struct rect {
  int lx, ly, hx, hy;
};
unordered_map<int, vector<pair<pair<int, int>,int> > > fafa;
set<int> ds;
unordered_map<int, int> is;
int _1tpd = 0;
int ono = 0;
set<int> rofl;
signed main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int n;
  cin >> n;
  rect r[n];
  for(int i=0; i<n; i++) {
    cin >> r[i].lx >> r[i].ly >> r[i].hx >> r[i].hy;
    rofl.insert(r[i].lx);
    ds.insert(r[i].ly);
    rofl.insert(r[i].hx);
    ds.insert(r[i].hy);
  }
  for(int x: ds) is[x] = ++_1tpd, huh[_1tpd] = x;
  for(int i=0; i<n; i++) {
    fafa[r[i].lx].push_back({{
    is[r[i].ly], is[r[i].hy]}, 1});
    fafa[r[i].hx].push_back({{
    is[r[i].ly], is[r[i].hy]}, -1});
  }
  vector<int> uwu;
  for(int x: rofl) uwu.push_back(x);
  int prv = 0;
  for(int x: uwu) {
    ono += (x-prv) * query();
    for(pair<pair<int,int>,int> a0_forever: fafa[x]) {
      if(a0_forever.first.first == a0_forever.first.second) continue;
      update(a0_forever.first.first + 1, a0_forever.first.second, a0_forever.second);
    }
    prv = x;
  }
  cout<<ono<<"\n";
}
