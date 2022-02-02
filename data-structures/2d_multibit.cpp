OST bit[MAXN]; // 2D bit in regular matrices but only supporting single add/del
int id = 0;
map<pair<int, int>, queue<int> > mp;
void insert(int x, int y) {
  id++;
  mp[{y, x}].push(id);
  for(;x<MAXN;x+=x&-x) bit[x].insert({{y, x}, id});
}
void erase(int x, int y) {
  int ono = mp[{y, x}].front(); mp[{y, x}].pop();
  for(;x<MAXN;x+=x&-x) bit[x].erase({{y, x}, ono});
}
int query(int x, int y) {
  int sum = 0;
  for(;x;x-=x&-x) sum += bit[x].order_of_key({{y+1, 0}, 0});
  return sum;
}
