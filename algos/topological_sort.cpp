// #include "common_headers.h"
#include "bits/stdc++.h"

using namespace std;
using ll = long long;

int n;
vector<vector<int>> adj;
vector<bool> vis;
vector<int> ans;

void dfs(int v) {
    vis[v] = true;

    for(auto x : adj[v]) {
        if(!vis[v]){
            dfs(x);
        }
    }

    ans.push_back(v);
}

void topo_sort() {
    vis.assign(n, false);
    ans.clear();

    for(int i = 0;i < n; ++i) {
        if(!vis[i]) {
            dfs(i);
        }
    }

    reverse(ans.begin(), ans.end());
}

int main() {

    return 0;
}
