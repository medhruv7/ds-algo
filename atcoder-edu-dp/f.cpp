// #include "common_headers.h"
#include "bits/stdc++.h"

using namespace std;
using ll = long long;

int main() {
    string s,t;
    cin >> s >> t;

    int n = s.size();
    int m = t.size();

    // dp[i][j] -> length of largest common subsequence of s and t given we have seen i elements of s and j elements of t
    vector<vector<int> > dp(n + 1, vector<int> (m + 1, 0));

    
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) {
            // the two strings are equal then always optimal to add them to a subsequence
            if(s[i - 1] == t[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }else{
                // try to match s to string behind t or t to string behind s
                dp[i][j] = max(dp[i - 1][j] , dp[i][j - 1]);
            }
        }
    }

    // cout << dp[n][m] << '\n';

    string lcs = "";
    int i = n,j = m;
    while(i > 0 && j > 0) {
        if(s[i - 1] == t[j - 1]) {
            lcs += s[i - 1];
            j--;
            i--;
        }else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        }else{
            j--;
        }
    }

    reverse(lcs.begin(), lcs.end());
    // for(int i = 0;i <= n; ++i){
    //     for(int j = 0;j <= m; ++j) {
    //         cout << dp[i][j] << ' ';
    //     }
    //     cout << '\n';
    // }
    cout << lcs;
    return 0;
}
