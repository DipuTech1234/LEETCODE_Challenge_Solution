class Solution {
public:
    long long minimumCost(string source, string target,
                          vector<string>& original,
                          vector<string>& changed,
                          vector<int>& cost) {
        const long long INF = 1e18;
        int n = source.size();

        unordered_map<string, int> id;
        int idx = 0;

        for (auto &s : original) if (!id.count(s)) id[s] = idx++;
        for (auto &s : changed)  if (!id.count(s)) id[s] = idx++;

        int m = idx;
        vector<vector<long long>> dist(m, vector<long long>(m, INF));

        for (int i = 0; i < m; i++) dist[i][i] = 0;

        for (int i = 0; i < original.size(); i++) {
            int u = id[original[i]];
            int v = id[changed[i]];
            dist[u][v] = min(dist[u][v], (long long)cost[i]);
        }

        for (int k = 0; k < m; k++)
            for (int i = 0; i < m; i++)
                for (int j = 0; j < m; j++)
                    if (dist[i][k] < INF && dist[k][j] < INF)
                        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

        vector<long long> dp(n + 1, INF);
        dp[0] = 0;

        for (int i = 0; i < n; i++) {
            if (dp[i] == INF) continue;

            if (source[i] == target[i])
                dp[i + 1] = min(dp[i + 1], dp[i]);

            for (auto &p1 : id) {
                const string &a = p1.first;
                int len = a.size();
                if (i + len > n) continue;
                if (source.substr(i, len) != a) continue;

                for (auto &p2 : id) {
                    const string &b = p2.first;
                    if (b.size() != len) continue;
                    if (target.substr(i, len) != b) continue;

                    long long d = dist[p1.second][p2.second];
                    if (d < INF)
                        dp[i + len] = min(dp[i + len], dp[i] + d);
                }
            }
        }

        return dp[n] == INF ? -1 : dp[n];
    }
};
