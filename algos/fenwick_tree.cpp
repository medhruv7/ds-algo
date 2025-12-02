// #include "common_headers.h"
#include "bits/stdc++.h"

using namespace std;
using ll = long long;

struct Fenwick_tree {
    int n;
    vector<ll> tree;

    Fenwick_tree(int n) : n(n), tree(n + 1, 0) {};

    Fenwick_tree(vector<int> &arr) : n(arr.size()) , tree(arr.size() + 1) {
        for(int i = 0;i < n; ++i) {
            update(i, arr[i]);
        }
    };

    // update in [1, i]
    // point update
    void update(int i, ll delta) {
        // convert to 1 indexed
        i++;
        while(i <= n) {
            tree[i] += delta;
            // add last 1 bit significant bit
            // update all the segments that have responsibility of this cell
            i += (i&-i);
        }
    }

    // query from [1, n]
    // point query
    ll query(int r) {
        // convert to 1 indexed
        r++;
        ll ans = 0;
        while(r >= 1) {
            ans += tree[r];
            // move to prev parts of the tree where prev segments have their responsibility
            r -= (r&-r);
        }

        return ans;
    }

    // range query
    ll query(int l, int r) {
        if(l == 0) {
            return query(r);
        }

        return (query(r) - query(l - 1));
    }
};

int main() {
    
    return 0;
}
