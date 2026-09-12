class Solution {
public:
    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();

        vector<array<long long, 4>> a(n);
        for (int i = 0; i < n; ++i) {
            a[i] = {intervals[i][0], intervals[i][1], intervals[i][2], i};
        }

        sort(a.begin(), a.end(), [](auto &x, auto &y) {
            if (x[1] != y[1]) return x[1] < y[1];
            return x[0] < y[0];
        });

        vector<int> ends(n);
        for (int i = 0; i < n; ++i)
            ends[i] = a[i][1];

        vector<array<long long, 5>> dp(n + 1);
        vector<array<vector<int>, 5>> path(n + 1);

        for (int i = 0; i <= n; ++i)
            for (int k = 0; k <= 4; ++k)
                dp[i][k] = (k == 0 ? 0 : LLONG_MIN);

        auto better = [](const vector<int>& x, const vector<int>& y) {
            if (y.empty()) return true;
            return x < y;
        };

        for (int i = 1; i <= n; ++i) {
            // Skip current interval
            for (int k = 0; k <= 4; ++k) {
                dp[i][k] = dp[i - 1][k];
                path[i][k] = path[i - 1][k];
            }

            int l = a[i - 1][0];

            // Find last interval whose right endpoint is strictly less than l
            int p = lower_bound(ends.begin(), ends.end(), l) - ends.begin();

            for (int k = 1; k <= 4; ++k) {
                if (dp[p][k - 1] == LLONG_MIN)
                    continue;

                long long val = dp[p][k - 1] + a[i - 1][2];
                vector<int> cur = path[p][k - 1];
                cur.push_back((int)a[i - 1][3]);
                sort(cur.begin(), cur.end());

                if (val > dp[i][k] ||
                    (val == dp[i][k] && better(cur, path[i][k]))) {
                    dp[i][k] = val;
                    path[i][k] = cur;
                }
            }
        }

        long long bestScore = LLONG_MIN;
        vector<int> ans;

        for (int k = 1; k <= 4; ++k) {
            if (dp[n][k] > bestScore ||
                (dp[n][k] == bestScore && better(path[n][k], ans))) {
                bestScore = dp[n][k];
                ans = path[n][k];
            }
        }

        return ans;
    }
};
