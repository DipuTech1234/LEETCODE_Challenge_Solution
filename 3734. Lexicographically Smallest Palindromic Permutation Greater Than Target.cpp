class Solution {
public:
    string lexPalindromicPermutation(string s, string target) {
        int n = s.size();
        vector<int> cnt(26);
        
        for (char c : s)
            cnt[c - 'a']++;
        
        int odd = -1;
        for (int i = 0; i < 26; i++) {
            if (cnt[i] % 2) {
                if (odd != -1) return "";
                odd = i;
            }
        }
        
        vector<int> half(26);
        for (int i = 0; i < 26; i++)
            half[i] = cnt[i] / 2;
        
        int h = n / 2;
        
        // Try to match target's first half exactly.
        vector<int> rem = half;
        bool possible = true;
        
        for (int i = 0; i < h; i++) {
            int x = target[i] - 'a';
            if (rem[x] == 0) {
                possible = false;
                break;
            }
            rem[x]--;
        }
        
        // If exact first half is possible, check the palindrome itself.
        if (possible) {
            string left;
            for (int i = 0; i < 26; i++)
                left += string(rem[i], char('a' + i));
            
            // Reconstruct exact left half from target.
            left.clear();
            for (int i = 0; i < h; i++)
                left += target[i];
            
            string ans = left;
            if (odd != -1)
                ans += char('a' + odd);
            ans += string(left.rbegin(), left.rend());
            
            if (ans > target)
                return ans;
        }
        
        // Backtrack: find the rightmost position where we can
        // put a character strictly greater than target[i].
        for (int k = h - 1; k >= 0; k--) {
            vector<int> leftCnt = half;
            
            bool ok = true;
            for (int i = 0; i < k; i++) {
                int x = target[i] - 'a';
                if (leftCnt[x] == 0) {
                    ok = false;
                    break;
                }
                leftCnt[x]--;
            }
            
            if (!ok) continue;
            
            int x = target[k] - 'a';
            int greater = -1;
            
            for (int c = x + 1; c < 26; c++) {
                if (leftCnt[c] > 0) {
                    greater = c;
                    break;
                }
            }
            
            if (greater == -1) continue;
            
            string left;
            
            // Prefix equal to target.
            for (int i = 0; i < k; i++)
                left += target[i];
            
            // First character making the palindrome greater.
            left += char('a' + greater);
            leftCnt[greater]--;
            
            // Smallest possible suffix.
            for (int c = 0; c < 26; c++)
                left += string(leftCnt[c], char('a' + c));
            
            string ans = left;
            if (odd != -1)
                ans += char('a' + odd);
            ans += string(left.rbegin(), left.rend());
            
            return ans;
        }
        
        return "";
    }
};
