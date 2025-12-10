/*
    This is the version of the prims algorithm where the graph is sparse
    We do 2 operations in prim's , 
    first is to find the min edge from all the unmarked vertices to the MST 
    second is updating the min weights of unmarked vertices connected to this
    newly added vertex in MST

    first operation can be done in log(V) time using set
    second operation can be done in overall O(logE) time now which earlier
    in dense graph was O(n) overall and if we use set here to update then
    complexity becomes more which is O(n^2*logn) which earlier was O(n^2)

    so that gives the total complexity here as O(VlogV + VlogE)
*/

// #include "common_headers.h"
#include "bits/stdc++.h"

using namespace std;
using ll = long long;

const int INF = 1000000000;

struct Edge {
    int w = INF, to = -1;
    bool operator<(Edge const& other) const {
        return make_pair(w, to) < make_pair(other.w, other.to);
    }
};

int n;
vector<vector<Edge>> adj;

void prim() {
    int total_weight = 0;
    vector<Edge> min_e(n);
    min_e[0].w = 0;
    set<Edge> q;
    q.insert({0, 0});
    vector<bool> selected(n, false);
    for (int i = 0; i < n; ++i) {
        if (q.empty()) {
            cout << "No MST!" << endl;
            exit(0);
        }

        int v = q.begin()->to;
        selected[v] = true;
        total_weight += q.begin()->w;
        q.erase(q.begin());

        if (min_e[v].to != -1)
            cout << v << " " << min_e[v].to << endl;

        for (Edge e : adj[v]) {
            if (!selected[e.to] && e.w < min_e[e.to].w) {
                q.erase({min_e[e.to].w, e.to});
                min_e[e.to] = {e.w, v};
                q.insert({e.w, e.to});
            }
        }
    }

    cout << total_weight << endl;
}

int main() {
    
    return 0;
}
