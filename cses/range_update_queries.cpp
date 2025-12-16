// #include "common_headers.h"
#include "bits/stdc++.h"

using namespace std;
using ll = long long;

vector<ll> t, a;

struct seg_tree {
    seg_tree() {
        int n = a.size();
        t.assign(4*a.size(), 0);

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
    }

    void update(int v, int tl, int tr, int l, int r, int val) {
        if(l > r) {
            return;
        }
        if(tl == l && tr == r) {
            t[v] += val;
            return;
        }
        int tm = (tl + tr)>>1;
        update(v<<1, tl, tm, l, min(r, tm), val);
        update(v<<1|1, tm + 1, tr, max(l, tm + 1), r, val);
    }

    void query(int v, int tl, int tr, int pos, ll& ans) {
        ans += t[v];
        if(tl == tr) {
            return;
        }
        int tm = (tl + tr)>>1;
        if(pos <= tm) {
            query(v<<1, tl, tm, pos, ans);
        }else{
            query(v<<1|1, tm + 1, tr, pos, ans);
        }
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
            int a,b,u;
            cin >> a >> b >> u;
            --a, --b;
            st.update(1, 0, n - 1, a, b, u);
        }else{
            int k;
            cin >> k;
            ll ans = 0;
            --k;
            st.query(1, 0, n - 1, k, ans);
            cout << ans << '\n';
        }
    }
    return 0;
}
