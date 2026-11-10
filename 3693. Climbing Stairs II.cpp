class Solution {
public:
    int climbStairs(int n, vector<int>& costs) {
        vector<long long> dp(n + 1, LLONG_MAX);

        dp[0] = 0;

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= 3; j++) {
                if (i - j >= 0) {
                    long long cost = dp[i - j] + costs[i - 1] + 1LL * j * j;
                    dp[i] = min(dp[i], cost);
                }
            }
        }

        return dp[n];
    }
};
