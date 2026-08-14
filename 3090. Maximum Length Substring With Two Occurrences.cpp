class Solution {
public:
    int maximumLengthSubstring(string s) {
        vector<int> cnt(26, 0);
        int left = 0, ans = 0;

        for (int right = 0; right < s.size(); right++) {
            cnt[s[right] - 'a']++;

            while (cnt[s[right] - 'a'] > 2) {
                cnt[s[left] - 'a']--;
                left++;
            }

            ans = max(ans, right - left + 1);
        }

        return ans;
    }
};
