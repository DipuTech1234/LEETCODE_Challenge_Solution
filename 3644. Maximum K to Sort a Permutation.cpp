
class Solution {
public:
    int sortPermutation(vector<int>& nums) {
        int k = INT_MAX;
        bool sorted = true;

        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] != i) {
                k &= nums[i];
                sorted = false;
            }
        }

        return sorted ? 0 : k;
    }
};
