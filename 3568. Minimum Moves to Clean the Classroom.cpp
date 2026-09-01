class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size(), n = classroom[0].size();
        int N = m * n, k = 0, start = 0;

        vector<vector<int>> id(m, vector<int>(n, -1));

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (classroom[i][j] == 'L')
                    id[i][j] = k++;
                else if (classroom[i][j] == 'S')
                    start = i * n + j;
            }
        }

        if (k == 0) return 0;

        int full = (1 << k) - 1;

        // best[pos][mask] = maximum energy seen so far.
        vector<signed char> best(N * (1 << k), -1);

        // Encode: ((mask * N + pos) * (energy + 1) + remainingEnergy)
        auto encode = [&](int pos, int mask, int e) -> uint32_t {
            return ((uint32_t)mask * N + pos) * (energy + 1) + e;
        };

        auto decode = [&](uint32_t x, int &pos, int &mask, int &e) {
            e = x % (energy + 1);
            x /= (energy + 1);
            pos = x % N;
            mask = x / N;
        };

        queue<uint32_t> q;

        int sr = start / n, sc = start % n;
        int initialMask = 0;

        if (classroom[sr][sc] == 'L')
            initialMask |= 1 << id[sr][sc];

        int startIndex = initialMask * N + start;
        best[startIndex] = energy;
        q.push(encode(start, initialMask, energy));

        int dist = 0;
        int dr[] = {1, -1, 0, 0};
        int dc[] = {0, 0, 1, -1};

        while (!q.empty()) {
            int sz = q.size();

            while (sz--) {
                uint32_t cur = q.front();
                q.pop();

                int pos, mask, e;
                decode(cur, pos, mask, e);

                if (mask == full)
                    return dist;

                int r = pos / n, c = pos % n;

                for (int d = 0; d < 4; ++d) {
                    int nr = r + dr[d];
                    int nc = c + dc[d];

                    if (nr < 0 || nr >= m || nc < 0 || nc >= n)
                        continue;

                    if (classroom[nr][nc] == 'X')
                        continue;

                    if (e == 0)
                        continue;

                    int ne = e - 1;
                    int npos = nr * n + nc;
                    int nmask = mask;

                    if (classroom[nr][nc] == 'L') {
                        nmask |= 1 << id[nr][nc];
                    }

                    if (classroom[nr][nc] == 'R') {
                        ne = energy;
                    }

                    int idx = nmask * N + npos;

                    // A state with more remaining energy dominates
                    // one with less remaining energy.
                    if (best[idx] >= ne)
                        continue;

                    best[idx] = ne;
                    q.push(encode(npos, nmask, ne));
                }
            }

            ++dist;
        }

        return -1;
    }
};
