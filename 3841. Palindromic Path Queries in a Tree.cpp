class Solution {
public:
    vector<bool> palindromePath(int n, vector<vector<int>>& edges,
                               string s, vector<string>& queries) {
        vector<vector<int>> adj(n);
        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        int LOG = 1;
        while ((1 << LOG) <= n) ++LOG;

        vector<vector<int>> up(LOG, vector<int>(n));
        vector<int> tin(n), tout(n), depth(n), pref(n);
        vector<int> order;
        order.reserve(n);

        int timer = 0;
        vector<int> st = {0};
        up[0][0] = 0;
        pref[0] = 1 << (s[0] - 'a');
        tin[0] = timer++;
        order.push_back(0);

        vector<int> parent(n, -1), iter(n, 0);
        parent[0] = 0;

        while (!st.empty()) {
            int u = st.back();

            if (iter[u] < (int)adj[u].size()) {
                int v = adj[u][iter[u]++];

                if (v == parent[u]) continue;

                parent[v] = u;
                up[0][v] = u;
                depth[v] = depth[u] + 1;
                pref[v] = pref[u] ^ (1 << (s[v] - 'a'));
                tin[v] = timer++;
                order.push_back(v);
                st.push_back(v);
            } else {
                tout[u] = timer;
                st.pop_back();
            }
        }

        for (int k = 1; k < LOG; ++k) {
            for (int u = 0; u < n; ++u) {
                up[k][u] = up[k - 1][up[k - 1][u]];
            }
        }

        auto lca = [&](int u, int v) {
            if (depth[u] < depth[v]) swap(u, v);

            int diff = depth[u] - depth[v];
            for (int k = 0; k < LOG; ++k) {
                if (diff & (1 << k)) u = up[k][u];
            }

            if (u == v) return u;

            for (int k = LOG - 1; k >= 0; --k) {
                if (up[k][u] != up[k][v]) {
                    u = up[k][u];
                    v = up[k][v];
                }
            }

            return up[0][u];
        };

        vector<int> bit(n + 2, 0);

        auto update = [&](int idx, int val) {
            for (++idx; idx <= n + 1; idx += idx & -idx) {
                bit[idx] ^= val;
            }
        };

        auto query = [&](int idx) {
            int res = 0;
            for (++idx; idx > 0; idx -= idx & -idx) {
                res ^= bit[idx];
            }
            return res;
        };

        auto rangeUpdate = [&](int l, int r, int val) {
            update(l, val);
            update(r, val);
        };

        vector<bool> answer;
        answer.reserve(queries.size());

        for (const string& q : queries) {
            stringstream ss(q);
            string type;
            int u;
            ss >> type >> u;

            if (type == "update") {
                char c;
                ss >> c;

                int oldBit = 1 << (s[u] - 'a');
                int newBit = 1 << (c - 'a');
                int diff = oldBit ^ newBit;

                if (diff != 0) {
                    rangeUpdate(tin[u], tout[u], diff);
                    s[u] = c;
                }
            } else {
                int v;
                ss >> v;

                int w = lca(u, v);

                int maskU = pref[u] ^ query(tin[u]);
                int maskV = pref[v] ^ query(tin[v]);

                int pathMask = maskU ^ maskV ^ (1 << (s[w] - 'a'));

                answer.push_back((pathMask & (pathMask - 1)) == 0);
            }
        }

        return answer;
    }
};
