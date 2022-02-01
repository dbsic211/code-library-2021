struct BigInteger {
  string s;
  public:
  void read() {
    cin >> s;
  }
  int size() {
    return (int)s.size();
  }
  void erase(int pos, int nums) {
    s.erase(pos, nums);
  }
  void write() {
    cout << s << "\n";
  }
  void insert(int pos, char x) {
    string t = ""; t += x;
    s.insert(pos, t);
  }
  char get(int pos) {
    return s[pos];
  }
  void append(char x) {
    s += x;
  }
  void reverse() {
    ::reverse(s.begin(), s.end());
  }
  BigInteger operator-(BigInteger other) {  // O(n)
    int neg = 0;
    if(s.size() < other.s.size()) {
      neg = 1;
    }
    if(s.size() == other.s.size() && s < other.s) {
      neg = 1;
    }
    int i = s.size() - 1, j = other.s.size() - 1;
    if(neg) swap(i, j);
    int borrow = 0;
    int m = max((int)s.size(), (int)other.s.size());
    BigInteger res;
    while(m--) {
      int me = (i < 0 ? 0 : get(i) - '0');
      int you = (j < 0 ? 0 : other.get(j) - '0');
      if(neg) swap(me, you);
      me -= borrow;
      if(me < you) {
        borrow = 1;
        me += 10;
      }
      else {
        borrow = 0;
      }
      res.append(char(me - you + '0'));
      i--, j--;
    }
    while(res.size() > 1 && res.get(res.size() - 1) == '0') {
      res.erase(res.size() - 1, 1);
    }
    res.reverse();
    if(neg) res.insert(0, '-');
    return res;
  }
};
BigInteger abs(BigInteger x) { // O(n)
  if(x.get(0) == '-') x.erase(0, 1);
  return x;
}
BigInteger min(BigInteger x, BigInteger y) { // O(n)
  if(x.size() != y.size()) return (x.size() < y.size() ? x : y);
  return (x.s < y.s ? x : y);
}
BigInteger concat(BigInteger x, BigInteger y) {
  BigInteger z;
  z.s = x.s + y.s;
  return z;
}
