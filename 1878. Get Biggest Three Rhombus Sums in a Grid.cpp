class Solution {
public:
    vector<int> getBiggestThree(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        set<int, greater<int>> s;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                s.insert(grid[i][j]); 

                for (int k = 1; i + 2 * k < m && j - k >= 0 && j + k < n; k++) {
                    int sum = 0;

                    int x = i, y = j;

                    for (int t = 0; t < k; t++) sum += grid[x + t][y + t];
                    for (int t = 0; t < k; t++) sum += grid[x + k + t][y + k - t];
                    for (int t = 0; t < k; t++) sum += grid[x + 2 * k - t][y - t];
                    for (int t = 0; t < k; t++) sum += grid[x + k - t][y - k + t];

                    s.insert(sum);
                }
            }
        }

        vector<int> ans;
        for (auto x : s) {
            ans.push_back(x);
            if (ans.size() == 3) break;
        }

        return ans;
    }
};
