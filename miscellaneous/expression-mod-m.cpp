int M;
int Stoi(string o) {
  bool neg = 0;
  if(o[0] == '-') o.erase(0, 1), neg = 1;
  int p = 0;
  for(char c: o) {
    p = (p * 10 + c - 48) % M;
  }
  return (neg ? (M - p) % M : p);
}
int eval(string now) {
  if(now[0] == '-') now = "0" + now;
  vector<string> v;
  string str;
  for(int i=0; i<now.size(); i++) {
    if(now[i] == '+' || now[i] == '-' || now[i] == '*' || now[i] == '(' || now[i] == ')') {
      if(str != "") v.push_back(str);
      str = "";
      v.push_back(now.substr(i, 1));
      if(now[i] == '*' && now[i+1] == '-') {
        str += "-";
        i++;
      }
      if(now[i] == '(' && now[i+1] == '-') {
        str += "-";
        i++;
      }
    }
    else {
      str += now[i];
    }
  }
  if(str != "") v.push_back(str);
  v.push_back("+");
  v.push_back("0");
  stack<string >st;
  for(int i=0; i<v.size(); i++) {
    if(v[i] != "+" && v[i] != "-" && v[i] != "*" && v[i] != "(" && v[i] != ")") { // num
      int cur = Stoi(v[i]);
      while(st.size() && st.top() == "*") {
        int nums1 = cur;
        st.pop();
        int nums2 = Stoi(st.top());
        st.pop();
        cur = (nums1 * nums2) % M;
      }
      st.push(to_string(cur));
      if(i+1 == v.size() || v[i+1] != "*") {
        int cur = Stoi(st.top()); 
        st.pop();
        while(st.size() && (st.top() == "+" || st.top() == "-")) {
          if(st.top() == "+") {
            int nums1 = cur;
            st.pop();
            int nums2 = Stoi(st.top());
            st.pop();
            cur = (nums1 + nums2) % M;
          }
          else {
            int nums1 = cur;
            st.pop();
            int nums2 = Stoi(st.top());
            st.pop();
            cur = (nums2 - nums1 + M) % M;
          }
        }
        st.push(to_string(cur));
      }
    }
    else {
      if(v[i] == ")") {
        string nums = st.top();
        st.pop();
        st.pop();
        st.push(nums);
        int cur = Stoi(nums);
        st.pop();
        while(st.size() && st.top() == "*") {
          int nums1 = cur;
          st.pop();
          int nums2 = Stoi(st.top());
          st.pop();
          cur = (nums1 * nums2) % M;
        }
        st.push(to_string(cur));
        if(i+1 == v.size() || v[i+1] != "*") {
          int cur = Stoi(st.top()); 
          st.pop();
          while(st.size() && (st.top() == "+" || st.top() == "-")) {
            if(st.top() == "+") {
              int nums1 = cur;
              st.pop();
              int nums2 = Stoi(st.top());
              st.pop();
              cur = (nums1 + nums2) % M;
            }
            else {
              int nums1 = cur;
              st.pop();
              int nums2 = Stoi(st.top());
              st.pop();
              cur = (nums2 - nums1 + M) % M;
            }
          }
          st.push(to_string(cur));
        }
      }
      else {
        st.push(v[i]);
      }
    }
  }
  return Stoi(st.top());
}
