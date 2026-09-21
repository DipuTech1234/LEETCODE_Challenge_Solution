class Solution {
public:
    vector<long long> resultArray(vector<int>& nums, int k) {
        vector<long long> ans(k, 0), dp(k, 0);

        for (int num : nums) {
            vector<long long> ndp(k, 0);
            int v = num % k;

            ndp[v]++;

            for (int r = 0; r < k; r++) {
                if (dp[r]) {
                    ndp[(r * v) % k] += dp[r];
                }
            }

            dp = ndp;

            for (int r = 0; r < k; r++) {
                ans[r] += dp[r];
            }
        }

        return ans;
    }
};
