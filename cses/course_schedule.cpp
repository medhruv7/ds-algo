// #include "common_headers.h"
#include "bits/stdc++.h"

using namespace std;
using ll = long long;

vector<vector<int>> adj;
vector<int> ans;
vector<int> col;

bool dfs(int v) {
    for(int x : adj[v]) {
        if(col[x] == 0) {
            col[x] = 1;
            dfs(x);
        }
        // cycle
        if(col[x] == 1) {
            return false;
        }
    }

    col[v] = 2;
    ans.push_back(v);
    return true;
}

int main() {
    int n,m;
    cin >> n >> m;
    adj.resize(n + 1);
    col.assign(n + 1, 0);

    for(int i = 0;i < m; ++i) {
        int a,b;
        cin >> a >> b;
        adj[a].push_back(b);
    }

    bool ok = true;

    for(int i= 1;i <= n; ++i) {
        if(col[i] == 0) {
            ok &= dfs(i);
        }
    }

    if(ok){
        reverse(ans.begin(), ans.end());

        for(int x : ans) {
            cout << x << ' ';
        }
    }else{
        cout << "IMPOSSIBLE";
    }

    return 0;
}
