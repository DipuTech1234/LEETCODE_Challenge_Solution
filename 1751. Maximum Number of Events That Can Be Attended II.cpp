class Solution {
public:
    int maxValue(vector<vector<int>>& events, int k) {
        int n = events.size();
        sort(events.begin(), events.end());
        vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));
        
        for (int i = n - 1; i >= 0; --i) {
            for (int j = 1; j <= k; ++j) {
                int next_event = -1;
                int low = i + 1, high = n - 1;
                while (low <= high) {
                    int mid = low + (high - low) / 2;
                    if (events[mid][0] > events[i][1]) {
                        next_event = mid;
                        high = mid - 1;
                    } else {
                        low = mid + 1;
                    }
                }
                int take = events[i][2] + (next_event == -1 ? 0 : dp[next_event][j - 1]);
                int not_take = dp[i + 1][j];
                dp[i][j] = max(take, not_take);
            }
        }
        
        return dp[0][k];
    }
};
