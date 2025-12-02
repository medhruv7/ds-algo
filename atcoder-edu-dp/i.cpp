// #include "common_headers.h"
#include "bits/stdc++.h"

using namespace std;
using ll = long long;

int main() {
    int n;
    cin >> n;
    vector<double> a(n);

    // dp[i][j] -> probility of getting exactly i heads when we have seen j items
    vector<vector<double>> dp(n + 1, vector<double>(n + 1));

    for(int i = 0;i < n; ++i) {
        cin >> a[i];
    }

    dp[0][0] = 1;

    for(int i = 0; i <= n; ++i) {
        for(int j = 1; j <= n; ++j) {
            if(i == 0) {
                dp[i][j] = (dp[i][j - 1])*(1 - a[j - 1]);
            }else{
                // have heads here
                dp[i][j] = a[j - 1]*(dp[i - 1][j - 1]);
                // have tails here
                dp[i][j] += (1 - a[j - 1])*(dp[i][j - 1]);
            }
        }
    }

    double ans = 0;

    for(int i = 1; i <= n; ++i) {
        int heads = i;
        int tails = n - i;
        if(heads > tails) {
            ans += dp[i][n];
        }
    }

    cout << fixed << setprecision(10) << ans;
    return 0;
}
