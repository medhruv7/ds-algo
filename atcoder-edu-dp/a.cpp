// #include "common_headers.h"
#include "bits/stdc++.h"

using namespace std;
using ll = long long;

int main() {
    int n,k;
    cin >> n >> k;
    vector<int> h(n);

    // dp[i] -> total cost to reach the ith stone
    vector<ll>  dp(n, 1e9 + 100);
    dp[0] = 0;

    for(int i = 0;i < n; ++i) cin >> h[i];

    for(int i = 1;i < n; ++i) {
        for(int j = 1; j <= k; ++j) {
            if(i - j >= 0) {
                dp[i] = min(dp[i], dp[i - j] + abs(h[i] - h[i - j]));
            }
        }
    }

    cout << dp[n - 1];

    return 0;
}
