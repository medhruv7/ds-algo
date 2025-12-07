// #include "common_headers.h"
#include "bits/stdc++.h"

using namespace std;
using ll = long long;

const int inf = 1e9;
vector<vector<pair<int,int>>> adj;
vector<int> d;
vector<int> p;

void dijkstra(int s) {
    int n = adj.size();
    d.assign(n, inf);
    p.assign(n, -1);
    
    d[s] = 0;
    set<pair<int,int>> st;
    st.insert({0, s});

    while(!st.empty()) {
        int v = st.begin()->first;
        st.erase(st.begin());

        for(auto edge : adj[v]) {
            int to = edge.first;
            int len = edge.second;

            if(d[v] + len < d[to]) {
                st.erase({d[to], to});
                st.insert({d[v] + len, to});
                p[to] = v;
                d[to] = d[v] + len;
            }
        }
    }
}

int main() {
    
    return 0;
}
