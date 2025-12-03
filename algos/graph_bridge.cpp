// #include "common_headers.h"
#include "bits/stdc++.h"

using namespace std;
using ll = long long;

const int MAXN = 1e3;

struct Edge {
    int v,id;

    Edge(int vv, int ii) {
        // destination
        v = vv;
        // unique id to prevent processing same edge
        id = ii;
    }
};

vector<Edge> adj[MAXN];
vector<pair<int,int>> bridges;
int low[MAXN], pre[MAXN];
int cnt = 0;

struct Graph {
    int n,m;

    Graph(int nn) {
        n = nn + 1;
        m = 0;
        for(int i = 0;i < n; ++i) {
            adj[i].clear();
        }

        fill(pre, pre + n, -1);
        fill(low, low + n, -1);

        bridges = vector<pair<int,int>>(0);
        cnt = 0;
    }

    void add(int i,int j) {
        Edge e1 = Edge(j, m);
        Edge e2 = Edge(i, m);
        adj[i].push_back(e1);
        adj[j].push_back(e2);
        m++;
    }
};

int find_bridges(int node , int p, int id) {
    
    // back edge
    if(pre[node] != -1) {
        return pre[node];
    }

    // forward edge so explore the tree and assign pre and low link same
    pre[node] = cnt++;
    low[node] = pre[node];

    // exploration
    for(Edge to : adj[node]) {
        // same back edge or self loop cases
        if(id == to.id) {
            continue;
        }

        // explore neighbors
        int pre_parent = find_bridges(to.v, node, to.id);

        if(pre_parent == -1) {
            // this came back from a forward edge
            low[node] = min(low[node], low[to.v]);

            // if this neighboring has low link value = pre value then no way to escape from edge to (node -> to.v)
            if(low[to.v] > pre[node]) {
                bridges.push_back({node, to.v});
            }
        }else{
            // this came back from a back edge
            low[node] = min(low[node], pre_parent);
        }
    }
    return -1;
}

void solve() {
    int n,m;
    cin >> n >> m;
    Graph g = Graph(n);
    for(int i = 0;i < m; ++i) {
        int a,b;
        cin >> a >> b;
        g.add(a,b);
    }

    for(int i = 1;i <= n; ++i) {
        if(pre[i] == -1) {
            find_bridges(i, -1, -1);
        }
    }

    if(bridges.size()) {
        cout << bridges.size() << '\n';
        for(int i = 0;i < bridges.size(); ++i) {
            cout << bridges[i].first << ' ' << bridges[i].second << '\n';
        }
    }else{
        cout << "Sin bloqueos" << '\n';
    }
}

int main() {
    int tc;
    cin >> tc;
    int ctr = 1;
    while(tc--) {
        cout << "Caso #" << ctr++ << '\n';
        solve();
    }
    return 0;
}
