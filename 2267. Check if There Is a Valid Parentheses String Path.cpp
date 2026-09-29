class Solution {
public:
    int m, n;
    vector<vector<vector<int>>> dp;

    bool dfs(vector<vector<char>>& grid, int r, int c, int bal) {
        if (r >= m || c >= n) return false;

        if (grid[r][c] == '(')
            bal++;
        else
            bal--;

        if (bal < 0) return false;

        int remaining = (m - 1 - r) + (n - 1 - c);

        if (bal > remaining) return false;

        if (r == m - 1 && c == n - 1)
            return bal == 0;

        if (dp[r][c][bal] != -1)
            return dp[r][c][bal];

        return dp[r][c][bal] =
            dfs(grid, r + 1, c, bal) ||
            dfs(grid, r, c + 1, bal);
    }

    bool hasValidPath(vector<vector<char>>& grid) {
        m = grid.size();
        n = grid[0].size();

        // Path length must be even.
        // Path length = m + n - 1
        if ((m + n) % 2 == 0)
            return false;

        dp.assign(m, vector<vector<int>>(n, vector<int>(m + n, -1)));

        return dfs(grid, 0, 0, 0);
    }
};
