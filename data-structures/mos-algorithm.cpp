//Block should be around sqrt(n)

//If answer is NOT a single integer, change the ans array and output.

//All variables are related to block and query range except for the ans array.

int block;
bool cmp(pair<pair<int, int>, int> a,pair<pair<int, int>, int> b) {
    if(a.first.first / block != b.first.first / block) return a.first.first / block < b.first.first / block;
    return a.first.second < b.first.second;
}
bool cmp2(pair<int, int> a,pair<int, int> b) {
    return a.second < b.second;
}
void solve(int tc) {
    int n, q; 
    cin >> n >> q;
    block = ceil(sqrt(n));
    pair<pair<int, int>, int> b[q];
    for(int i=0; i<q; i++) {
        cin >> b[i].first.first >> b[i].first.second;
        b[i].second = i;
    }
    pair<long long, int> ans[q];
    sort(b, b+q, cmp);
    for(int i=0; i<q; i++) {
        ans[i].second = b[i].second;
    }
    //Naively compute answer to first query
    for(int i=b[0].first.first; i<=b[0].first.second; i++) {
        
    }
    //Mo's algorithm on remaining queries
    for(int i=1; i<q; i++) {
        while(b[i].first.first > b[i-1].first.first) {
            //Delete the contribution from b[i-1].first.first to answer
            
            b[i-1].first.first++;
        }
        while(b[i].first.first < b[i-1].first.first) {
             b[i-1].first.first--;
            //Add the contribution from new b[i-1].first.first to answer
            
        }
        while(b[i].first.second < b[i-1].first.second) {
            //Delete the contribution from b[i-1].first.second to answer
            
            b[i-1].first.second--;
        }
        while(b[i].first.second > b[i-1].first.second) {
             b[i-1].first.second++;
            //Add the contribution from new b[i-1].first.second to answer
            
        }
    }
    sort(ans, ans+q, cmp2);
    for(int i=0; i<q; i++) {
        cout << ans[i].first << endl;
    }
}
