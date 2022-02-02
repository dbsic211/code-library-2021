//https://codeforces.com/blog/entry/52094
OST bit[MAXN]; // 2D bit in binary matrices
void insert(int x, int y) {
  for(;x<MAXN;x+=x&-x) bit[x].insert({y, x});
}
void erase(int x, int y) {
  for(;x<MAXN;x+=x&-x) bit[x].erase({y, x});
}
int query(int x, int y) {
  int sum = 0;
  for(;x;x-=x&-x) sum += bit[x].order_of_key({y+1, 0});
  return sum;
}
