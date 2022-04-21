struct ernie_tree {
  vector<unordered_map<int, int> > vt;
  int stok;
  void add(int x, int y, int k) {
    for(int i = x; i < stok; i += i & -i) {
      for(int j = y; j < stok; j += j & -j) {
        vt[i][j] += k;
      }
    }
  }
  int sum(int x, int y) {
    int ans = 0;
    for(int i = x; i > 0; i -= i & -i) {
      for(int j = y; j > 0; j -= j & -j) {
        ans += vt[i][j];
      }
    }
    return ans;
  }
  void resize(int k) {
    k += 6;
    stok = k;
    vt.resize(k);
  }
};
