class Solution {
public:
    int minCost(vector<vector<int>>& grid, int k) {
        int m = grid.size(), n = grid[0].size();
        const long long INF = 1e18;

        // dist[i][j][t] = min cost to reach (i,j) using t teleports
        vector<vector<vector<long long>>> dist(
            m, vector<vector<long long>>(n, vector<long long>(k + 1, INF))
        );

        // cells sorted by value
        vector<array<int,3>> cells;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                cells.push_back({grid[i][j], i, j});
        sort(cells.begin(), cells.end()); // ascending by value

        // pointer per teleport layer
        vector<int> ptr(k + 1, 0);

        using State = tuple<long long,int,int,int>; // cost, i, j, t
        priority_queue<State, vector<State>, greater<State>> pq;

        dist[0][0][0] = 0;
        pq.push({0, 0, 0, 0});

        while (!pq.empty()) {
            auto [cost, i, j, t] = pq.top();
            pq.pop();
            if (cost != dist[i][j][t]) continue;

            if (i == m - 1 && j == n - 1) return cost;

            // normal moves
            if (i + 1 < m) {
                long long nc = cost + grid[i + 1][j];
                if (nc < dist[i + 1][j][t]) {
                    dist[i + 1][j][t] = nc;
                    pq.push({nc, i + 1, j, t});
                }
            }
            if (j + 1 < n) {
                long long nc = cost + grid[i][j + 1];
                if (nc < dist[i][j + 1][t]) {
                    dist[i][j + 1][t] = nc;
                    pq.push({nc, i, j + 1, t});
                }
            }

            // teleport moves
            if (t < k) {
                while (ptr[t] < (int)cells.size() &&
                       cells[ptr[t]][0] <= grid[i][j]) {
                    int x = cells[ptr[t]][1];
                    int y = cells[ptr[t]][2];
                    if (cost < dist[x][y][t + 1]) {
                        dist[x][y][t + 1] = cost;
                        pq.push({cost, x, y, t + 1});
                    }
                    ptr[t]++;
                }
            }
        }

        long long ans = INF;
        for (int t = 0; t <= k; t++)
            ans = min(ans, dist[m - 1][n - 1][t]);

        return (int)ans;
    }
};
