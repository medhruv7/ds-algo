// AKBAR - Akbar , The great problem


// #include "common_headers.h"
#include "bits/stdc++.h"

using namespace std;
using ll = long long;

void solve() {
    int n,r,m;
    cin >> n >> r >> m;
    vector<int> adj[n + 1];
    for(int i = 0;i < r; ++i) {
        int a,b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<pair<int,int>> sol(m);
    for(int i = 0;i < m; ++i) {
        cin >> sol[i].first >> sol[i].second;
    }

    vector<int> covered(n + 1);

    for(int i = 0;i < m; ++i) {
        queue<pair<int,int>> q;
        q.push({sol[i].first, 0});
        vector<bool> used(n + 1);
        used[sol[i].first] = true;
        while(!q.empty()) {
            auto ff = q.front();
            q.pop();
            int dis = ff.second;
            if(dis > sol[i].second) {
                continue;
            }
            int cur_node = ff.first;
            // cout << "debug";
            // cout << i << ' ' << cur_node << ' ' << dis << '\n';
            covered[cur_node]++;
            for(int neighbor : adj[cur_node]) {
                if(!used[neighbor]){
                    q.push({neighbor, dis + 1});
                    used[neighbor] = true;
                }
            }
        }
    }

    for(int i = 1; i <= n; ++i) {
        if(covered[i] != 1) {
            cout << "No" << endl;
            return;
        }
    }

    cout << "Yes" << endl;
}

int main() {
    int tc;
    cin >> tc;
    while(tc--) {
        solve();
    }
    return 0;
}
