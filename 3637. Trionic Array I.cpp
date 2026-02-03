class Solution {
public:
    bool isTrionic(vector<int>& nums) {
        int n = nums.size();
        if (n < 3) return false;

        int i = 0;

        // first strictly increasing
        while (i + 1 < n && nums[i] < nums[i + 1]) i++;
        if (i == 0 || i == n - 1) return false;

        // strictly decreasing
        int j = i;
        while (j + 1 < n && nums[j] > nums[j + 1]) j++;
        if (j == i || j == n - 1) return false;

        // strictly increasing
        int k = j;
        while (k + 1 < n && nums[k] < nums[k + 1]) k++;

        return k == n - 1;
    }
};
