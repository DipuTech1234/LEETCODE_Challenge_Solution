class Solution {
public:
    int longestSubsequence(vector<int>& nums) {
        int xr = 0;
        bool nonZero = false;

        for (int x : nums) {
            xr ^= x;
            if (x != 0) nonZero = true;
        }

        if (xr != 0) return nums.size();
        if (nonZero) return nums.size() - 1;
        return 0;
    }
};
