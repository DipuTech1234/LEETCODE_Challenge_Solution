#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    string smallestNumber(string num, long long t) {
        // Factorize t into prime factors 2, 3, 5, 7
        long long temp = t;
        int c2 = 0, c3 = 0, c5 = 0, c7 = 0;
        
        while (temp % 2 == 0) { temp /= 2; c2++; }
        while (temp % 3 == 0) { temp /= 3; c3++; }
        while (temp % 5 == 0) { temp /= 5; c5++; }
        while (temp % 7 == 0) { temp /= 7; c7++; }
        
        // If t has prime factors other than 2, 3, 5, 7, it's impossible
        if (temp > 1) return "-1";

        int n = num.size();

        // Function to find minimum digits needed to satisfy required prime factors
        auto get_min_digits = [](int c2, int c3, int c5, int c7) -> string {
            string res = "";
            
            // Greedily combine factors into largest single digits (9, 8, 7, 6, 5, 4, 3, 2)
            while (c3 >= 2) { res += '9'; c3 -= 2; }
            while (c2 >= 3) { res += '8'; c2 -= 3; }
            while (c7 > 0)  { res += '7'; c7--; }
            if (c2 >= 1 && c3 >= 1) { res += '6'; c2--; c3--; }
            while (c5 > 0)  { res += '5'; c5--; }
            while (c2 >= 2) { res += '4'; c2 -= 2; }
            while (c3 > 0)  { res += '3'; c3--; }
            while (c2 > 0)  { res += '2'; c2--; }
            
            sort(res.begin(), res.end());
            return res;
        };

        // Prefix factor counts in num
        vector<int> p2(n + 1, 0), p3(n + 1, 0), p5(n + 1, 0), p7(n + 1, 0);
        int zero_idx = -1;

        for (int i = 0; i < n; ++i) {
            if (num[i] == '0') {
                if (zero_idx == -1) zero_idx = i;
                p2[i + 1] = p2[i];
                p3[i + 1] = p3[i];
                p5[i + 1] = p5[i];
                p7[i + 1] = p7[i];
            } else {
                int d = num[i] - '0';
                p2[i + 1] = p2[i];
                p3[i + 1] = p3[i];
                p5[i + 1] = p5[i];
                p7[i + 1] = p7[i];
                
                int td = d;
                while (td % 2 == 0) { td /= 2; p2[i + 1]++; }
                while (td % 3 == 0) { td /= 3; p3[i + 1]++; }
                while (td % 5 == 0) { td /= 5; p5[i + 1]++; }
                while (td % 7 == 0) { td /= 7; p7[i + 1]++; }
            }
        }

        // Try prefix match length L from n down to 0
        for (int L = n; L >= 0; --L) {
            if (zero_idx != -1 && zero_idx < L) continue;

            int rem2 = max(0, c2 - p2[L]);
            int rem3 = max(0, c3 - p3[L]);
            int rem5 = max(0, c5 - p5[L]);
            int rem7 = max(0, c7 - p7[L]);

            if (L == n) {
                if (rem2 == 0 && rem3 == 0 && rem5 == 0 && rem7 == 0) {
                    return num;
                }
                continue;
            }

            // Try next digit at position L greater than num[L]
            int start_digit = (L < n) ? (num[L] - '0' + 1) : 1;
            for (int d = start_digit; d <= 9; ++d) {
                int td = d;
                int d2 = 0, d3 = 0, d5 = 0, d7 = 0;
                while (td % 2 == 0) { td /= 2; d2++; }
                while (td % 3 == 0) { td /= 3; d3++; }
                while (td % 5 == 0) { td /= 5; d5++; }
                while (td % 7 == 0) { td /= 7; d7++; }

                int cur_rem2 = max(0, rem2 - d2);
                int cur_rem3 = max(0, rem3 - d3);
                int cur_rem5 = max(0, rem5 - d5);
                int cur_rem7 = max(0, rem7 - d7);

                string suffix = get_min_digits(cur_rem2, cur_rem3, cur_rem5, cur_rem7);

                if ((int)suffix.size() <= n - 1 - L) {
                    string res = num.substr(0, L);
                    res += to_string(d);
                    
                    int ones = (n - 1 - L) - (int)suffix.size();
                    res.append(ones, '1');
                    res += suffix;
                    return res;
                }
            }
        }

        // If no solution with n digits, construct minimal length > n
        string suffix = get_min_digits(c2, c3, c5, c7);
        int target_len = max((int)num.size() + 1, (int)suffix.size());
        
        string res = "";
        int ones = target_len - (int)suffix.size();
        res.append(ones, '1');
        res += suffix;

        return res;
    }
};
