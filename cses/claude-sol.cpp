#include "bits/stdc++.h"

using namespace std;
using ll = long long;

const int MAXN = 2e5 + 10;
ll t[4*MAXN], del[4*MAXN], set_val[4*MAXN];
bool marked[4*MAXN];

void build(int v, int tl, int tr, vector<ll>& a) {
    if(tl == tr) {
        t[v] = a[tl];
        return;
    }
    int tm = (tl + tr) >> 1;
    build(2*v, tl, tm, a);
    build(2*v + 1, tm + 1, tr, a);
    t[v] = t[2*v] + t[2*v + 1];
}

void push(int v, int tl, int tr) {
    if(tl == tr) return;  // Leaf node - nothing to push
    
    int tm = (tl + tr) >> 1;
    
    if(marked[v]) {
        // Propagate set operation
        set_val[2*v] = set_val[2*v + 1] = set_val[v];
        del[2*v] = del[2*v + 1] = del[v];
        marked[2*v] = marked[2*v + 1] = true;
        
        // Update children's t values
        t[2*v] = (tm - tl + 1) * (set_val[v] + del[v]);
        t[2*v + 1] = (tr - tm) * (set_val[v] + del[v]);
        
        // Clear parent's lazy values
        marked[v] = false;
        del[v] = 0;
    }
    else if(del[v] != 0) {
        // Propagate addition operation
        del[2*v] += del[v];
        del[2*v + 1] += del[v];
        
        t[2*v] += (tm - tl + 1) * del[v];
        t[2*v + 1] += (tr - tm) * del[v];
        
        del[v] = 0;
    }
}

void range_set(int v, int tl, int tr, int l, int r, ll val) {
    if(l > r) return;
    
    if(l == tl && r == tr) {
        set_val[v] = val;
        del[v] = 0;
        marked[v] = true;
        t[v] = (tr - tl + 1) * val;
        return;
    }
    
    push(v, tl, tr);
    
    int tm = (tl + tr) >> 1;
    range_set(2*v, tl, tm, l, min(r, tm), val);
    range_set(2*v + 1, tm + 1, tr, max(tm + 1, l), r, val);
    
    t[v] = t[2*v] + t[2*v + 1];
}

void range_add(int v, int tl, int tr, int l, int r, ll delta) {
    if(l > r) return;
    
    if(l == tl && r == tr) {
        del[v] += delta;
        t[v] += (tr - tl + 1) * delta;
        return;
    }
    
    push(v, tl, tr);
    
    int tm = (tl + tr) >> 1;
    range_add(2*v, tl, tm, l, min(r, tm), delta);
    range_add(2*v + 1, tm + 1, tr, max(tm + 1, l), r, delta);
    
    t[v] = t[2*v] + t[2*v + 1];
}

ll query(int v, int tl, int tr, int l, int r) {
    if(l > r) return 0;
    
    if(l == tl && r == tr) {
        // If there's a pending set operation, calculate from it
        if(marked[v]) {
            return (set_val[v] + del[v]) * (tr - tl + 1);
        }
        // Otherwise t[v] is up-to-date (del is applied in range_add base case)
        return t[v];
    }
    
    push(v, tl, tr);
    
    int tm = (tl + tr) >> 1;
    return query(2*v, tl, tm, l, min(r, tm)) + 
           query(2*v + 1, tm + 1, tr, max(l, tm + 1), r);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, q;
    cin >> n >> q;
    
    vector<ll> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    build(1, 0, n - 1, a);
    
    while(q--) {
        int type;
        cin >> type;
        
        if(type == 1) {
            // Range add
            int l, r;
            ll val;
            cin >> l >> r >> val;
            l--; r--;  // Convert to 0-indexed
            range_add(1, 0, n - 1, l, r, val);
        }
        else if(type == 2) {
            // Range set
            int l, r;
            ll val;
            cin >> l >> r >> val;
            l--; r--;
            range_set(1, 0, n - 1, l, r, val);
        }
        else {
            // Range query
            int l, r;
            cin >> l >> r;
            l--; r--;
            cout << query(1, 0, n - 1, l, r) << "\n";
        }
    }
    
    return 0;
}