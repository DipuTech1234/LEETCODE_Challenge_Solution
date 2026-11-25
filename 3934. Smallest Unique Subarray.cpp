class Solution {
public:
    int smallestUniqueSubarray(vector<int>& nums) {
        int n = nums.size();

        vector<int> sa(n), rank(n), temp(n);

        for (int i = 0; i < n; i++) {
            sa[i] = i;
            rank[i] = nums[i];
        }

        // Build Suffix Array
        for (int k = 1; k < n; k *= 2) {
            sort(sa.begin(), sa.end(), [&](int a, int b) {
                if (rank[a] != rank[b])
                    return rank[a] < rank[b];

                int x = (a + k < n) ? rank[a + k] : -1;
                int y = (b + k < n) ? rank[b + k] : -1;

                return x < y;
            });

            temp[sa[0]] = 0;

            for (int i = 1; i < n; i++) {
                int a = sa[i - 1];
                int b = sa[i];

                temp[b] = temp[a] +
                    (rank[a] != rank[b] ||
                     (a + k < n ? rank[a + k] : -1) !=
                     (b + k < n ? rank[b + k] : -1));
            }

            rank = temp;

            if (rank[sa[n - 1]] == n - 1)
                break;
        }

        // Build LCP Array using Kasai's Algorithm
        vector<int> pos(n), lcp(n, 0);

        for (int i = 0; i < n; i++)
            pos[sa[i]] = i;

        int h = 0;

        for (int i = 0; i < n; i++) {
            int r = pos[i];

            if (r == 0)
                continue;

            int j = sa[r - 1];

            while (i + h < n && j + h < n &&
                   nums[i + h] == nums[j + h]) {
                h++;
            }

            lcp[r] = h;

            if (h > 0)
                h--;
        }

        // Find the minimum unique subarray length
        int ans = n + 1;

        for (int i = 0; i < n; i++) {
            int r = pos[i];

            int mx = 0;

            if (r > 0)
                mx = max(mx, lcp[r]);

            if (r + 1 < n)
                mx = max(mx, lcp[r + 1]);

            int len = mx + 1;

            if (len <= n - i)
                ans = min(ans, len);
        }

        return ans;
    }
};
