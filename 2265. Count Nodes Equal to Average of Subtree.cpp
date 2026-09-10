class Solution {
public:
    int ans = 0;

    pair<int, int> dfs(TreeNode* root) {
        if (!root)
            return {0, 0};

        auto L = dfs(root->left);
        auto R = dfs(root->right);

        int sum = L.first + R.first + root->val;
        int cnt = L.second + R.second + 1;

        if (root->val == sum / cnt)
            ans++;

        return {sum, cnt};
    }

    int averageOfSubtree(TreeNode* root) {
        dfs(root);
        return ans;
    }
};
