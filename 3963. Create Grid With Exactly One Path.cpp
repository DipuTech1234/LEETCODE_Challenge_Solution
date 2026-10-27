class Solution {
public:
    vector<string> createGrid(int m, int n) {
        vector<string> grid(m, string(n, '#'));
        
        for (int c = 0; c < n; ++c) {
            grid[0][c] = '.';
        }
        
        for (int r = 0; r < m; ++r) {
            grid[r][n - 1] = '.';
        }
        
        return grid;
    }
};
