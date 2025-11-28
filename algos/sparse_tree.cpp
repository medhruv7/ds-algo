// #include "common_headers.h"
#include "bits/stdc++.h"

using namespace std;
using ll = long long;

const int K = 25;
const int MAXN = 1e6;

int st[K + 1][MAXN];

int log2_floor(unsigned long long i) {
    return i ? __builtin_clzll(1) - __builtin_clzll(i) : -1;
}

void precompute(vector<int> &a) {  
    int n = a.size(); 

    for(int i = 0;i < n; ++i){
        st[0][i] = a[i];
    }

    for(int i = 1;i <= K; i++){
        for(int j = 0;j + (1 << (i)) - 1 < n; ++j) {
            st[i][j] = min(st[i - 1][j], st[i - 1][j + (1<<(i - 1))]);
        }
    }
}

int compute(vector<int> &a, int l, int r) {
    int res = 0;

    for(int i = K; i >= 0; --i) {
        if((1<<i) <= (r - l + 1)) {
            res += st[i][l];
            l += (1<<i);
        }
    }
}

int main() {
    
    return 0;
}
