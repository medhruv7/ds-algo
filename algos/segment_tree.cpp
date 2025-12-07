// #include "common_headers.h"
#include "bits/stdc++.h"

using namespace std;
using ll = long long;

const int MAXN = 1e5;

int n, t[4*MAXN];
bool marked[4*MAXN];

struct Segtree {
    Segtree(int nn, vector<int> &a) {
        int n = a.size();
        fill(t, t + 4*n + 2, 0);
        fill(marked, marked + 4*n + 2, false);
        build(a, 0, n - 1, 1);
    }

    void build(vector<int> &a, int l, int r, int v) {
        if(l == r) {
            t[v] = a[l];
            return;
        }
        int m = (l + r) >> 1;
        build(a, l, m, 2*v);
        build(a, m + 1, r, 2*v + 1);
        t[v] = t[2*v] + t[2*v + 1];
    }

    int sum(int v, int tl, int tr, int l, int r) {
        if(l > r) {
            return 0;
        }
        if(l == tl && r == tr) {
            return t[v];   
        }

        int m = (tl + tr)>>1;
        return sum(2*v, tl, m, l, min(m, r)) + sum(2*v + 1, m + 1, tr, max(m + 1, l), r);
    }

    void update(int v,int tl,int tr, int pos, int val) {
        if(tl == tr) {
            t[v] = val;
            return;
        }
        int m = (tl + tr) >> 1;
        if(pos <= m) {
            update(2*v, tl, m, pos, val);
        }else{
            update(2*v + 1, m + 1, tr, pos, val);
        }
        t[v] = t[2*v] + t[2*v + 1];
    }

    void push(int v) {
        if(marked[v]) {
            t[v*2] = t[v*2 + 1] = t[v];
            marked[v*2] = marked[v*2 + 1] = true;
            marked[v] = false;
        }
    }

    void range_update(int v, int tl, int tr, int l, int r, int new_val) {
        if(l > r) {
            return;
        } 
        if(l == tl && r == tr) {
            t[v] = new_val;
            marked[v] = true;
            return;
        }

        push(v);
        int tm = (l + r)>>1;
        range_update(2*v, tl, tm, l, min(r, tm), new_val);
        range_update(2*v, tm + 1, tr, max(l, tm + 1), r, new_val);
    }

    int get_point(int pos,int v, int tl, int tr) {
        if(tl == tr) {
            return t[v];
        }
        push(v);
        int tm = (tl + tr)>>1;
        if(pos <= tm) {
            return get_point(pos, 2*v, tl, tm);
        }else{
            return get_point(pos, 2*v + 1, tm + 1,tr);
        }
    }
};

int main() {
    
    return 0;
}
