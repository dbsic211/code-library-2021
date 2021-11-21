struct line {
    int m, c;
    mutable function<const line*()> succ;
    bool operator<(const line& rhs) const {
        if (rhs.c != -(1ll<<62)) return m < rhs.m;
        const line* s = succ();
        if (!s) return 0;
        return c - s->c < (s->m - m) * rhs.m;
    }
};
struct convex_hull : public multiset<line> { 
    bool bad(iterator y) {
        auto z = next(y);
        auto x = prev(y);
        if (y == begin()) {
            if (z == end()) return 0;
            return y->m == z->m && y->c <= z->c;
        }
        else {
            if (z == end()) return y->m == x->m && y->c <= x->c;
            return (x->c - y->c)*(z->m - y->m) >= (y->c - z->c)*(y->m - x->m);
        }
    }
    void insert_line(int m, int c) {
        auto y = insert({m, c});
        y->succ = [=] { return next(y) == end() ? 0 : &*next(y); };
        if (bad(y)) { erase(y); return; }
        while (next(y) != end() && bad(next(y))) erase(next(y));
        while (y != begin() && bad(prev(y))) erase(prev(y));
    }
    int eval(int x) {
        auto l = *lower_bound((line) { x, -(1ll<<62)});
        return l.m * x + l.c;
    }
};
