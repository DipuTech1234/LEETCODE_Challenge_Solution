class Solution {
public:
    bool isZeroArray(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        vector<int> diff(n + 2, 0); 

      
        for (const auto& q : queries) {
            int l = q[0];
            int r = q[1];
            diff[l] += 1;
            if (r + 1 < n) {
                diff[r + 1] -= 1;
            }
        }

        
        int current = 0;
        for (int i = 0; i < n; ++i) {
            current += diff[i];
            if (current < nums[i]) {
                return false;
            }
        }

        return true;
    }
};
