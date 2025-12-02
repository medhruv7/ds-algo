// #include "common_headers.h"
#include "bits/stdc++.h"

using namespace std;
using ll = long long;

int main() {
    int n,w;
    cin >> n >> w;
    vector<int> wt(n), vl(n);

    ll sm = 0;
    for(int i = 0;i < n; ++i) {
        cin >> wt[i] >> vl[i];
        sm += vl[i];
    }

    const int INF = 0;

    // dp[i][j] -> minimum weight to get to value i with j elements been seen
    vector<vector<int>> dp(sm + 1, vector<int> (n + 1, 1e9));

    for(int i = 0; i <= n; ++i) {
        dp[0][i] = 0;
    }

    for(int i = 1;i <= sm; ++i) {
        for(int j = 1; j <= n; ++j) {
            dp[i][j] = dp[i][j - 1];
            if(vl[j - 1] <= i) {
                dp[i][j] = min(dp[i][j], dp[i - vl[j - 1]][j - 1] + wt[j - 1]);
            }
        }
    }

    ll ans = 0;

    for(int i = 1;i <= sm; ++i) {
        if(dp[i][n] <= w) {
            ans = i;
        }
    }

    cout << ans;

    return 0;
}
