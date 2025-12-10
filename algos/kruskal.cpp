// #include "common_headers.h"
#include "bits/stdc++.h"

using namespace std;
using ll = long long;

vector<int> parent, rnk;

void make_set(int v) {
    parent[v] = v;
    rnk[v] = 0;
}

int find_set(int v) {
    if(v == parent[v]) {
        return v;
    }
    parent[v] = find_set(parent[v]);
}

void union_set(int a, int b) {
    a = find_set(a);
    b = find_set(b);

    if(a != b) {
        if(rnk[a] < rnk[b]) {
            swap(a, b);
        }
        parent[b] = a;
        if(rnk[a] == rnk[b]) {
            rnk[a]++;
        }
    }
}

struct Edge {
    int u, v, weight;
    bool operator<(Edge const& other) {
        return weight < other.weight;
    }
};



void kruskal() {
    int n;
    vector<Edge> edges;
    int cost = 0;
    vector<Edge> result;
    parent.resize(n);   
    rnk.resize(n);

    for(int i = 0;i < n; ++i) {
        make_set(i);
    }

    sort(edges.begin(), edges.end());

    for(Edge e : edges) {
        if(find_set(e.u) != find_set(e.v)) {
            cost += e.weight;
            union_set(e.u, e.v);
            result.push_back(e);
        }
    }
}


int main() {
    
    return 0;
}
