class Solution {
public:
    double soupServings(int n) {
        if (n >= 4800) return 1.0;
        n = (n + 24) / 25; // Normalize to make operations manageable
        vector<vector<double>> dp(n + 1, vector<double>(n + 1, -1.0));
        return helper(n, n, dp);
    }
    
private:
    double helper(int a, int b, vector<vector<double>>& dp) {
        if (a <= 0 && b <= 0) return 0.5;
        if (a <= 0) return 1.0;
        if (b <= 0) return 0.0;
        if (dp[a][b] != -1.0) return dp[a][b];
        dp[a][b] = 0.25 * (helper(a - 4, b, dp) +
                          helper(a - 3, b - 1, dp) +
                          helper(a - 2, b - 2, dp) +
                          helper(a - 1, b - 3, dp));
        return dp[a][b];
    }
};
