class Solution {
public:
    int maxSumDivThree(vector<int>& nums) {
        vector<int> dp = {0, INT_MIN, INT_MIN};
        
        for (int num : nums) {
            vector<int> temp = dp;
            for (int i = 0; i < 3; i++) {
                if (dp[i] != INT_MIN) {
                    int newSum = dp[i] + num;
                    int rem = newSum % 3;
                    temp[rem] = max(temp[rem], newSum);
                }
            }
            dp = temp;
        }
        
        return dp[0];
    }
};
