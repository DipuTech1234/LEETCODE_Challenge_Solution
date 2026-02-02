class Solution {
public:
    long long minimumCost(vector<int>& nums, int k, int dist) {
        int n = nums.size();
        multiset<int> low, high;
        long long sumLow = 0;
        long long ans = LLONG_MAX;

        auto add = [&](int x) {
            if ((int)low.size() < k - 1) {
                low.insert(x);
                sumLow += x;
            } else if (!low.empty() && x < *prev(low.end())) {
                auto it = prev(low.end());
                sumLow -= *it;
                high.insert(*it);
                low.erase(it);
                low.insert(x);
                sumLow += x;
            } else {
                high.insert(x);
            }
        };

        auto remove = [&](int x) {
            auto itLow = low.find(x);
            if (itLow != low.end()) {
                sumLow -= x;
                low.erase(itLow);
                if (!high.empty()) {
                    auto it = high.begin();
                    low.insert(*it);
                    sumLow += *it;
                    high.erase(it);
                }
            } else {
                auto itHigh = high.find(x);
                if (itHigh != high.end()) high.erase(itHigh);
            }
        };

        for (int i = 1; i <= dist + 1 && i < n; i++) add(nums[i]);

        if ((int)low.size() == k - 1)
            ans = min(ans, nums[0] + sumLow);

        for (int i = dist + 2; i < n; i++) {
            remove(nums[i - dist - 1]);
            add(nums[i]);
            if ((int)low.size() == k - 1)
                ans = min(ans, nums[0] + sumLow);
        }

        return ans;
    }
};
