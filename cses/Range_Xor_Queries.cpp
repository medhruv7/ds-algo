// #include "common_headers.h"
#include "bits/stdc++.h"

using namespace std;
using ll = long long;

int main() {
    int n, q;
    cin >> n >> q;
    vector<ll> a(n), pre(n + 1, 0);

    for(int i = 0;i < n; ++i) {
        cin >> a[i];
        pre[i + 1] = (pre[i]^a[i]);
    }

    while(q--) {
        int l,r;
        cin >> l >> r;
        cout << (pre[r]^pre[l - 1]) << '\n';
    }
    return 0;
}
