class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums) {
        sort(nums.begin(), nums.end(), [](int a, int b) {
            return 1LL * a * a < 1LL * b * b;
        });

        int n = nums.size();
        long long ans = 0;

        for (int i = 0; i < n; i++) {
            long long x = nums[i];
            if (i < n / 2)
                ans -= x * x;
            else
                ans += x * x;
        }

        return ans;
    }
};
