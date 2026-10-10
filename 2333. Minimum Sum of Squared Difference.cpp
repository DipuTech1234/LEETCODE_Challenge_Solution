class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2, int k1, int k2) {
        long long k = (long long)k1 + k2;
        vector<int> diff(nums1.size());

        long long sum = 0;
        for (int i = 0; i < nums1.size(); i++) {
            diff[i] = abs(nums1[i] - nums2[i]);
            sum += diff[i];
        }

        if (k >= sum) {
            return 0;
        }

        int maxDiff = *max_element(diff.begin(), diff.end());
        vector<long long> freq(maxDiff + 1, 0);

        for (int d : diff) {
            freq[d]++;
        }

        for (int d = maxDiff; d > 0 && k > 0; d--) {
            long long count = freq[d];
            long long use = min(k, count);

            freq[d] -= use;
            freq[d - 1] += use;
            k -= use;
        }

        long long ans = 0;
        for (int d = 0; d <= maxDiff; d++) {
            ans += freq[d] * d * d;
        }

        return ans;
    }
};
