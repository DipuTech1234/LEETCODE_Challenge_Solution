class Solution {
public:
    vector<vector<int>> constructProductMatrix(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        const int MOD = 12345;
        
        vector<int> arr;
        for (auto &row : grid)
            for (int x : row)
                arr.push_back(x % MOD);
        
        int size = arr.size();
        vector<int> prefix(size, 1), suffix(size, 1);
        
        for (int i = 1; i < size; i++)
            prefix[i] = (prefix[i - 1] * arr[i - 1]) % MOD;
        
        for (int i = size - 2; i >= 0; i--)
            suffix[i] = (suffix[i + 1] * arr[i + 1]) % MOD;
        
        vector<vector<int>> result(n, vector<int>(m));
        
        for (int i = 0; i < size; i++) {
            int val = (prefix[i] * suffix[i]) % MOD;
            result[i / m][i % m] = val;
        }
        
        return result;
    }
};
