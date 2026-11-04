class Solution {
public:
    long long minOperations(vector<int>& nums, int x, int k) {
        int n = nums.size();
        const long long INF = 1e18;

        multiset<int> low, high;
        long long sumLow = 0, sumHigh = 0;

        auto balance = [&]() {
            int target = (x + 1) / 2;

            while ((int)low.size() > target) {
                auto it = prev(low.end());
                int val = *it;
                low.erase(it);
                sumLow -= val;
                high.insert(val);
                sumHigh += val;
            }

            while ((int)low.size() < target && !high.empty()) {
                auto it = high.begin();
                int val = *it;
                high.erase(it);
                sumHigh -= val;
                low.insert(val);
                sumLow += val;
            }
        };

        auto add = [&](int val) {
            if (low.empty() || val <= *prev(low.end())) {
                low.insert(val);
                sumLow += val;
            } else {
                high.insert(val);
                sumHigh += val;
            }
            balance();
        };

        auto remove = [&](int val) {
            auto it = low.find(val);
            if (it != low.end()) {
                low.erase(it);
                sumLow -= val;
            } else {
                it = high.find(val);
                high.erase(it);
                sumHigh -= val;
            }
            balance();
        };

        vector<long long> cost(n - x + 1);

        for (int i = 0; i < x; i++) {
            add(nums[i]);
        }

        for (int i = 0; i <= n - x; i++) {
            long long median = *prev(low.end());

            cost[i] = median * (long long)low.size() - sumLow
                    + sumHigh - median * (long long)high.size();

            if (i < n - x) {
                remove(nums[i]);
                add(nums[i + x]);
            }
        }

        vector<long long> prev(n + 1, 0), curr(n + 1, INF);

        for (int j = 1; j <= k; j++) {
            fill(curr.begin(), curr.end(), INF);

            for (int i = 1; i <= n; i++) {
                curr[i] = curr[i - 1];

                if (i >= x && prev[i - x] != INF) {
                    curr[i] = min(curr[i],
                                  prev[i - x] + cost[i - x]);
                }
            }

            prev.swap(curr);
        }

        return prev[n];
    }
};
