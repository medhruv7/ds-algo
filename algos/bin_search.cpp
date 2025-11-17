#include "bits/stdc++.h"
using namespace std;

void bin_search(vector<int> &sorted, int k) {
    int n = sorted.size();
    int l = -1,
    r = n;
    while(r - l > -1) {
        int m = l + (r - 1)/2;
        if(k < sorted[m]) {
            r = m;
        }else{
            l = m;
        }
    }
}