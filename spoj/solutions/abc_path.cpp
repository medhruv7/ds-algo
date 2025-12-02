//ABCPATH - ABC Path

  #include "bits/stdc++.h"
  using namespace std;

  int H, W;
  vector<string> grid;
  int dp[55][55];
  int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
  int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

  bool isValid(int x, int y) {
      return x >= 0 && x < H && y >= 0 && y < W;
  }

  int dfs(int x, int y) {
      // If already computed, return stored result
      if(dp[x][y] != -1) {
          return dp[x][y];
      }

      // Current cell contributes 1 to the path length
      dp[x][y] = 1;

      char currentChar = grid[x][y];
      char nextChar = currentChar + 1;

      // Try all 8 directions
      for(int i = 0; i < 8; i++) {
          int nx = x + dx[i];
          int ny = y + dy[i];

          if(isValid(nx, ny) && grid[nx][ny] == nextChar) {
              dp[x][y] = max(dp[x][y], 1 + dfs(nx, ny));
          }
      }

      return dp[x][y];
  }

  void solve(int caseNum) {
      cin >> H >> W;

      if(H == 0 && W == 0) {
          exit(0);
      }

      grid.clear();
      grid.resize(H);
      memset(dp, -1, sizeof(dp));

      for(int i = 0; i < H; i++) {
          cin >> grid[i];
      }

      int maxLen = 0;

      // Find all 'A' positions and start DFS from each
      for(int i = 0; i < H; i++) {
          for(int j = 0; j < W; j++) {
              if(grid[i][j] == 'A') {
                  maxLen = max(maxLen, dfs(i, j));
              }
          }
      }

      cout << "Case " << caseNum << ": " << maxLen << endl;
  }

  int main() {
      int caseNum = 1;
      while(true) {
          solve(caseNum++);
      }
      return 0;
  }
