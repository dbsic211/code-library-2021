//Complexity: O(max(|a|, |b|))

string binAdd(string a, string b) { 
    string result = ""; int s = 0;
    int i = a.size()-1, j = b.size()-1;
    while(i >= 0 || j >= 0 || s == 1) {
        s += ((i>=0 ? a[i] - '0':0));
        s += ((j>=0 ? b[j] - '0':0));
        result += char(s%2 + '0');
        s /= 2;
        i--, j--;
    }
    reverse(result.begin(), result.end());
    return result;
}

string binSub(string a, string b) { //a >= b must hold
    string result = ""; int s = 0;
    int i = a.size()-1, j = b.size()-1;
    while(i >= 0 || j >= 0 || s != 0) {
        s += ((i>=0 ? a[i] - '0':0));
        s -= ((j>=0 ? b[j] - '0':0));
        result += char(abs(s)%2 + '0');
        if(s >= 0) s /= 2;
        else s = (s-1) / 2;
        i--, j--;
    }
    while(result.size() > 1 && result[result.size() - 1] == '0') {
        result.erase(result.size() - 1, 1);
    }
    reverse(result.begin(), result.end());
    return result;
}
