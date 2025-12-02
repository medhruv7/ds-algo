#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

int main() {
    int N;
    cin >> N;
    
    vector<int> count(4, 0);
    for (int i = 0; i < N; i++) {
        int a;
        cin >> a;
        count[a]++;
    }
    
    // DP table: dp[c1][c2][c3]
    vector<vector<vector<double>>> dp(N+1, vector<vector<double>>(N+1, vector<double>(N+1, 0.0)));
    
    // Calculate max total pieces
    int max_pieces = count[1] + 2 * count[2] + 3 * count[3];
    
    // Iterate in order of increasing total sushi pieces
    for (int total_pieces = 1; total_pieces <= max_pieces; total_pieces++) {
        for (int c3 = 0; c3 <= min(N, total_pieces / 3); c3++) {
            for (int c2 = 0; c2 <= min(N, (total_pieces - 3 * c3) / 2); c2++) {
                int c1 = total_pieces - 2 * c2 - 3 * c3;
                
                // Check if this is a valid state
                if (c1 < 0 || c1 > N || c1 + c2 + c3 > N) {
                    continue;
                }
                
                int total_dishes = c1 + c2 + c3;
                double result = (double)N / total_dishes;
                
                if (c1 > 0) {
                    result += (double)c1 / total_dishes * dp[c1-1][c2][c3];
                }
                if (c2 > 0) {
                    result += (double)c2 / total_dishes * dp[c1+1][c2-1][c3];
                }
                if (c3 > 0) {
                    result += (double)c3 / total_dishes * dp[c1][c2+1][c3-1];
                }
                
                dp[c1][c2][c3] = result;
            }
        }
    }
    
    cout << fixed << setprecision(10) << dp[count[1]][count[2]][count[3]] << endl;
    
    return 0;
}