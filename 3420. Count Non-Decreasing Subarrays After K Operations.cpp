class Solution {
public:
    long long countNonDecreasingSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        int LOG = 20;

        vector<int> nxt(n, n);
        stack<int> st;

        for (int i = n - 1; i >= 0; i--) {
            while (!st.empty() && nums[st.top()] <= nums[i])
                st.pop();

            if (!st.empty())
                nxt[i] = st.top();

            st.push(i);
        }

        vector<vector<int>> up(LOG, vector<int>(n + 1, n));
        vector<vector<long long>> sum(LOG, vector<long long>(n + 1, 0));

        vector<long long> pref(n + 1, 0);

        for (int i = 0; i < n; i++) {
            pref[i + 1] = pref[i] + nums[i];
            up[0][i] = nxt[i];
            sum[0][i] = 1LL * nums[i] * (nxt[i] - i);
        }

        for (int j = 1; j < LOG; j++) {
            for (int i = 0; i < n; i++) {
                int mid = up[j - 1][i];

                up[j][i] = up[j - 1][mid];
                sum[j][i] = sum[j - 1][i] + sum[j - 1][mid];
            }
        }

        auto getCost = [&](int l, int r) -> long long {
            long long total = 0;
            int cur = l;

            for (int j = LOG - 1; j >= 0; j--) {
                if (up[j][cur] <= r) {
                    total += sum[j][cur];
                    cur = up[j][cur];
                }
            }

            total += 1LL * nums[cur] * (r - cur + 1);

            return total - (pref[r + 1] - pref[l]);
        };

        long long ans = 0;

        for (int r = 0; r < n; r++) {
            int lo = 0, hi = r;

            while (lo < hi) {
                int mid = lo + (hi - lo) / 2;

                if (getCost(mid, r) <= k)
                    hi = mid;
                else
                    lo = mid + 1;
            }

            ans += r - lo + 1;
        }

        return ans;
    }
};
