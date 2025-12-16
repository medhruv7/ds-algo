// #include "common_headers.h"
#include "bits/stdc++.h"

using namespace std;
using ll = long long;

vector<ll> t;
vector<int> a;

struct seg_tree {
    int n;
    seg_tree() {
        n = a.size();
        t.assign(4*n + 1, 0);
        build(1, 0, n - 1);
    }

    void build(int v, int tl, int tr) {
        if(tl == tr) {
            t[v] = a[tl];
            return;
        }

        int tm = (tl + tr)>>1;

        build(v<<1, tl, tm);
        build(v<<1|1, tm + 1, tr);

        t[v] = t[v<<1] + t[v<<1|1];
    }

    ll query(int v, int tl, int tr, int l, int r) {
        if(l > r) {
            return 0;
        }
        if(l == tl && r == tr) {
            return t[v];
        }
        int tm = (tl + tr)>>1;
        return query(v << 1, tl, tm, l, min(r, tm)) +  
               query(v << 1 | 1, tm + 1, tr, max(l, tm + 1), r);
    }

    void update(int v,int tl, int tr, int pos, int val) {
        if(tl == tr) {
            t[v] = val;
            return;
        }
        int tm = (tl + tr)>>1;
        if(pos <= tm) {
            update(v<<1, tl, tm, pos, val);
        }else{
            update(v<<1|1, tm + 1, tr, pos, val);
        }
        t[v] = t[v<<1] + t[v<<1|1];
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
        int a;
        cin >> a;
        if(a == 1) {
            int pos, val;
            cin >> pos >> val;
            st.update(1, 0, n - 1, pos - 1, val);
        }else{
            int l,r;
            cin >> l >> r;
            cout << st.query(1, 0, n - 1, l - 1, r - 1) << '\n';
        }
    }
    return 0;
}
