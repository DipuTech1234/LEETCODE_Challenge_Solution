class Solution {
public:
    int minCost(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        vector<vector<bool>> reachable(1024, vector<bool>(m * n, false));
        reachable[grid[0][0]][0] = true;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (i == 0 && j == 0) continue;

                int idx = i * n + j;
                int val = grid[i][j];

                for (int x = 0; x < 1024; x++) {
                    if (i > 0 && reachable[x][(i - 1) * n + j]) {
                        reachable[x ^ val][idx] = true;
                    }
                    if (j > 0 && reachable[x][i * n + j - 1]) {
                        reachable[x ^ val][idx] = true;
                    }
                }
            }
        }

        for (int x = 0; x < 1024; x++) {
            if (reachable[x][m * n - 1]) return x;
        }

        return 0;
    }
};
