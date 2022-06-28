vector<int> prefix_function(string t) {
  int n = t.size();
  vector<int> lps(n);
  lps[0] = 0;
  for(int i=1; i<n; i++) {
    int j = lps[i-1];
    while(j > 0 && t[i] != t[j]) {
      j = lps[j-1];
    }
    if(t[i] == t[j]) lps[i] = j+1;
    else lps[i] = 0;
  }
  return lps;
}
