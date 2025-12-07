    // #include "common_headers.h"
    #include "bits/stdc++.h"

    using namespace std;
    using ll = long long;

    const int mxn = 2e5 + 10;
    ll t[4*mxn], del[4*mxn], set_val[4*mxn];
    bool marked[4*mxn];

    void build(int v, int tl, int tr, vector<int>&a) {
        if(tl == tr) {
            t[v] = a[tr];
            return;
        }
        int tm = (tl + tr)>>1;
        build(2*v, tl, tm, a);
        build(2*v + 1, tm + 1, tr, a);
        t[v] = t[2*v] + t[2*v + 1];
    }

    // applies lazy to current node
    ll get_node(int v, int tl, int tr) {
        ll res = t[v];
        int len = (tr - tl + 1);
        if(marked[v]) {
            res = (set_val[v])*len;
        }
        res += (del[v])*len;

        return res;
    }

    // only lazy updates
    void push(int v, int tl, int tr) {
        if(tl == tr) {
            // leaf node
            return;
        }
        if(marked[v]) {
            set_val[2*v] = set_val[2*v + 1] = set_val[v];
            marked[2*v] = marked[2*v + 1] = true;
            marked[v] = false;

            del[2*v] = del[2*v + 1] = del[v];
            del[v] = 0;
        }
        else if(del[v] != 0) {
            del[2*v] += del[v];
            del[2*v + 1] += del[v];
            del[v] = 0;
        }

        // update the stale parent node as the lazy updates are lost
        int tm = (tl + tr)>>1;
        t[v] = get_node(2*v, tl, tm) + get_node(2*v + 1, tm + 1, tr);
    }

    // parent , current subtree and non invloved subtree will be up to date now
    void set_update(int v, int tl, int tr, int l, int r, int new_val) {
        if(l > r) {
            return;
        }

        if(l == tl && r == tr) {
            // only lazy updates
            marked[v] = true;
            set_val[v] = new_val;
            del[v] = 0;
            return;
        }

        push(v, tl, tr);

        int tm = (tl + tr)>>1;
        set_update(2*v, tl, tm, l, min(r, tm), new_val);
        set_update(2*v + 1, tm + 1, tr, max(tm + 1, l), r, new_val);

        t[v] = get_node(2*v, tl, tm) + get_node(2*v + 1, tm + 1, tr); 
    }

    // parent, current subtree and non involved subtree will be up to date now
    void set_del_update(int v,int tl, int tr, int l, int r, int delta) {
        if(l > r) {
            return;
        }

        if(tl == l && tr == r) {
            del[v] += delta;
            return;
        }

        // make children up to date as subtrees diverge
        push(v, tl, tr);

        int tm = (tl + tr)>>1;
        set_del_update(2*v, tl, tm, l, min(r, tm), delta);
        set_del_update(2*v + 1, tm + 1, tr, max(tm + 1, l), r, delta);

        t[v] = get_node(2*v, tl, tm) + get_node(2*v + 1, tm + 1, tr); 
    }

    ll query(int v, int tl, int tr, int l, int r) {
        if(l > r) {
            return 0;
        }

        if(tl == l && tr == r) {        
            return get_node(v, tl, tr);
        }

        // make children up to date as we need to apply the lazy values to actual node
        push(v, tl, tr);
        int tm = (tl + tr)>>1;

        return query(2*v, tl, tm, l, min(r, tm)) + query(2*v + 1, tm + 1, tr, max(l, tm + 1) , r);
    }

    void print(int n) {
        for(int i = 1;i <= 4*n; ++i) {
            cout << i << ' ' << t[i] << '\n';
        }
    }

    int main() {
        int n,q;
        cin >> n >> q;
        vector<int> a(n);
        for(int i = 0;i < n; ++i) {
            cin >> a[i];
        }

        build(1, 0, n - 1, a);
        // print(n);

        while(q--){
            int c;
            cin >> c;
            if(c == 1) {
                int aa,bb,xx;
                cin >> aa >> bb >> xx;
                --aa, --bb;
                set_del_update(1, 0, n - 1, aa, bb, xx);
            }else if(c == 2){
                int aa, bb, xx;
                cin >> aa >> bb >> xx;
                --aa, --bb;
                set_update(1, 0, n - 1, aa, bb, xx);
            }else {
                int aa,bb;
                cin >> aa >> bb;
                --aa, --bb;
                cout << query(1, 0, n - 1, aa, bb) << '\n';
            }

            // print(n);
        }
        return 0;
    }
