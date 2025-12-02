// #include "common_headers.h"
#include "bits/stdc++.h"

using namespace std;
using ll = long long;

int main() {
    int n,w;
    cin >> n >> w;

    vector<int> wt(n), vl(n);

    for(int i = 0;i < n; ++i) {
        cin >> wt[i] >> vl[i];
    }
    
    // dp[i][j] = max value i can get if the knapsack weight is i and i have seen j elements till now
    vector<vector<ll> > dp(w + 1, vector<ll>(n + 1, 0));
    

    for(int i = 1; i <= w; ++i){
        for(int j = 1;j <= n; ++j) {
            dp[i][j] = dp[i][j - 1];
            if(wt[j - 1] <= i) {
                dp[i][j] = max(dp[i][j], dp[i - wt[j - 1]][j - 1] + vl[j - 1]);
            }
        }
    }

    // for(int i = 1;i <= w; ++i){
    //     for(int j = 0;j <= n; ++j) {
    //         cout << dp[i][j] << ' ';
    //     }
    //     cout << '\n';
    // }

    cout << dp[w][n];

    return 0;
}
