class Solution {
public:
    int uniquePaths(vector<vector<int>>& grid) {
        const int MOD = 1e9 + 7;
        int m = grid.size();
        int n = grid[0].size();

        vector<vector<int>> dp(m, vector<int>(n, 0));
        vector<vector<vector<int>>> memo(
            m, vector<vector<int>>(n, vector<int>(2, -2))
        );

        function<int(int, int, int)> go = [&](int r, int c, int dir) -> int {
            if (r >= m || c >= n)
                return -1;

            if (memo[r][c][dir] != -2)
                return memo[r][c][dir];

            if (grid[r][c] == 0)
                return memo[r][c][dir] = r * n + c;

            if (dir == 0)
                return memo[r][c][dir] = go(r + 1, c, 1);
            else
                return memo[r][c][dir] = go(r, c + 1, 0);
        };

        dp[0][0] = 1;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (dp[i][j] == 0 || grid[i][j] == 1)
                    continue;

                int right = go(i, j + 1, 0);
                int down = go(i + 1, j, 1);

                if (right != -1) {
                    int r = right / n;
                    int c = right % n;
                    dp[r][c] = (dp[r][c] + dp[i][j]) % MOD;
                }

                if (down != -1) {
                    int r = down / n;
                    int c = down % n;
                    dp[r][c] = (dp[r][c] + dp[i][j]) % MOD;
                }
            }
        }

        return dp[m - 1][n - 1];
    }
};
