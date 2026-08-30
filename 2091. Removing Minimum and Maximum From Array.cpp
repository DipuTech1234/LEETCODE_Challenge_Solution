class Solution {
public:
    int minimumDeletions(vector<int>& nums) {
        int n = nums.size();
        
        int minIdx = 0, maxIdx = 0;
        
        for (int i = 0; i < n; i++) {
            if (nums[i] < nums[minIdx])
                minIdx = i;
            if (nums[i] > nums[maxIdx])
                maxIdx = i;
        }
        
        int a = min(minIdx, maxIdx);
        int b = max(minIdx, maxIdx);
        
        int fromFront = b + 1;
        int fromBack = n - a;
        int oneFrontOneBack = (a + 1) + (n - b);
        
        return min({fromFront, fromBack, oneFrontOneBack});
    }
};
