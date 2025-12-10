// #include "common_headers.h"
#include "bits/stdc++.h"

using namespace std;
using ll = long long;

struct LCA {
    vector<int> height, euler, first, segtree;
    vector<bool> visited;
    int n;

    LCA(vector<vector<int>> &adj, int root = 0) {
        n = adj.size();
        height.resize(n);
        first.resize(n);
        euler.reserve(n*2);
        visited.assign(n, false);
        dfs(adj, root);
        int m = euler.size();
        segtree.resize(4*m);
        build(1, 0, m - 1);
    }

    void dfs(vector<vector<int>> &adj, int node, int h = 0) {
        visited[node] = true;
        height[node] = h;
        first[node] = euler.size();
        euler.push_back(node);
        for(auto to : adj[node]) {
            if(!visited[to]) {
                dfs(adj, to, h + 1);
                euler.push_back(node);
            }
        }
    }

    void build(int node, int l, int r) {
        if(l == r) {
            segtree[node] = euler[l];
        }else{
            int mid = (l + r)>>1;
            build(node<<1, l, mid);
            build(node<<1|1, mid + 1, r);
            int left = segtree[node<<1];
            int right = segtree[node<<1|1];
            segtree[node] = (height[left] < height[right]) ? left : right;
        }
    }

    int query(int node, int tl, int tr, int l, int r) {
        if(l > r) {
            return -1;
        }
        if(l == tl && r == tr) {
            return segtree[node];
        }

        int tm = (tl + tr)>>1;
        int left = query(node<<1, tl, tm, l, min(r, tm));
        int right = query(node<<1|1, tm + 1, tr, max(tm + 1, l), r);
        if(left == -1) return right;
        if(right == -1) return left;
        return (height[left] < height[right]) ? left : right;
    }

    int lca(int a, int b) {
        int left = first[a];
        int right = first[b];
        if(left > right) {
            swap(left, right);
        }

        return query(1, 0, euler.size() - 1, left, right);
    }
};

int main() {
    
    return 0;
}
