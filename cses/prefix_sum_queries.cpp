// #include "common_headers.h"
#include "bits/stdc++.h"

using namespace std;
using ll = long long;

vector<ll> a;
vector<pair<ll,ll>> t;

struct seg_tree {
    seg_tree() {
        int n = a.size();
        t.resize(4*n + 1);
        build(1, 0, n - 1);
    }

    pair<ll,ll> combine(pair<ll,ll> &a, pair<ll,ll> &b) {
        pair<ll,ll> res;
        res.first = a.first + b.first;
        res.second = max(a.second, a.first + b.second);
        return res;
    }

    void build(int v,int tl, int tr) {
        if(tl == tr) {
            t[v].first = a[tl];
            t[v].second = max(a[tl], 0ll);
            return;
        }
        int tm = (tl + tr)>>1;
        build(v<<1, tl, tm);
        build(v<<1|1, tm + 1, tr);
        t[v] = combine(t[v<<1], t[v<<1|1]);
    }

    void update(int v,int tl, int tr, int idx,ll val) {
        if(tl == tr) {
            t[v].first = val;
            t[v].second = max(val, 0ll);
            return;
        }

        int tm = (tl + tr)>>1;
        if(idx <= tm) {
            update(v<<1, tl, tm, idx, val);
        }else{
            update(v<<1|1, tm + 1, tr, idx, val);
        }

        t[v] = combine(t[v<<1], t[v<<1|1]);
    }

    pair<ll,ll> query(int v, int tl, int tr, int l, int r){
        if(l > r) {
            return {0, 0};
        }

        if(tl == l && tr == r) {
            return t[v];
        }
        int tm = (tl + tr)>>1;
        pair<ll,ll> lv = query(v<<1, tl, tm, l, min(tm, r));
        pair<ll,ll> rv = query(v<<1|1, tm + 1, tr, max(l, tm + 1), r);
        return combine(lv, rv);
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
        int tp;
        cin >> tp;
        if(tp == 1) {
            int k,u;
            cin >> k >> u;
            st.update(1, 0, n - 1,k - 1, u);
        }else{
            int l,r;
            cin >> l >> r;
            cout << st.query(1, 0, n - 1, l - 1, r - 1).second << '\n';
        }
    }

    return 0;
}
