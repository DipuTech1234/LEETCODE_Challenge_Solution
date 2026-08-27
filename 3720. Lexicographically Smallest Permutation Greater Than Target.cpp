class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        int n = s.size();
        int base[26] = {};

        for (char c : s)
            base[c - 'a']++;

        // Try changing the rightmost possible position.
        for (int i = n - 1; i >= 0; i--) {
            int cnt[26];

            for (int j = 0; j < 26; j++)
                cnt[j] = base[j];

            // Use characters of target[0...i-1].
            bool possible = true;

            for (int j = 0; j < i; j++) {
                int x = target[j] - 'a';

                if (cnt[x] == 0) {
                    possible = false;
                    break;
                }

                cnt[x]--;
            }

            if (!possible)
                continue;

            int cur = target[i] - 'a';

            // Choose the smallest character greater than target[i].
            for (int c = cur + 1; c < 26; c++) {
                if (cnt[c] > 0) {
                    string ans = target.substr(0, i);

                    ans += char('a' + c);
                    cnt[c]--;

                    // Put all remaining characters in sorted order.
                    for (int x = 0; x < 26; x++) {
                        while (cnt[x] > 0) {
                            ans += char('a' + x);
                            cnt[x]--;
                        }
                    }

                    return ans;
                }
            }
        }

        return "";
    }
};
