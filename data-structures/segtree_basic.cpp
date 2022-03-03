// WARNING: This template lacks testing for query 5, 6, 7
// WARNING: This template is over 700 lines long
// NOTE: 0 is allowed as index in this segtree version
struct segtree_basic {
  //Segtree that supports all basic operations
  //Updates: Range :=, Range +=
  //Basic queries: Range min, Range max, Range sum
  //Advanced queries: Range first >= v, Range first <= v, Range last >= v, Range last <= v
  //https://codeforces.com/edu/course/2/lesson/5/2/practice Problem A, D, E, F
  //https://codeforces.com/edu/course/2/lesson/5/3/practice Problem C
  //https://codeforces.com/edu/course/2/lesson/5/4/practice Problem A
  //#define int long long please
  struct node {
    int upd = 0;
    char type = '?'; 
    int mi = 0, ma = 0, sum = 0;
  };
  int stok;
  vector<node> st;
  void u1(int l, int r, int constl, int constr, int idx, int val) { // Range :=
    if(l <= constl && constr <= r) {
      st[idx].upd = val;
      st[idx].type = ':';
      st[idx].mi = val;
      st[idx].ma = val;
      st[idx].sum = val * (constr - constl + 1);
      return;
    }
    int mid = (constl + constr) >> 1;
    if(st[idx].type != '?') {
      if(st[idx].type == ':') {
        st[2*idx+1].upd = st[idx].upd;
        st[2*idx+1].type = ':';
        st[2*idx+1].mi = st[idx].upd;
        st[2*idx+1].ma = st[idx].upd;
        st[2*idx+1].sum = st[idx].upd * (mid - constl + 1);

        st[2*idx+2].upd = st[idx].upd;
        st[2*idx+2].type = ':';
        st[2*idx+2].mi = st[idx].upd;
        st[2*idx+2].ma = st[idx].upd;
        st[2*idx+2].sum = st[idx].upd * (constr - mid);

        st[idx].upd = 0;
        st[idx].type = '?';
        st[idx].mi = min(st[2*idx+1].mi, st[2*idx+2].mi);
        st[idx].ma = max(st[2*idx+1].ma, st[2*idx+2].ma);
        st[idx].sum = st[2*idx+1].sum + st[2*idx+2].sum;
      }
      else {
        st[2*idx+1].upd += st[idx].upd;
        if(st[2*idx+1].type == '?') st[2*idx+1].type = '+';
        st[2*idx+1].mi += st[idx].upd;
        st[2*idx+1].ma += st[idx].upd;
        st[2*idx+1].sum += st[idx].upd * (mid - constl + 1);

        st[2*idx+2].upd += st[idx].upd;
        if(st[2*idx+2].type == '?') st[2*idx+2].type = '+';
        st[2*idx+2].mi += st[idx].upd;
        st[2*idx+2].ma += st[idx].upd;
        st[2*idx+2].sum += st[idx].upd * (constr - mid);

        st[idx].upd = 0;
        st[idx].type = '?';
        st[idx].mi = min(st[2*idx+1].mi, st[2*idx+2].mi);
        st[idx].ma = max(st[2*idx+1].ma, st[2*idx+2].ma);
        st[idx].sum = st[2*idx+1].sum + st[2*idx+2].sum;
      }
    }
    if(mid<l || r<constl) u1(l, r, mid + 1, constr, 2*idx+2, val);
    else if(constr<l || r<mid+1) u1(l, r, constl, mid, 2*idx+1, val);
    else {
      u1(l, r, constl, mid, 2*idx+1, val); u1(l, r, mid + 1, constr, 2*idx+2, val);
    }
    st[idx].mi = min(st[2*idx+1].mi, st[2*idx+2].mi);
    st[idx].ma = max(st[2*idx+1].ma, st[2*idx+2].ma);
    st[idx].sum = st[2*idx+1].sum + st[2*idx+2].sum;
  }
  void u2(int l, int r, int constl, int constr, int idx, int val) { // Range +=
    if(l <= constl && constr <= r) {
      st[idx].upd += val;
      if(st[idx].type == '?') st[idx].type = '+';
      st[idx].mi += val;
      st[idx].ma += val;
      st[idx].sum += val * (constr - constl + 1);
      return;
    }
    int mid = (constl + constr) >> 1;
    if(st[idx].type != '?') {
      if(st[idx].type == ':') {
        st[2*idx+1].upd = st[idx].upd;
        st[2*idx+1].type = ':';
        st[2*idx+1].mi = st[idx].upd;
        st[2*idx+1].ma = st[idx].upd;
        st[2*idx+1].sum = st[idx].upd * (mid - constl + 1);

        st[2*idx+2].upd = st[idx].upd;
        st[2*idx+2].type = ':';
        st[2*idx+2].mi = st[idx].upd;
        st[2*idx+2].ma = st[idx].upd;
        st[2*idx+2].sum = st[idx].upd * (constr - mid);

        st[idx].upd = 0;
        st[idx].type = '?';
        st[idx].mi = min(st[2*idx+1].mi, st[2*idx+2].mi);
        st[idx].ma = max(st[2*idx+1].ma, st[2*idx+2].ma);
        st[idx].sum = st[2*idx+1].sum + st[2*idx+2].sum;
      }
      else {
        st[2*idx+1].upd += st[idx].upd;
        if(st[2*idx+1].type == '?') st[2*idx+1].type = '+';
        st[2*idx+1].mi += st[idx].upd;
        st[2*idx+1].ma += st[idx].upd;
        st[2*idx+1].sum += st[idx].upd * (mid - constl + 1);

        st[2*idx+2].upd += st[idx].upd;
        if(st[2*idx+2].type == '?') st[2*idx+2].type = '+';
        st[2*idx+2].mi += st[idx].upd;
        st[2*idx+2].ma += st[idx].upd;
        st[2*idx+2].sum += st[idx].upd * (constr - mid);

        st[idx].upd = 0;
        st[idx].type = '?';
        st[idx].mi = min(st[2*idx+1].mi, st[2*idx+2].mi);
        st[idx].ma = max(st[2*idx+1].ma, st[2*idx+2].ma);
        st[idx].sum = st[2*idx+1].sum + st[2*idx+2].sum;
      }
    }
    if(mid<l || r<constl) u2(l, r, mid + 1, constr, 2*idx+2, val);
    else if(constr<l || r<mid+1) u2(l, r, constl, mid, 2*idx+1, val);
    else {
      u2(l, r, constl, mid, 2*idx+1, val); u2(l, r, mid + 1, constr, 2*idx+2, val);
    }
    st[idx].mi = min(st[2*idx+1].mi, st[2*idx+2].mi);
    st[idx].ma = max(st[2*idx+1].ma, st[2*idx+2].ma);
    st[idx].sum = st[2*idx+1].sum + st[2*idx+2].sum;
  }
  int qu1(int l, int r, int constl, int constr, int idx) { // Range min
    if(l<=constl && constr<=r) return st[idx].mi;
    int mid = (constl + constr) >> 1;
    if(st[idx].type != '?') {
      if(st[idx].type == ':') {
        st[2*idx+1].upd = st[idx].upd;
        st[2*idx+1].type = ':';
        st[2*idx+1].mi = st[idx].upd;
        st[2*idx+1].ma = st[idx].upd;
        st[2*idx+1].sum = st[idx].upd * (mid - constl + 1);

        st[2*idx+2].upd = st[idx].upd;
        st[2*idx+2].type = ':';
        st[2*idx+2].mi = st[idx].upd;
        st[2*idx+2].ma = st[idx].upd;
        st[2*idx+2].sum = st[idx].upd * (constr - mid);

        st[idx].upd = 0;
        st[idx].type = '?';
        st[idx].mi = min(st[2*idx+1].mi, st[2*idx+2].mi);
        st[idx].ma = max(st[2*idx+1].ma, st[2*idx+2].ma);
        st[idx].sum = st[2*idx+1].sum + st[2*idx+2].sum;
      }
      else {
        st[2*idx+1].upd += st[idx].upd;
        if(st[2*idx+1].type == '?') st[2*idx+1].type = '+';
        st[2*idx+1].mi += st[idx].upd;
        st[2*idx+1].ma += st[idx].upd;
        st[2*idx+1].sum += st[idx].upd * (mid - constl + 1);

        st[2*idx+2].upd += st[idx].upd;
        if(st[2*idx+2].type == '?') st[2*idx+2].type = '+';
        st[2*idx+2].mi += st[idx].upd;
        st[2*idx+2].ma += st[idx].upd;
        st[2*idx+2].sum += st[idx].upd * (constr - mid);

        st[idx].upd = 0;
        st[idx].type = '?';
        st[idx].mi = min(st[2*idx+1].mi, st[2*idx+2].mi);
        st[idx].ma = max(st[2*idx+1].ma, st[2*idx+2].ma);
        st[idx].sum = st[2*idx+1].sum + st[2*idx+2].sum;
      }
    }
    if(mid<l || r<constl) return qu1(l, r, mid+1, constr, 2*idx+2);
    else if(constr<l || r<mid+1) return qu1(l, r, constl, mid, 2*idx+1);
    return min(qu1(l, r, constl, mid, 2*idx+1), qu1(l, r, mid+1, constr, 2*idx+2));
  }
  int qu2(int l, int r, int constl, int constr, int idx) { // Range max
    if(l<=constl && constr<=r) return st[idx].ma;
    int mid = (constl + constr) >> 1;
    if(st[idx].type != '?') {
      if(st[idx].type == ':') {
        st[2*idx+1].upd = st[idx].upd;
        st[2*idx+1].type = ':';
        st[2*idx+1].mi = st[idx].upd;
        st[2*idx+1].ma = st[idx].upd;
        st[2*idx+1].sum = st[idx].upd * (mid - constl + 1);

        st[2*idx+2].upd = st[idx].upd;
        st[2*idx+2].type = ':';
        st[2*idx+2].mi = st[idx].upd;
        st[2*idx+2].ma = st[idx].upd;
        st[2*idx+2].sum = st[idx].upd * (constr - mid);

        st[idx].upd = 0;
        st[idx].type = '?';
        st[idx].mi = min(st[2*idx+1].mi, st[2*idx+2].mi);
        st[idx].ma = max(st[2*idx+1].ma, st[2*idx+2].ma);
        st[idx].sum = st[2*idx+1].sum + st[2*idx+2].sum;
      }
      else {
        st[2*idx+1].upd += st[idx].upd;
        if(st[2*idx+1].type == '?') st[2*idx+1].type = '+';
        st[2*idx+1].mi += st[idx].upd;
        st[2*idx+1].ma += st[idx].upd;
        st[2*idx+1].sum += st[idx].upd * (mid - constl + 1);

        st[2*idx+2].upd += st[idx].upd;
        if(st[2*idx+2].type == '?') st[2*idx+2].type = '+';
        st[2*idx+2].mi += st[idx].upd;
        st[2*idx+2].ma += st[idx].upd;
        st[2*idx+2].sum += st[idx].upd * (constr - mid);

        st[idx].upd = 0;
        st[idx].type = '?';
        st[idx].mi = min(st[2*idx+1].mi, st[2*idx+2].mi);
        st[idx].ma = max(st[2*idx+1].ma, st[2*idx+2].ma);
        st[idx].sum = st[2*idx+1].sum + st[2*idx+2].sum;
      }
    }
    if(mid<l || r<constl) return qu2(l, r, mid+1, constr, 2*idx+2);
    else if(constr<l || r<mid+1) return qu2(l, r, constl, mid, 2*idx+1);
    return max(qu2(l, r, constl, mid, 2*idx+1), qu2(l, r, mid+1, constr, 2*idx+2));
  }
  int qu3(int l, int r, int constl, int constr, int idx) { // Range sum
    if(l<=constl && constr<=r) return st[idx].sum;
    int mid = (constl + constr) >> 1;
    if(st[idx].type != '?') {
      if(st[idx].type == ':') {
        st[2*idx+1].upd = st[idx].upd;
        st[2*idx+1].type = ':';
        st[2*idx+1].mi = st[idx].upd;
        st[2*idx+1].ma = st[idx].upd;
        st[2*idx+1].sum = st[idx].upd * (mid - constl + 1);

        st[2*idx+2].upd = st[idx].upd;
        st[2*idx+2].type = ':';
        st[2*idx+2].mi = st[idx].upd;
        st[2*idx+2].ma = st[idx].upd;
        st[2*idx+2].sum = st[idx].upd * (constr - mid);

        st[idx].upd = 0;
        st[idx].type = '?';
        st[idx].mi = min(st[2*idx+1].mi, st[2*idx+2].mi);
        st[idx].ma = max(st[2*idx+1].ma, st[2*idx+2].ma);
        st[idx].sum = st[2*idx+1].sum + st[2*idx+2].sum;
      }
      else {
        st[2*idx+1].upd += st[idx].upd;
        if(st[2*idx+1].type == '?') st[2*idx+1].type = '+';
        st[2*idx+1].mi += st[idx].upd;
        st[2*idx+1].ma += st[idx].upd;
        st[2*idx+1].sum += st[idx].upd * (mid - constl + 1);

        st[2*idx+2].upd += st[idx].upd;
        if(st[2*idx+2].type == '?') st[2*idx+2].type = '+';
        st[2*idx+2].mi += st[idx].upd;
        st[2*idx+2].ma += st[idx].upd;
        st[2*idx+2].sum += st[idx].upd * (constr - mid);

        st[idx].upd = 0;
        st[idx].type = '?';
        st[idx].mi = min(st[2*idx+1].mi, st[2*idx+2].mi);
        st[idx].ma = max(st[2*idx+1].ma, st[2*idx+2].ma);
        st[idx].sum = st[2*idx+1].sum + st[2*idx+2].sum;
      }
    }
    if(mid<l || r<constl) return qu3(l, r, mid + 1, constr, 2*idx + 2);
    else if(constr < l || r <mid+ 1) return qu3(l, r, constl, mid, 2*idx + 1);
    else {
      return qu3(l, r, constl, mid, 2*idx + 1) + qu3(l, r, mid + 1, constr, 2*idx + 2);
    }
  }
  int qu4(int l, int r, int constl, int constr, int idx, int val) { // First element ≥ v
    if(l<=constl && constr<=r) {
      if(st[idx].ma < val) return -1;
      while(constl < constr) {
        int mid = (constl + constr) >> 1;
        if(st[idx].type != '?') {
          if(st[idx].type == ':') {
            st[2*idx+1].upd = st[idx].upd;
            st[2*idx+1].type = ':';
            st[2*idx+1].mi = st[idx].upd;
            st[2*idx+1].ma = st[idx].upd;
            st[2*idx+1].sum = st[idx].upd * (mid - constl + 1);

            st[2*idx+2].upd = st[idx].upd;
            st[2*idx+2].type = ':';
            st[2*idx+2].mi = st[idx].upd;
            st[2*idx+2].ma = st[idx].upd;
            st[2*idx+2].sum = st[idx].upd * (constr - mid);

            st[idx].upd = 0;
            st[idx].type = '?';
            st[idx].mi = min(st[2*idx+1].mi, st[2*idx+2].mi);
            st[idx].ma = max(st[2*idx+1].ma, st[2*idx+2].ma);
            st[idx].sum = st[2*idx+1].sum + st[2*idx+2].sum;
          }
          else {
            st[2*idx+1].upd += st[idx].upd;
            if(st[2*idx+1].type == '?') st[2*idx+1].type = '+';
            st[2*idx+1].mi += st[idx].upd;
            st[2*idx+1].ma += st[idx].upd;
            st[2*idx+1].sum += st[idx].upd * (mid - constl + 1);

            st[2*idx+2].upd += st[idx].upd;
            if(st[2*idx+2].type == '?') st[2*idx+2].type = '+';
            st[2*idx+2].mi += st[idx].upd;
            st[2*idx+2].ma += st[idx].upd;
            st[2*idx+2].sum += st[idx].upd * (constr - mid);

            st[idx].upd = 0;
            st[idx].type = '?';
            st[idx].mi = min(st[2*idx+1].mi, st[2*idx+2].mi);
            st[idx].ma = max(st[2*idx+1].ma, st[2*idx+2].ma);
            st[idx].sum = st[2*idx+1].sum + st[2*idx+2].sum;
          }
        }
        if(st[2*idx+1].ma >= val) idx = 2*idx + 1, constr = mid;
        else idx = 2*idx+2, constl = mid + 1;
      }
      return constl;
    }
    int mid = (constl+constr) >> 1;
    if(st[idx].type != '?') {
      if(st[idx].type == ':') {
        st[2*idx+1].upd = st[idx].upd;
        st[2*idx+1].type = ':';
        st[2*idx+1].mi = st[idx].upd;
        st[2*idx+1].ma = st[idx].upd;
        st[2*idx+1].sum = st[idx].upd * (mid - constl + 1);

        st[2*idx+2].upd = st[idx].upd;
        st[2*idx+2].type = ':';
        st[2*idx+2].mi = st[idx].upd;
        st[2*idx+2].ma = st[idx].upd;
        st[2*idx+2].sum = st[idx].upd * (constr - mid);

        st[idx].upd = 0;
        st[idx].type = '?';
        st[idx].mi = min(st[2*idx+1].mi, st[2*idx+2].mi);
        st[idx].ma = max(st[2*idx+1].ma, st[2*idx+2].ma);
        st[idx].sum = st[2*idx+1].sum + st[2*idx+2].sum;
      }
      else {
        st[2*idx+1].upd += st[idx].upd;
        if(st[2*idx+1].type == '?') st[2*idx+1].type = '+';
        st[2*idx+1].mi += st[idx].upd;
        st[2*idx+1].ma += st[idx].upd;
        st[2*idx+1].sum += st[idx].upd * (mid - constl + 1);

        st[2*idx+2].upd += st[idx].upd;
        if(st[2*idx+2].type == '?') st[2*idx+2].type = '+';
        st[2*idx+2].mi += st[idx].upd;
        st[2*idx+2].ma += st[idx].upd;
        st[2*idx+2].sum += st[idx].upd * (constr - mid);

        st[idx].upd = 0;
        st[idx].type = '?';
        st[idx].mi = min(st[2*idx+1].mi, st[2*idx+2].mi);
        st[idx].ma = max(st[2*idx+1].ma, st[2*idx+2].ma);
        st[idx].sum = st[2*idx+1].sum + st[2*idx+2].sum;
      }
    }
    if(mid<l || r<constl) return qu4(l, r, mid+1, constr, 2*idx+2, val);
    else if(constr<l || r<mid+1) return qu4(l, r, constl, mid, 2*idx+1, val);
    else {
      int oho = qu4(l, r, constl, mid, 2*idx+1, val);
      if(oho != -1) return oho;
      return qu4(l, r, mid+1, constr, 2*idx+2, val);
    }
  }
  int qu5(int l, int r, int constl, int constr, int idx, int val) { // First element ≤ v
    if(l<=constl && constr<=r) {
      if(st[idx].mi > val) return -1;
      while(constl < constr) {
        int mid = (constl + constr) >> 1;
        if(st[idx].type != '?') {
          if(st[idx].type == ':') {
            st[2*idx+1].upd = st[idx].upd;
            st[2*idx+1].type = ':';
            st[2*idx+1].mi = st[idx].upd;
            st[2*idx+1].ma = st[idx].upd;
            st[2*idx+1].sum = st[idx].upd * (mid - constl + 1);

            st[2*idx+2].upd = st[idx].upd;
            st[2*idx+2].type = ':';
            st[2*idx+2].mi = st[idx].upd;
            st[2*idx+2].ma = st[idx].upd;
            st[2*idx+2].sum = st[idx].upd * (constr - mid);

            st[idx].upd = 0;
            st[idx].type = '?';
            st[idx].mi = min(st[2*idx+1].mi, st[2*idx+2].mi);
            st[idx].ma = max(st[2*idx+1].ma, st[2*idx+2].ma);
            st[idx].sum = st[2*idx+1].sum + st[2*idx+2].sum;
          }
          else {
            st[2*idx+1].upd += st[idx].upd;
            if(st[2*idx+1].type == '?') st[2*idx+1].type = '+';
            st[2*idx+1].mi += st[idx].upd;
            st[2*idx+1].ma += st[idx].upd;
            st[2*idx+1].sum += st[idx].upd * (mid - constl + 1);

            st[2*idx+2].upd += st[idx].upd;
            if(st[2*idx+2].type == '?') st[2*idx+2].type = '+';
            st[2*idx+2].mi += st[idx].upd;
            st[2*idx+2].ma += st[idx].upd;
            st[2*idx+2].sum += st[idx].upd * (constr - mid);

            st[idx].upd = 0;
            st[idx].type = '?';
            st[idx].mi = min(st[2*idx+1].mi, st[2*idx+2].mi);
            st[idx].ma = max(st[2*idx+1].ma, st[2*idx+2].ma);
            st[idx].sum = st[2*idx+1].sum + st[2*idx+2].sum;
          }
        }
        if(st[2*idx+1].mi <= val) idx = 2*idx + 1, constr = mid;
        else idx = 2*idx+2, constl = mid + 1;
      }
      return constl;
    }
    int mid = (constl+constr) >> 1;
    if(st[idx].type != '?') {
      if(st[idx].type == ':') {
        st[2*idx+1].upd = st[idx].upd;
        st[2*idx+1].type = ':';
        st[2*idx+1].mi = st[idx].upd;
        st[2*idx+1].ma = st[idx].upd;
        st[2*idx+1].sum = st[idx].upd * (mid - constl + 1);

        st[2*idx+2].upd = st[idx].upd;
        st[2*idx+2].type = ':';
        st[2*idx+2].mi = st[idx].upd;
        st[2*idx+2].ma = st[idx].upd;
        st[2*idx+2].sum = st[idx].upd * (constr - mid);

        st[idx].upd = 0;
        st[idx].type = '?';
        st[idx].mi = min(st[2*idx+1].mi, st[2*idx+2].mi);
        st[idx].ma = max(st[2*idx+1].ma, st[2*idx+2].ma);
        st[idx].sum = st[2*idx+1].sum + st[2*idx+2].sum;
      }
      else {
        st[2*idx+1].upd += st[idx].upd;
        if(st[2*idx+1].type == '?') st[2*idx+1].type = '+';
        st[2*idx+1].mi += st[idx].upd;
        st[2*idx+1].ma += st[idx].upd;
        st[2*idx+1].sum += st[idx].upd * (mid - constl + 1);

        st[2*idx+2].upd += st[idx].upd;
        if(st[2*idx+2].type == '?') st[2*idx+2].type = '+';
        st[2*idx+2].mi += st[idx].upd;
        st[2*idx+2].ma += st[idx].upd;
        st[2*idx+2].sum += st[idx].upd * (constr - mid);

        st[idx].upd = 0;
        st[idx].type = '?';
        st[idx].mi = min(st[2*idx+1].mi, st[2*idx+2].mi);
        st[idx].ma = max(st[2*idx+1].ma, st[2*idx+2].ma);
        st[idx].sum = st[2*idx+1].sum + st[2*idx+2].sum;
      }
    }
    if(mid<l || r<constl) return qu5(l, r, mid+1, constr, 2*idx+2, val);
    else if(constr<l || r<mid+1) return qu5(l, r, constl, mid, 2*idx+1, val);
    else {
      int oho = qu5(l, r, constl, mid, 2*idx+1, val);
      if(oho != -1) return oho;
      return qu5(l, r, mid+1, constr, 2*idx+2, val);
    }
  }
  int qu6(int l, int r, int constl, int constr, int idx, int val) { // Last element ≥ v
    if(l<=constl && constr<=r) {
      if(st[idx].ma < val) return -1;
      while(constl < constr) {
        int mid = (constl + constr) >> 1;
        if(st[idx].type != '?') {
          if(st[idx].type == ':') {
            st[2*idx+1].upd = st[idx].upd;
            st[2*idx+1].type = ':';
            st[2*idx+1].mi = st[idx].upd;
            st[2*idx+1].ma = st[idx].upd;
            st[2*idx+1].sum = st[idx].upd * (mid - constl + 1);

            st[2*idx+2].upd = st[idx].upd;
            st[2*idx+2].type = ':';
            st[2*idx+2].mi = st[idx].upd;
            st[2*idx+2].ma = st[idx].upd;
            st[2*idx+2].sum = st[idx].upd * (constr - mid);

            st[idx].upd = 0;
            st[idx].type = '?';
            st[idx].mi = min(st[2*idx+1].mi, st[2*idx+2].mi);
            st[idx].ma = max(st[2*idx+1].ma, st[2*idx+2].ma);
            st[idx].sum = st[2*idx+1].sum + st[2*idx+2].sum;
          }
          else {
            st[2*idx+1].upd += st[idx].upd;
            if(st[2*idx+1].type == '?') st[2*idx+1].type = '+';
            st[2*idx+1].mi += st[idx].upd;
            st[2*idx+1].ma += st[idx].upd;
            st[2*idx+1].sum += st[idx].upd * (mid - constl + 1);

            st[2*idx+2].upd += st[idx].upd;
            if(st[2*idx+2].type == '?') st[2*idx+2].type = '+';
            st[2*idx+2].mi += st[idx].upd;
            st[2*idx+2].ma += st[idx].upd;
            st[2*idx+2].sum += st[idx].upd * (constr - mid);

            st[idx].upd = 0;
            st[idx].type = '?';
            st[idx].mi = min(st[2*idx+1].mi, st[2*idx+2].mi);
            st[idx].ma = max(st[2*idx+1].ma, st[2*idx+2].ma);
            st[idx].sum = st[2*idx+1].sum + st[2*idx+2].sum;
          }
        }
        if(st[2*idx+2].ma >= val) idx = 2*idx + 2, constl = mid + 1;
        else idx = 2*idx + 1, constr = mid;
      }
      return constl;
    }
    int mid = (constl+constr) >> 1;
    if(st[idx].type != '?') {
      if(st[idx].type == ':') {
        st[2*idx+1].upd = st[idx].upd;
        st[2*idx+1].type = ':';
        st[2*idx+1].mi = st[idx].upd;
        st[2*idx+1].ma = st[idx].upd;
        st[2*idx+1].sum = st[idx].upd * (mid - constl + 1);

        st[2*idx+2].upd = st[idx].upd;
        st[2*idx+2].type = ':';
        st[2*idx+2].mi = st[idx].upd;
        st[2*idx+2].ma = st[idx].upd;
        st[2*idx+2].sum = st[idx].upd * (constr - mid);

        st[idx].upd = 0;
        st[idx].type = '?';
        st[idx].mi = min(st[2*idx+1].mi, st[2*idx+2].mi);
        st[idx].ma = max(st[2*idx+1].ma, st[2*idx+2].ma);
        st[idx].sum = st[2*idx+1].sum + st[2*idx+2].sum;
      }
      else {
        st[2*idx+1].upd += st[idx].upd;
        if(st[2*idx+1].type == '?') st[2*idx+1].type = '+';
        st[2*idx+1].mi += st[idx].upd;
        st[2*idx+1].ma += st[idx].upd;
        st[2*idx+1].sum += st[idx].upd * (mid - constl + 1);

        st[2*idx+2].upd += st[idx].upd;
        if(st[2*idx+2].type == '?') st[2*idx+2].type = '+';
        st[2*idx+2].mi += st[idx].upd;
        st[2*idx+2].ma += st[idx].upd;
        st[2*idx+2].sum += st[idx].upd * (constr - mid);

        st[idx].upd = 0;
        st[idx].type = '?';
        st[idx].mi = min(st[2*idx+1].mi, st[2*idx+2].mi);
        st[idx].ma = max(st[2*idx+1].ma, st[2*idx+2].ma);
        st[idx].sum = st[2*idx+1].sum + st[2*idx+2].sum;
      }
    }
    if(mid<l || r<constl) return qu6(l, r, mid+1, constr, 2*idx+2, val);
    else if(constr<l || r<mid+1) return qu6(l, r, constl, mid, 2*idx+1, val);
    else {
      int oho = qu6(l, r, mid+1, constr, 2*idx+2, val);
      if(oho != -1) return oho;
      return qu6(l, r, constl, mid, 2*idx+1, val);
    }
  }
  int qu7(int l, int r, int constl, int constr, int idx, int val) { // Last element ≤ v
    if(l<=constl && constr<=r) {
      if(st[idx].mi > val) return -1;
      while(constl < constr) {
        int mid = (constl + constr) >> 1;
        if(st[idx].type != '?') {
          if(st[idx].type == ':') {
            st[2*idx+1].upd = st[idx].upd;
            st[2*idx+1].type = ':';
            st[2*idx+1].mi = st[idx].upd;
            st[2*idx+1].ma = st[idx].upd;
            st[2*idx+1].sum = st[idx].upd * (mid - constl + 1);

            st[2*idx+2].upd = st[idx].upd;
            st[2*idx+2].type = ':';
            st[2*idx+2].mi = st[idx].upd;
            st[2*idx+2].ma = st[idx].upd;
            st[2*idx+2].sum = st[idx].upd * (constr - mid);

            st[idx].upd = 0;
            st[idx].type = '?';
            st[idx].mi = min(st[2*idx+1].mi, st[2*idx+2].mi);
            st[idx].ma = max(st[2*idx+1].ma, st[2*idx+2].ma);
            st[idx].sum = st[2*idx+1].sum + st[2*idx+2].sum;
          }
          else {
            st[2*idx+1].upd += st[idx].upd;
            if(st[2*idx+1].type == '?') st[2*idx+1].type = '+';
            st[2*idx+1].mi += st[idx].upd;
            st[2*idx+1].ma += st[idx].upd;
            st[2*idx+1].sum += st[idx].upd * (mid - constl + 1);

            st[2*idx+2].upd += st[idx].upd;
            if(st[2*idx+2].type == '?') st[2*idx+2].type = '+';
            st[2*idx+2].mi += st[idx].upd;
            st[2*idx+2].ma += st[idx].upd;
            st[2*idx+2].sum += st[idx].upd * (constr - mid);

            st[idx].upd = 0;
            st[idx].type = '?';
            st[idx].mi = min(st[2*idx+1].mi, st[2*idx+2].mi);
            st[idx].ma = max(st[2*idx+1].ma, st[2*idx+2].ma);
            st[idx].sum = st[2*idx+1].sum + st[2*idx+2].sum;
          }
        }
        if(st[2*idx+2].mi <= val) idx = 2*idx + 2, constl = mid + 1;
        else idx = 2*idx + 1, constr = mid;
      }
      return constl;
    }
    int mid = (constl+constr) >> 1;
    if(st[idx].type != '?') {
      if(st[idx].type == ':') {
        st[2*idx+1].upd = st[idx].upd;
        st[2*idx+1].type = ':';
        st[2*idx+1].mi = st[idx].upd;
        st[2*idx+1].ma = st[idx].upd;
        st[2*idx+1].sum = st[idx].upd * (mid - constl + 1);

        st[2*idx+2].upd = st[idx].upd;
        st[2*idx+2].type = ':';
        st[2*idx+2].mi = st[idx].upd;
        st[2*idx+2].ma = st[idx].upd;
        st[2*idx+2].sum = st[idx].upd * (constr - mid);

        st[idx].upd = 0;
        st[idx].type = '?';
        st[idx].mi = min(st[2*idx+1].mi, st[2*idx+2].mi);
        st[idx].ma = max(st[2*idx+1].ma, st[2*idx+2].ma);
        st[idx].sum = st[2*idx+1].sum + st[2*idx+2].sum;
      }
      else {
        st[2*idx+1].upd += st[idx].upd;
        if(st[2*idx+1].type == '?') st[2*idx+1].type = '+';
        st[2*idx+1].mi += st[idx].upd;
        st[2*idx+1].ma += st[idx].upd;
        st[2*idx+1].sum += st[idx].upd * (mid - constl + 1);

        st[2*idx+2].upd += st[idx].upd;
        if(st[2*idx+2].type == '?') st[2*idx+2].type = '+';
        st[2*idx+2].mi += st[idx].upd;
        st[2*idx+2].ma += st[idx].upd;
        st[2*idx+2].sum += st[idx].upd * (constr - mid);

        st[idx].upd = 0;
        st[idx].type = '?';
        st[idx].mi = min(st[2*idx+1].mi, st[2*idx+2].mi);
        st[idx].ma = max(st[2*idx+1].ma, st[2*idx+2].ma);
        st[idx].sum = st[2*idx+1].sum + st[2*idx+2].sum;
      }
    }
    if(mid<l || r<constl) return qu7(l, r, mid+1, constr, 2*idx+2, val);
    else if(constr<l || r<mid+1) return qu7(l, r, constl, mid, 2*idx+1, val);
    else {
      int oho = qu7(l, r, mid+1, constr, 2*idx+2, val);
      if(oho != -1) return oho;
      return qu7(l, r, constl, mid, 2*idx+1, val);
    }
  }
  public:
  void resize(int k) {
    stok = k;
    st.resize(4 * k + 10);
  }
  void range_assign(int l, int r, int v) {
    u1(l, r, 0, stok, 0, v);
  }
  void range_add(int l, int r, int v) {
    u2(l, r, 0, stok, 0, v);
  }
  int query_min(int l, int r) {
    return qu1(l, r, 0, stok, 0);
  }
  int query_max(int l, int r) {
    return qu2(l, r, 0, stok, 0);
  }
  int query_sum(int l, int r) {
    return qu3(l, r, 0, stok, 0);
  }
  int query_firstAtLeast(int l, int r, int v) {
    return qu4(l, r, 0, stok, 0, v);
  }
  int query_firstAtMost(int l, int r, int v) {
    return qu5(l, r, 0, stok, 0, v);
  }
  int query_lastAtLeast(int l, int r, int v) {
    return qu6(l, r, 0, stok, 0, v);
  }
  int query_lastAtMost(int l, int r, int v) {
    return qu7(l, r, 0, stok, 0, v);
  }
};
