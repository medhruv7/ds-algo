// #include "common_headers.h"
#include "bits/stdc++.h"

using namespace std;
using ll = long long;

ll cost(ll k, vector<ll> &h, vector<ll> &c) {
    int n = h.size();
    ll cost = 0;
    for(int i = 0;i < n; ++i) {
        cost += abs(h[i] - k)*c[i];
    }

    return cost;
}

int bin_search(vector<ll> &h, vector<ll> &c) {
    int n = h.size();
    ll maxi = 0, mini = 1e5;
    for(int i = 0;i < n; ++i) {
        maxi = max(maxi, h[i]);
        mini = min(mini, h[i]);
    }

    int l = mini, r = maxi;
    while(l <= r) {
        int m = l + (r - l)>>1;
        if((m + 1 < n) && (m - 1 >= 0)) {
            int cm = cost(m, h, c);
            int cl = cost(m - 1, h, c);
            int cr = cost(m + 1, h, c);
        }
    }
}

int main() {
    int tc;
    cin >> tc;

    while(tc--) {
        int n;
        cin >> n;
        vector<ll> a(n), c(n);
        for(int i = 0;i < n; ++i) {
            cin >> a[i];
        }
        for(int i = 0;i < n; ++i) {
            cin >> c[i];
        }
    }
    return 0;
}
