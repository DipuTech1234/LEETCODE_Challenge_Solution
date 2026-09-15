class Solution {
public:
    int maxPalindromes(string s, int k) {
        int n = s.size();
        vector<vector<bool>> dp(n, vector<bool>(n, false));

        for (int i = n - 1; i >= 0; --i) {
            for (int j = i; j < n; ++j) {
                if (s[i] == s[j] && (j - i <= 1 || dp[i + 1][j - 1]))
                    dp[i][j] = true;
            }
        }

        int ans = 0;
        int lastEnd = -1;

        for (int end = 0; end < n; ++end) {
            for (int start = lastEnd + 1; start <= end - k + 1; ++start) {
                if (dp[start][end]) {
                    ++ans;
                    lastEnd = end;
                    break;
                }
            }
        }

        return ans;
    }
};
