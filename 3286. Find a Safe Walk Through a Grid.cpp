class Solution {
public:
    static const int N = 5000;
    int q[N], maxH[N];
    int front, back;
    int d[5] = {0, 1, 0, -1, 0};

    static inline int idx(int i, int j, int c) {
        return i * c + j;
    }

    static bool outSide(int i, int j, int r, int c) {
        return i < 0 || i >= r || j < 0 || j >= c;
    }

    bool findSafeWalk(vector<vector<int>>& grid, int health) {
        int r = grid.size(), c = grid[0].size();

        memset(maxH, -1, sizeof(maxH));

        front = back = N / 2;
        q[back++] = 0;
        maxH[0] = health - grid[0][0];

        while (front < back) {
            int ij = q[front++];
            int curH = maxH[ij];

            if (ij == r * c - 1)
                return curH > 0;

            int i = ij / c;
            int j = ij % c;

            for (int a = 0; a < 4; a++) {
                int s = i + d[a];
                int t = j + d[a + 1];

                if (outSide(s, t, r, c))
                    continue;

                int st = idx(s, t, c);
                int H2 = curH - grid[s][t];

                if (H2 > maxH[st]) {
                    maxH[st] = H2;
                    if (grid[s][t] == 0)
                        q[--front] = st;
                    else
                        q[back++] = st;
                }
            }
        }

        return false;
    }
};
