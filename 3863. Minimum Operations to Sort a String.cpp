class Solution {
public:
    int minOperations(string s) {
        int n = s.size();
        int mn = s[0], mx = s[0];

        for (char c : s) {
            mn = min(mn, (int)c);
            mx = max(mx, (int)c);
        }

        if (is_sorted(s.begin(), s.end())) return 0;

        if (n == 2) return -1;

        if (n == 3) {
            if (s[0] <= s[1] && s[1] <= s[2]) return 0;
            if (s[0] == mn || s[2] == mx) return 1;
            return -1;
        }

        if (s[0] == mn || s[n - 1] == mx) return 1;

        if (s[0] == mx && s[n - 1] == mn) return 3;

        return 2;
    }
};
