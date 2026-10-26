class Solution {
public:
    int countIslands(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();
        int ans = 0;

        vector<vector<bool>> vis(m, vector<bool>(n, false));
        vector<pair<int, int>> dirs = {
            {1, 0}, {-1, 0}, {0, 1}, {0, -1}
        };

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 0 || vis[i][j])
                    continue;

                long long sum = 0;
                queue<pair<int, int>> q;
                q.push({i, j});
                vis[i][j] = true;

                while (!q.empty()) {
                    auto [x, y] = q.front();
                    q.pop();

                    sum += grid[x][y];

                    for (auto [dx, dy] : dirs) {
                        int nx = x + dx;
                        int ny = y + dy;

                        if (nx >= 0 && nx < m &&
                            ny >= 0 && ny < n &&
                            grid[nx][ny] > 0 &&
                            !vis[nx][ny]) {
                            vis[nx][ny] = true;
                            q.push({nx, ny});
                        }
                    }
                }

                if (sum % k == 0)
                    ans++;
            }
        }

        return ans;
    }
};
