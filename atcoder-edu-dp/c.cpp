// #include "common_headers.h"
#include "bits/stdc++.h"

using namespace std;
using ll = long long;

int main() {
    int n;
    cin >> n;

    vector<ll> dp(3, 0), dp2(3, 0);

    // dp[i] -> happiness today if ith activity was chosen
    // dp2[i] -> happiness yesterday if ith activity was chose

    for(int i = 0;i < n; ++i) {
        int a,b,c;
        cin >> a >> b >> c;
        if(i == 0) {
            dp[0] = a;
            dp[1] = b;
            dp[2] = c;
        }else{
            dp[0] = max(dp2[1], dp2[2]) + a;
            dp[1] = max(dp2[0], dp2[2]) + b;
            dp[2] = max(dp2[0], dp2[1]) + c;
        }

        for(int j = 0;j < 3; ++j) {
            dp2[j] = dp[j];
            dp[j] = 0;
        }
    }

    cout << max({dp2[0], dp2[1], dp2[2]});

    return 0;
}
