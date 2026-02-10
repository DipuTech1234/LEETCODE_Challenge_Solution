class Solution {
public:
    int longestBalanced(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;

        for (int l = 0; l < n; l++) {
            unordered_map<int,int> evenFreq, oddFreq;
            int distinctEven = 0, distinctOdd = 0;

            for (int r = l; r < n; r++) {
                int x = nums[r];
                if (x % 2 == 0) {
                    if (evenFreq[x]++ == 0) distinctEven++;
                } else {
                    if (oddFreq[x]++ == 0) distinctOdd++;
                }

                if (distinctEven == distinctOdd) {
                    ans = max(ans, r - l + 1);
                }
            }
        }
        return ans;
    }
};
