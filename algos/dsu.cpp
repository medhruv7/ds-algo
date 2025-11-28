// #include "common_headers.h"
#include "bits/stdc++.h"

using namespace std;
using ll = long long;

const int N = 1e6;

int parent[N];
int sz[N];

int find_set(int v) {
    if(v == parent[v]) {
        return v;
    }

    return parent[v] = find_set(parent[v]);
}

void make_set(int v) {
    parent[v] = v;
}

void combine_set(int u, int v){
    int a = find_set(u);
    int b = find_set(v);

    if(a != b){
        if(sz[a] < sz[b]) {
            swap(a, b);
        }
        parent[b] = a;
        sz[a] += sz[b];
    }
}

int main() {
    
    return 0;
}
