class Solution {
public:
    static bool asteroidsDestroyed(int mass, vector<int>& asteroids) {
        static unsigned freq[100001] = {0};

        unsigned xmax = 0, xmin = 100000;

        // Count frequencies
        for (unsigned x : asteroids) {
            freq[x]++;
            xmin = min(xmin, x);
            xmax = max(xmax, x);
        }

        long long planet = mass;

        // Process in sorted order
        for (unsigned x = xmin; x <= xmax; x++) {
            if (freq[x] == 0) continue;

            if (x > planet) {
                // Clear used frequencies before returning
                for (unsigned i = xmin; i <= xmax; i++) {
                    freq[i] = 0;
                }
                return false;
            }

            planet += 1LL * x * freq[x];
            freq[x] = 0;
        }

        return true;
    }
};

auto init = []() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 'c';
}();
