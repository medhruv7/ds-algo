// #include "common_headers.h"
#include "bits/stdc++.h"

using namespace std;
using ll = long long;

vector<ll> a;
vector<vector<ll>> t;

struct seg_tree {
    seg_tree() {
        int n = a.size();
        t.resize(4*n + 1);
        build(1, 0, n - 1);
    }

    vector<ll> combine(const vector<ll>& a, const vector<ll>& b) {
        if (a.empty()) return b;
        if (b.empty()) return a;

        vector<ll> res = a;
        ll mxa = a.back();

        for (ll x : b) {
            if (x > mxa) {
                res.push_back(x);
                mxa = x;
            }
        }
        return res;
    }

    void build(int v, int tl, int tr) {
        if (tl == tr) {
            t[v] = vector<ll>{a[tl]};
            return;
        }
        int tm = (tl + tr) >> 1;
        build(v<<1, tl, tm);
        build(v<<1|1, tm + 1, tr);
        t[v] = combine(t[v<<1], t[v<<1|1]);
    }

    vector<ll> query(int v, int tl, int tr, int l, int r) {
        if (l > r) return {};

        if (tl == l && tr == r)
            return t[v];

        int tm = (tl + tr) >> 1;
        return combine(
            query(v<<1, tl, tm, l, min(tm, r)),
            query(v<<1|1, tm + 1, tr, max(l, tm + 1), r)
        );
    }
};


int main() {
    int n,q;
    cin >> n >> q;
    a.resize(n);

    for(int i = 0;i < n; ++i) {
        cin >> a[i];
    }

    seg_tree st;

    while(q--) {
        int l,r;
        cin >> l >> r;
        cout << st.query(1, 0, n - 1, l - 1, r - 1).size() << '\n';
    }

    return 0;
}
