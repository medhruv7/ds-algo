#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    const int MOD = 1e9 + 7;
    
    // dp[i][j] = ways to distribute j candies among first i children
    vector<vector<ll>> dp(n + 1, vector<ll>(k + 1, 0));
    
    // Base case
    dp[0][0] = 1;
    
    // For each child
    for(int i = 1; i <= n; i++) {
        // Compute prefix sum for previous row
        vector<ll> prefix(k + 2, 0);
        for(int j = 0; j <= k; j++) {
            prefix[j+1] = (prefix[j] + dp[i-1][j]) % MOD;
        }
        
        // For each total number of candies
        for(int j = 0; j <= k; j++) {
            // We want: dp[i-1][j] + dp[i-1][j-1] + ... + dp[i-1][j-a[i-1]]
            // Which is: sum from index max(0, j-a[i-1]) to j
            int left = max(0, j - a[i-1]);
            int right = j;
            
            dp[i][j] = (prefix[right+1] - prefix[left] + MOD) % MOD;
        }
    }
    
    cout << dp[n][k] << endl;
    
    return 0;
}