#include <bits/stdc++.h>
using namespace std;

using int2 = pair<int, int>;

const int N = 100002;
static int2 R[N];

static constexpr int M = 1 << 10;
static constexpr int mask = M - 1;
static constexpr int bshift = 10;

int freq[M];

void radix_sort(int2* nums, int n) {
    int2* buffer = (int2*)alloca(n * sizeof(int2));

    int2* in = nums;
    int2* out = buffer;

    for (int round = 0; round < 3; round++) {
        int shift = round * bshift;

        memset(freq, 0, sizeof(freq));

        for (int i = 0; i < n; i++)
            freq[(in[i].first >> shift) & mask]++;

        partial_sum(freq, freq + M, freq);

        for (int i = n - 1; i >= 0; i--) {
            int x = (in[i].first >> shift) & mask;
            out[--freq[x]] = in[i];
        }

        swap(in, out);
    }

    if (in != nums)
        memcpy(nums, in, n * sizeof(int2));
}

class Solution {
public:
    int maxBuilding(int n, vector<vector<int>>& restrictions) {
        int m = restrictions.size();

        for (int i = 0; i < m; i++)
            R[i] = {restrictions[i][0], restrictions[i][1]};

        R[m] = {1, 0};
        R[m + 1] = {n, n - 1};
        m += 2;

        radix_sort(R, m);

        // Left-to-right pass
        for (int i = 1; i < m; i++) {
            R[i].second = min(
                R[i].second,
                R[i - 1].second + (R[i].first - R[i - 1].first)
            );
        }

        // Right-to-left pass
        for (int i = m - 2; i >= 0; i--) {
            R[i].second = min(
                R[i].second,
                R[i + 1].second + (R[i + 1].first - R[i].first)
            );
        }

        int ans = 0;

        for (int i = 0; i < m - 1; i++) {
            int d = R[i + 1].first - R[i].first;

            int peak = (R[i].second + R[i + 1].second + d) / 2;

            ans = max(ans, peak);
        }

        return ans;
    }
};

static auto init = []() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return 0;
}();
