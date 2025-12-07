// #include "common_headers.h"
#include "bits/stdc++.h"

using namespace std;
using ll = long long;

const int inf = 1e9;
vector<vector<pair<int,int>>> adj;

void dijkstra(int s, vector<int> &d, vector<int> &p) {
    int n = adj.size();
    d.assign(n, inf);
    p.assign(n, -1);
    vector<bool> u(n ,false);

    d[s] = 0;

    for(int i = 0;i < n; ++i) {
        int v = -1;
        for(int j = 0;j < n; ++j) {
            if(!u[j] && (v == -1 || d[j] < d[v])) {
                v = j;
            }
        }

        if(d[v] == inf) {
            break;
        }

        u[v] = true;
        for(auto x : adj[v]) {
            int to = x.first;
            int len = x.second;

            if(d[to] > d[v] + len) {
                d[to] = d[v] + len;
                p[to] = v;
            }
        }
    }
}

// restore path from s to t
vector<int> restore_path(int s, int t, vector<int> const& p) {
    vector<int> path;

    for (int v = t; v != s; v = p[v])
        path.push_back(v);
    path.push_back(s);

    reverse(path.begin(), path.end());
    return path;
}


int main() {
    
    return 0;
}
