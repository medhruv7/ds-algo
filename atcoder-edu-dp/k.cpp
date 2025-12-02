// #include "common_headers.h"
#include "bits/stdc++.h"

using namespace std;
using ll = long long;

int main() {
    int n,k;
    cin >> n >> k;
    vector<int> a(n);
    for(int i = 0;i < n; ++i) {
        cin >> a[i];
    }

    // dp[i] -> is i a winning position , meaning given a pile of i stones can we remove a stone from the array that forces the other person into a losing position

    // initially all positions are a losing position as we can't move to them
    vector<bool> dp(k + 1);

    for(int i = 1; i <= k; ++i){
        for(auto &x : a) {
            // meaning if we remove x stones from i the other player can never make a move in the next turn from any element in a
            if(i - x >= 0 && !dp[i - x]) {
                dp[i] = true;
            }
        }
    }

    if(dp[k]) {
        cout << "First";
    }else{
        cout << "Second";
    }
    return 0;
}
