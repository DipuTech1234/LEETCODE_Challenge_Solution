#include <string>
#include <vector>
#include <numeric>
#include <algorithm>

class Solution {
private:
    const long long LIMIT = 1000001LL;

    // Helper to compute n choose r (nCr), capped at LIMIT
    long long nCr(int n, int r) {
        if (r < 0 || r > n) return 0;
        if (r == 0 || r == n) return 1;
        r = std::min(r, n - r);
        long long res = 1;
        for (int i = 1; i <= r; ++i) {
            res = res * (n - i + 1) / i;
            if (res >= LIMIT) return LIMIT;
        }
        return res;
    }

    // Calculates the total unique permutations of character frequencies in count[]
    long long countPermutations(const std::vector<int>& count) {
        int total = 0;
        for (int c : count) total += c;

        long long res = 1;
        for (int c : count) {
            if (c > 0) {
                res *= nCr(total, c);
                if (res >= LIMIT) return LIMIT;
                total -= c;
            }
        }
        return res;
    }

public:
    std::string smallestPalindrome(std::string s, int k) {
        std::vector<int> freq(26, 0);
        for (char ch : s) {
            freq[ch - 'a']++;
        }

        std::vector<int> half(26, 0);
        int half_len = 0;
        char mid_char = 0;

        for (int i = 0; i < 26; ++i) {
            half[i] = freq[i] / 2;
            half_len += half[i];
            if (freq[i] % 2 != 0) {
                mid_char = 'a' + i;
            }
        }

        // Total possible distinct palindromic permutations
        if (countPermutations(half) < k) {
            return "";
        }

        std::string left_half = "";
        
        for (int pos = 0; pos < half_len; ++pos) {
            for (int i = 0; i < 26; ++i) {
                if (half[i] == 0) continue;

                // Try placing character ('a' + i)
                half[i]--;
                long long ways = countPermutations(half);

                if (ways >= k) {
                    left_half += (char)('a' + i);
                    break; // Move to the next position
                } else {
                    k -= ways;
                    half[i]++; // Backtrack and try next character
                }
            }
        }

        std::string right_half = left_half;
        std::reverse(right_half.begin(), right_half.end());

        if (mid_char != 0) {
            return left_half + mid_char + right_half;
        }

        return left_half + right_half;
    }
};
