// #include "common_headers.h"
#include "bits/stdc++.h"

using namespace std;
using ll = long long;

vector<vector<pair<int, ll>>> adj;
vector<vector<ll>> d;
const ll inf = 1e18;

void dijk(int s) {
    int n = adj.size();

    set<tuple<ll,ll, ll>> st;
    d[s][0] = 0;

    st.insert({0, s, 0});

    while(!st.empty()) {
        auto [_, v, state] = *st.begin();
        st.erase(st.begin());


        for(auto edge : adj[v]) {
            int to = edge.first;
            ll len = edge.second;

            // don't use coupon
            ll new_len = d[v][state] + len;

            if(d[to][state] > new_len) {
                st.erase({d[to][state], to, state});
                d[to][state] = new_len;
                st.insert({new_len, to, state});
            }

            // use coupon
            if(state == 0) {
                ll discounted = d[v][state] + len/2;

                if(d[to][1] > discounted) {
                    st.erase({d[to][1], to, 1});
                    d[to][1] = discounted;
                    st.insert({discounted, to, 1});
                }
            }
        }
    }
}

int main() {
    int n,m;
    cin >> n >> m;
    adj.resize(n + 1);
    d.assign(n + 1 , vector<ll>(2, inf));

    for(int i = 0;i < m; ++i) {
        int a,b;
        ll c;
        cin >> a >> b >> c;
        adj[a].push_back({b,c});
    }

    dijk(1);

    cout << min(d[n][0], d[n][1]);

    return 0;
}
