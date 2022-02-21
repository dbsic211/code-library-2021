struct segtree_dec {
  // #define int long long required!!!
  // Maintain a monotonically decreasing(!!!) array, initially all zeros
  // Maintain the following two types of queries:
  // 1. Given i, find range of indices [l, r] s.t. a[i] = a[j] for all l ≤ j ≤ r (parallel binary search, log(n))
  // 2. Given l, r, v, perform a[i] += v for all l ≤ i ≤ r
  // 3. Given l, r, compute a[l] + a[l+1] + ... + a[r]
  // 4. Given l, r, compute max(a[l], a[l+1], ..., a[r]) ( = a[l])
  // 5. Given l, r, compute min(a[l], a[l+1], ..., a[r]) ( = a[r])
  struct node {
    int mi = 0, ma = 0, upd = 0, sum = 0;
  };
  vector<node> a;
  int stok;
  void u(int l, int r, int constl, int constr, int idx, int v) {
    if(l<=constl && constr<=r) {
      a[idx].mi += v;
      a[idx].ma += v;
      a[idx].upd += v;
      a[idx].sum += v * (constr-constl+1);
      return;
    }
    int mid = (constl + constr) >> 1;
    if(a[idx].upd != 0) {
      a[2*idx+1].mi += a[idx].upd;
      a[2*idx+2].mi += a[idx].upd;
      a[2*idx+1].ma += a[idx].upd;
      a[2*idx+2].ma += a[idx].upd;
      a[2*idx+1].upd += a[idx].upd;
      a[2*idx+2].upd += a[idx].upd;
      a[2*idx+1].sum += a[idx].upd * (mid - constl + 1);
      a[2*idx+2].sum += a[idx].upd * (constr - mid);
      a[idx].upd = 0;
      a[idx].sum = a[2*idx+1].sum + a[2*idx+2].sum;
      a[idx].mi = min(a[2*idx+1].mi, a[2*idx+2].mi);
      a[idx].ma = max(a[2*idx+1].ma, a[2*idx+2].ma);
    }
    if(mid<l || r<constl) u(l, r, mid+1, constr, 2*idx+2, v);
    else if(constr<l || r<mid+1) u(l, r, constl, mid, 2*idx+1, v);
    else {
      u(l, r, constl, mid, 2*idx+1, v);
      u(l, r, mid+1, constr, 2*idx+2, v);
    }
    a[idx].mi = min(a[2*idx+1].mi, a[2*idx+2].mi);
    a[idx].ma = max(a[2*idx+1].ma, a[2*idx+2].ma);
    a[idx].sum = a[2*idx+1].sum + a[2*idx+2].sum;
  }
  int qu1(int l, int r, int constl, int constr, int idx) {
    if(l<=constl && constr<=r) return a[idx].sum;
    int mid = (constl+constr) >> 1;
    if(a[idx].upd != 0) {
      a[2*idx+1].mi += a[idx].upd;
      a[2*idx+2].mi += a[idx].upd;
      a[2*idx+1].ma += a[idx].upd;
      a[2*idx+2].ma += a[idx].upd;
      a[2*idx+1].upd += a[idx].upd;
      a[2*idx+2].upd += a[idx].upd;
      a[2*idx+1].sum += a[idx].upd * (mid - constl + 1);
      a[2*idx+2].sum += a[idx].upd * (constr - mid);
      a[idx].upd = 0;
      a[idx].sum = a[2*idx+1].sum + a[2*idx+2].sum;
      a[idx].mi = min(a[2*idx+1].mi, a[2*idx+2].mi);
      a[idx].ma = max(a[2*idx+1].ma, a[2*idx+2].ma);
    }
    if(mid<l || r<constl) return qu1(l, r, mid+1, constr, 2*idx+2);
    else if(constr<l || r<mid+1) return qu1(l, r, constl, mid, 2*idx+1);
    return qu1(l, r, constl, mid, 2*idx+1) + qu1(l, r, mid+1, constr, 2*idx+2);
  }
  int qu2(int l, int r, int constl, int constr, int idx) {
    if(l<=constl && constr<=r) return a[idx].mi;
    int mid = (constl+constr) >> 1;
    if(a[idx].upd != 0) {
      a[2*idx+1].mi += a[idx].upd;
      a[2*idx+2].mi += a[idx].upd;
      a[2*idx+1].ma += a[idx].upd;
      a[2*idx+2].ma += a[idx].upd;
      a[2*idx+1].upd += a[idx].upd;
      a[2*idx+2].upd += a[idx].upd;
      a[2*idx+1].sum += a[idx].upd * (mid - constl + 1);
      a[2*idx+2].sum += a[idx].upd * (constr - mid);
      a[idx].upd = 0;
      a[idx].sum = a[2*idx+1].sum + a[2*idx+2].sum;
      a[idx].mi = min(a[2*idx+1].mi, a[2*idx+2].mi);
      a[idx].ma = max(a[2*idx+1].ma, a[2*idx+2].ma);
    }
    if(mid<l || r<constl) return qu2(l, r, mid+1, constr, 2*idx+2);
    else if(constr<l || r<mid+1) return qu2(l, r, constl, mid, 2*idx+1);
    return min(qu2(l, r, constl, mid, 2*idx+1), qu2(l, r, mid+1, constr, 2*idx+2));
  }
  int qu3(int l, int r, int constl, int constr, int idx) {
    if(l<=constl && constr<=r) return a[idx].ma;
    int mid = (constl+constr) >> 1;
    if(a[idx].upd != 0) {
      a[2*idx+1].mi += a[idx].upd;
      a[2*idx+2].mi += a[idx].upd;
      a[2*idx+1].ma += a[idx].upd;
      a[2*idx+2].ma += a[idx].upd;
      a[2*idx+1].upd += a[idx].upd;
      a[2*idx+2].upd += a[idx].upd;
      a[2*idx+1].sum += a[idx].upd * (mid - constl + 1);
      a[2*idx+2].sum += a[idx].upd * (constr - mid);
      a[idx].upd = 0;
      a[idx].sum = a[2*idx+1].sum + a[2*idx+2].sum;
      a[idx].mi = min(a[2*idx+1].mi, a[2*idx+2].mi);
      a[idx].ma = max(a[2*idx+1].ma, a[2*idx+2].ma);
    }
    if(mid<l || r<constl) return qu3(l, r, mid+1, constr, 2*idx+2);
    else if(constr<l || r<mid+1) return qu3(l, r, constl, mid, 2*idx+1);
    return max(qu3(l, r, constl, mid, 2*idx+1), qu3(l, r, mid+1, constr, 2*idx+2));
  }
  int qu4(int l, int r, int constl, int constr, int idx, int val) {
    if(l<=constl && constr<=r) {
      if(a[idx].mi > val) return -1;
      while(constl < constr) {
        int mid = (constl + constr) >> 1;
        if(a[idx].upd != 0) {
          a[2*idx+1].mi += a[idx].upd;
          a[2*idx+2].mi += a[idx].upd;
          a[2*idx+1].ma += a[idx].upd;
          a[2*idx+2].ma += a[idx].upd;
          a[2*idx+1].upd += a[idx].upd;
          a[2*idx+2].upd += a[idx].upd;
          a[2*idx+1].sum += a[idx].upd * (mid - constl + 1);
          a[2*idx+2].sum += a[idx].upd * (constr - mid);
          a[idx].upd = 0;
          a[idx].sum = a[2*idx+1].sum + a[2*idx+2].sum;
          a[idx].mi = min(a[2*idx+1].mi, a[2*idx+2].mi);
          a[idx].ma = max(a[2*idx+1].ma, a[2*idx+2].ma);
        }
        if(a[2*idx+1].mi == val) {
          idx = 2*idx+1;
          constr = mid;
        }
        else {
          idx = 2*idx+2;
          constl = mid + 1;
        }
      }
      return (a[idx].mi == val? constl: -1);
    }
    int mid = (constl + constr) >> 1;
    if(a[idx].upd != 0) {
      a[2*idx+1].mi += a[idx].upd;
      a[2*idx+2].mi += a[idx].upd;
      a[2*idx+1].ma += a[idx].upd;
      a[2*idx+2].ma += a[idx].upd;
      a[2*idx+1].upd += a[idx].upd;
      a[2*idx+2].upd += a[idx].upd;
      a[2*idx+1].sum += a[idx].upd * (mid - constl + 1);
      a[2*idx+2].sum += a[idx].upd * (constr - mid);
      a[idx].upd = 0;
      a[idx].sum = a[2*idx+1].sum + a[2*idx+2].sum;
      a[idx].mi = min(a[2*idx+1].mi, a[2*idx+2].mi);
      a[idx].ma = max(a[2*idx+1].ma, a[2*idx+2].ma);
    }
    if(mid<l || r<constl) {
      return qu4(l, r, mid+1, constr, 2*idx+2, val);
    }
    else if(constr<l || r<mid+1) {
      return qu4(l, r, constl, mid, 2*idx+1, val);
    }
    int omg = qu4(l, r, constl, mid, 2*idx+1, val);
    if(omg != -1) return omg;
    return qu4(l, r, mid+1, constr, 2*idx+2, val);
  }
  int qu5(int l, int r, int constl, int constr, int idx, int val) {
    if(l<=constl && constr<=r) {
      if(a[idx].ma < val) return -1;
      while(constl < constr) {
        int mid = (constl + constr) >> 1;
        if(a[idx].upd != 0) {
          a[2*idx+1].mi += a[idx].upd;
          a[2*idx+2].mi += a[idx].upd;
          a[2*idx+1].ma += a[idx].upd;
          a[2*idx+2].ma += a[idx].upd;
          a[2*idx+1].upd += a[idx].upd;
          a[2*idx+2].upd += a[idx].upd;
          a[2*idx+1].sum += a[idx].upd * (mid - constl + 1);
          a[2*idx+2].sum += a[idx].upd * (constr - mid);
          a[idx].upd = 0;
          a[idx].sum = a[2*idx+1].sum + a[2*idx+2].sum;
          a[idx].mi = min(a[2*idx+1].mi, a[2*idx+2].mi);
          a[idx].ma = max(a[2*idx+1].ma, a[2*idx+2].ma);
        }
        if(a[2*idx+2].ma == val) {
          idx = 2*idx+2;
          constl = mid+1;
        }
        else {
          idx = 2*idx+1;
          constr = mid;
        }
      }
      return (a[idx].ma == val? constl: -1);
    }
    int mid = (constl + constr) >> 1;
    if(a[idx].upd != 0) {
      a[2*idx+1].mi += a[idx].upd;
      a[2*idx+2].mi += a[idx].upd;
      a[2*idx+1].ma += a[idx].upd;
      a[2*idx+2].ma += a[idx].upd;
      a[2*idx+1].upd += a[idx].upd;
      a[2*idx+2].upd += a[idx].upd;
      a[2*idx+1].sum += a[idx].upd * (mid - constl + 1);
      a[2*idx+2].sum += a[idx].upd * (constr - mid);
      a[idx].upd = 0;
      a[idx].sum = a[2*idx+1].sum + a[2*idx+2].sum;
      a[idx].mi = min(a[2*idx+1].mi, a[2*idx+2].mi);
      a[idx].ma = max(a[2*idx+1].ma, a[2*idx+2].ma);
    }
    if(mid<l || r<constl) {
      return qu5(l, r, mid+1, constr, 2*idx+2, val);
    }
    else if(constr<l || r<mid+1) {
      return qu5(l, r, constl, mid, 2*idx+1, val);
    }
    int omg = qu5(l, r, mid+1, constr, 2*idx+2, val);
    if(omg != -1) return omg;
    return qu5(l, r, constl, mid, 2*idx+1, val);
  }
  public:
  void resize(int k) {
    stok = k;
    a.resize(4*k + 10);
  }
  void range_add(int l, int r, int v) {
    u(l, r, 0, stok, 0, v);
  }
  int query_sum(int l, int r) {
    return qu1(l, r, 0, stok, 0);
  }
  int query_min(int l, int r) {
    return qu2(l, r, 0, stok, 0);
  }
  int query_max(int l, int r) {
    return qu3(l, r, 0, stok, 0);
  }
  pair<int, int> query_range(int i) {
    int val = query_sum(i, i);
    int lb = qu4(1, i, 0, stok, 0, val);
    int rb = qu5(i, stok, 0, stok, 0, val);
    return {lb, rb};
  }
};
