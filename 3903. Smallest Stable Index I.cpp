class Solution {
public:
    int firstStableIndex(vector<int>& nums, int k) {
        int n = nums.size();
        int mx = nums[0];

        vector<int> suffixMin(n);
        suffixMin[n - 1] = nums[n - 1];

        for (int i = n - 2; i >= 0; --i)
            suffixMin[i] = min(suffixMin[i + 1], nums[i]);

        for (int i = 0; i < n; ++i) {
            mx = max(mx, nums[i]);
            if (mx - suffixMin[i] <= k)
                return i;
        }

        return -1;
    }
};
