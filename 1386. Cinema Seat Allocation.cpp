class Solution {
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
        unordered_map<int, int> mp;

        for (auto &seat : reservedSeats) {
            int row = seat[0];
            int col = seat[1];

            if (col >= 2 && col <= 9)
                mp[row] |= (1 << (col - 2));
        }

        int ans = (n - mp.size()) * 2;

        for (auto &[row, mask] : mp) {
            bool left  = (mask & 0b00001111) == 0; // 2,3,4,5
            bool right = (mask & 0b11110000) == 0; // 6,7,8,9
            bool mid   = (mask & 0b00111100) == 0; // 4,5,6,7

            if (left && right)
                ans += 2;
            else if (left || right || mid)
                ans += 1;
        }

        return ans;
    }
};
