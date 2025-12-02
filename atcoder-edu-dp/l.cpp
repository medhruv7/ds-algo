// #include "common_headers.h"
#include "bits/stdc++.h"

using namespace std;
using ll = long long;

int main() {
    int n;
    cin >> n;
    vector<ll> a(n);
    for(int i = 0;i < n; ++i) {
        cin >> a[i];
    }

    vector<vector<ll>> dp(n, vector<ll>(n));

    // dp[i][j] -> max value i can get for X - Y in interval [i, j] both inclusive

    for(int L = n - 1; L >= 0; --L) {
        for(int R = L; R < n; R++) {
            if(L == R) {
                dp[L][R] = a[L];
            }else{
                dp[L][R] = max(a[L] - dp[L + 1][R], a[R] - dp[L][R - 1]);
            }
        }
    }

    cout << dp[0][n - 1];
    return 0;
}
