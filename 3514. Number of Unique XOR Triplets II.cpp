class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        const int MAXX = 2048;

        vector<bool> present(MAXX, false);
        for (int x : nums) present[x] = true;

        vector<vector<bool>> dp(4, vector<bool>(MAXX, false));
        dp[0][0] = true;

        for (int cnt = 0; cnt < 3; cnt++) {
            for (int xr = 0; xr < MAXX; xr++) {
                if (!dp[cnt][xr]) continue;
                for (int v = 0; v < MAXX; v++) {
                    if (present[v]) {
                        dp[cnt + 1][xr ^ v] = true;
                    }
                }
            }
        }

        int ans = 0;
        for (bool x : dp[3]) {
            if (x) ans++;
        }
        return ans;
    }
};
