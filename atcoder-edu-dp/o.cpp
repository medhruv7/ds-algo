#include <bits/stdc++.h>
using namespace std;

struct SegTree {
    int n;
    vector<long long> tree;

    SegTree(int n) : n(n), tree(4 * n, 0) {}

    void update(int node, int start, int end, int idx, long long val) {
        if (start == end) {
            tree[node] = max(tree[node], val);
            return;
        }
        int mid = (start + end) / 2;
        if (idx <= mid)
            update(2 * node, start, mid, idx, val);
        else
            update(2 * node + 1, mid + 1, end, idx, val);

        tree[node] = max(tree[2 * node], tree[2 * node + 1]);
    }

    long long query(int node, int start, int end, int l, int r) {
        if (r < start || end < l)
            return 0;
        if (l <= start && end <= r)
            return tree[node];
        int mid = (start + end) / 2;
        return max(
            query(2 * node, start, mid, l, r),
            query(2 * node + 1, mid + 1, end, l, r)
        );
    }

    void update(int idx, long long val) {
        update(1, 1, n, idx, val);
    }

    long long query(int l, int r) {
        if (l > r) return 0;
        return query(1, 1, n, l, r);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<int> h(N);
    vector<long long> a(N);

    for (int i = 0; i < N; i++) cin >> h[i];
    for (int i = 0; i < N; i++) cin >> a[i];

    SegTree seg(N);

    for (int i = 0; i < N; i++) {
        long long best = seg.query(1, h[i] - 1);
        long long dp = best + a[i];
        seg.update(h[i], dp);
    }

    cout << seg.query(1, N) << "\n";
    return 0;
}
