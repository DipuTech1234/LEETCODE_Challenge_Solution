class Solution {
public:
    int maxProduct(TreeNode* root) {
        const int MOD = 1e9 + 7;
        vector<long> subtreeSums;
        
        // First DFS to compute total sum and all subtree sums
        function<long(TreeNode*)> dfs1 = [&](TreeNode* node) -> long {
            if (!node) return 0;
            long sum = node->val + dfs1(node->left) + dfs1(node->right);
            subtreeSums.push_back(sum);
            return sum;
        };
        
        long totalSum = dfs1(root);
        long maxProduct = 0;
        
        // For each subtree sum, calculate product and track maximum
        for (long sum : subtreeSums) {
            maxProduct = max(maxProduct, sum * (totalSum - sum));
        }
        
        return maxProduct % MOD;
    }
};
