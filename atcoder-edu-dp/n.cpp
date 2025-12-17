// #include "common_headers.h"
#include "bits/stdc++.h"

using namespace std;
using ll = long long;

int main() {
    int n;
    cin >> n;
    vector<ll> a(n);
    vector<ll> pref(n + 1);
    for(int i = 0;i < n; ++i) {
        cin >> a[i];
        pref[i + 1] = pref[i] + a[i];
    }

    // dp[i][j] -> min cost of combining segments [i, j]
    ll inf = 1e18;

    vector<vector<ll>> dp(n + 1,vector<ll>(n + 1, inf));
    
    for(int i = 0;i <= n; ++i) {
        dp[i][i] = 0;
    }

    for(int l = 2; l <= n; ++l) {
        for(int j = 0;j < n; ++j) {
            int left = j;
            int right = left + l - 1;
            for(int cut = left; cut < right && right < n; cut++) {
                dp[left][right] = min(dp[left][right], dp[left][cut] + dp[cut + 1][right] + pref[right + 1] - pref[left]);
            }
        }
    }

    cout << dp[0][n - 1];
    
    return 0;
}
