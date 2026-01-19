class Solution {
public:
    int maxSideLength(vector<vector<int>>& mat, int threshold) {
        int m = mat.size();
        int n = mat[0].size();
        vector<vector<int>> prefixSum(m + 1, vector<int>(n + 1, 0));

        // Build 2D Prefix Sum table
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                prefixSum[i][j] = mat[i-1][j-1] + prefixSum[i-1][j] + 
                                  prefixSum[i][j-1] - prefixSum[i-1][j-1];
            }
        }

        int maxSide = 0;
        // Sliding window approach for side length
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                // Check if a square of (maxSide + 1) exists starting at (i, j)
                int s = maxSide + 1;
                if (i + s - 1 <= m && j + s - 1 <= n) {
                    int currentSum = prefixSum[i+s-1][j+s-1] - prefixSum[i-1][j+s-1] - 
                                     prefixSum[i+s-1][j-1] + prefixSum[i-1][j-1];
                    
                    if (currentSum <= threshold) {
                        maxSide++; // Increase current best side length
                    }
                }
            }
        }
        return maxSide;
    }
};
