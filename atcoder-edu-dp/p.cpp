// #include "common_headers.h"
#include "bits/stdc++.h"

using namespace std;
using ll = long long;

vector<vector<ll>> adj, dp;
const int mod = 1e9 + 7;

void dfs(int v, int p) {
    dp[v][0] = 1;
    dp[v][1] = 1;

    for(int nei : adj[v]) {
        if(nei != p) {
            dfs(nei, v);
            dp[v][0] *= (dp[nei][1]);
            dp[v][0] %= mod;

            dp[v][1] *= (dp[nei][1] + dp[nei][0]);
            dp[v][1] %= mod;
        }
    }
}

int main() {
    int n;
    cin >> n;
    adj.resize(n + 1);
    dp.resize(n + 1, vector<ll>(2));

    for(int i = 0;i < n - 1; ++i) {
        int x,y;
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    dfs(1, -1);

    cout << (dp[1][0] + dp[1][1])%mod << '\n';
    return 0;
}
