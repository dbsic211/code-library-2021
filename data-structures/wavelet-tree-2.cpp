//Works, but extremely inefficient
#define int long long
struct wavelet_tree { // 0-based wavelet tree
  struct node {
    vector<pair<int, int> > v; // (value, index)
    vector<int> sums;
    int mi, ma;
  };
  vector<node> st;
  int stok;
  int stomi, stoma;
  void bu(int l, int r, vector<pair<int, int> > all, int idx) {
    st[idx].mi = l, st[idx].ma = r;
    st[idx].v = all;
    for(pair<int, int> x: st[idx].v) {
      int sz = st[idx].sums.size();
      if(!sz) st[idx].sums.push_back(x.first);
      else st[idx].sums.push_back(st[idx].sums[sz - 1] + x.first);
    }
    if(all.size() <= 1 || l == r) {
      return;
    }
    int mid = (l + r) >> 1;
    vector<pair<int, int> > lchild, rchild;
    for(pair<int, int> x: all) {
      if(x.first <= mid) lchild.push_back(x);
      else rchild.push_back(x);
    }
    bu(l, mid, lchild, 2*idx + 1);
    bu(mid+1, r, rchild, 2*idx + 2);
    
  }
  int qu1(int l, int r, int constl, int constr, int idx, int val) { // Node idx: stores elements that have value in [constl, constr]
    if(st[idx].v.size() == 1) { // Found
      return (st[idx].v[0].second >= l && st[idx].v[0].second <= r && val == 1 ? st[idx].v[0].first : -1);
    }
    if(constl == constr) {
      int lb = 0, rb = st[idx].v.size() - 1;
      while(lb < rb) {
        int mid = (lb + rb + 1) >> 1;
        if(st[idx].v[mid].second <= r) lb = mid;
        else rb = mid - 1;
      }
      int lb2 = 0, rb2 = st[idx].v.size() - 1;
      while(lb2 < rb2) {
        int mid = (lb2 + rb2) >> 1;
        if(st[idx].v[mid].second >= l) rb2 = mid;
        else lb2 = mid + 1;
      }
      if(st[idx].v[lb].second <= r && st[idx].v[lb2].second >= l) {
        int ct = lb - lb2 + 1;
        return (ct >= val ? constl : -1);
      }
    }
    if(st[2*idx+1].v.empty()) {
      int mid = (constl + constr) >> 1;
      return qu1(l, r, mid+1, constr, 2*idx+2, val);
    }
    int lb = 0, rb = st[2*idx+1].v.size() - 1;
    while(lb < rb) {
      int mid = (lb + rb + 1) >> 1;
      if(st[2*idx+1].v[mid].second <= r) lb = mid;
      else rb = mid - 1;
    }
    int lb2 = 0, rb2 = st[2*idx+1].v.size() - 1;
    while(lb2 < rb2) {
      int mid = (lb2 + rb2) >> 1;
      if(st[2*idx+1].v[mid].second >= l) rb2 = mid;
      else lb2 = mid + 1;
    }
    int cnt = 0;
    if(st[2*idx+1].v[lb].second <= r && st[2*idx+1].v[lb2].second >= l) {
      cnt = lb - lb2 + 1;
    }
    
    int mid = (constl + constr) >> 1;
    if(cnt >= val) return qu1(l, r, constl, mid, 2*idx+1, val);
    else return qu1(l, r, mid+1, constr, 2*idx+2, val - cnt);
  }
  int qu2(int l, int r, int constl, int constr, int idx, int val) { // Sum of elements in [l, r] that ≤ val
    if(constl > val || st[idx].v.empty()) {
      return 0;
    }
    if(st[idx].v.size() == 1) {
      if(st[idx].v[0].second >= l && st[idx].v[0].second <= r && st[idx].v[0].first <= val) return st[idx].v[0].first;
      return 0;
    }
    if(constr <= val) {
      int lb = 0, rb = st[idx].v.size() - 1;
      while(lb < rb) {
        int mid = (lb + rb + 1) >> 1;
        if(st[idx].v[mid].second <= r) lb = mid;
        else rb = mid - 1;
      }
      int lb2 = 0, rb2 = st[idx].v.size() - 1;
      while(lb2 < rb2) {
        int mid = (lb2 + rb2) >> 1;
        if(st[idx].v[mid].second >= l) rb2 = mid;
        else lb2 = mid + 1;
      }
      int cnt = 0;
      if(st[idx].v[lb].second <= r && st[idx].v[lb2].second >= l) cnt = st[idx].sums[lb] - (lb2 == 0 ? 0 : st[idx].sums[lb2 - 1]);
      return cnt;
    }
    int mid = (constl + constr) >> 1;
    return qu2(l, r, constl, mid, 2*idx+1, val) + qu2(l, r, mid+1, constr, 2*idx+2, val);
  }
  int qu3(int l, int r, int constl, int constr, int idx, int val) { // Number of elements in [l, r] that ≤ val
    if(constl > val || st[idx].v.empty()) {
      return 0;
    }
    if(st[idx].v.size() == 1) {
      if(st[idx].v[0].second >= l && st[idx].v[0].second <= r && st[idx].v[0].first <= val) return 1;
      return 0;
    }
    if(constr <= val) {
      int lb = 0, rb = st[idx].v.size() - 1;
      while(lb < rb) {
        int mid = (lb + rb + 1) >> 1;
        if(st[idx].v[mid].second <= r) lb = mid;
        else rb = mid - 1;
      }
      int lb2 = 0, rb2 = st[idx].v.size() - 1;
      while(lb2 < rb2) {
        int mid = (lb2 + rb2) >> 1;
        if(st[idx].v[mid].second >= l) rb2 = mid;
        else lb2 = mid + 1;
      }
      int cnt = 0;
      if(st[idx].v[lb].second <= r && st[idx].v[lb2].second >= l) cnt = lb - lb2 + 1;
      return cnt;
    }
    int mid = (constl + constr) >> 1;
    return qu3(l, r, constl, mid, 2*idx+1, val) + qu3(l, r, mid+1, constr, 2*idx+2, val);
  }
  public:
  void resize(int k, int mi, int ma) {
    stok = k;
    st.resize(8 * k * fastlog(ma - mi + 2) + 10); // Warning: n log n memory!!
  }
  void build(int mi, int ma, vector<int> uwu) {
    stomi = mi, stoma = ma;
    vector<pair<int, int > > owo;
    for(int i=0; i<uwu.size(); i++) {
      owo.push_back({uwu[i], i});
    }
    bu(mi, ma, owo, 0);
  }
  int kth(int l, int r, int k) { // Finds the VALUE of the k-th order statistics (k-th SMALLEST value)
    return qu1(l, r, stomi, stoma, 0, k);
  }
  int sum(int l, int r, int k) {
    if(k < stomi) return 0;
    k = min(k, stoma);
    return qu2(l, r, stomi, stoma, 0, k);
  }
  int count(int l, int r, int k) {
    if(k < stomi || k > stoma) return 0;
    if(k == stomi) return qu3(l, r, stomi, stoma, 0, k);
    else return qu3(l, r, stomi, stoma, 0, k) - qu3(l, r, stomi, stoma, 0, k - 1);
  }
  int lte(int l, int r, int k) {
    if(k < stomi) return 0;
    k = min(k, stoma);
    return qu3(l, r, stomi, stoma, 0, k);
  }
  int upper_bound(int l, int r, int k) { 
    int qwq = lte(l, r, k - 1);
    if(qwq == 0) return -1;
    return kth(l, r, qwq);
  }
};
