#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestBalanced(string s) {
        int n = s.size();
        int ans = 0;

        for (int i = 0; i < n; i++) {
            vector<int> freq(26, 0);
            int mx = 0;

            for (int j = i; j < n; j++) {
                int c = s[j] - 'a';
                freq[c]++;
                mx = max(mx, freq[c]);

                int len = j - i + 1;
                int distinct = 0;
                bool ok = true;

                for (int k = 0; k < 26; k++) {
                    if (freq[k] > 0) {
                        distinct++;
                        if (freq[k] != mx) {
                            ok = false;
                            break;
                        }
                    }
                }

                if (ok && mx * distinct == len) {
                    ans = max(ans, len);
                }
            }
        }

        return ans;
    }
};
