pair<long long, long long> exgcd(long long a, long long b) {
    //Finds a solution to ax + by = gcd(a, b)
    bool swp = 0;
    if(a < b) {
        swp = 1;
        swap(a, b);
    }
    if(b == 0) {
        if(swp) return {0, 1};
        return {1, 0};
    }
    pair<long long, long long> pre = exgcd(a%b, b);
    if(swp) return {pre.second - (a/b) * pre.first, pre.first};
    return {pre.first, pre.second - (a/b) * pre.first};
}
