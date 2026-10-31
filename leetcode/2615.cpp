class Solution {
public:
    vector<long long> distance(vector<int>& nums) {
        unordered_map<int, vector<int>> groups;
        for(int i = 0;i < nums.size(); ++i) {
            groups[nums[i]].push_back(i);
        }

        vector<long long> res(nums.size(), 0);

        for(auto& [k, idxs] : groups) {
            long long pref = 0;
            long long total = 0;

            for(auto idx : idxs) {
                total += idx;
            }

            long long isz = idxs.size();

            for(int t = 0;t < isz; t++) {
                long long cur = idxs[t];

                long long left = cur * t - pref;

                long long suff = total - pref - cur;
                long long right = suff - (1LL*isz - t - 1)*cur;

                res[cur] = left + right;
                pref += cur;
            }
        }

        return res;
    }
};
