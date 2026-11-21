class Solution {
public:
    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        int n = parent.size();

        vector<vector<int>> adj(n), tree(n);

        for (int i = 1; i < n; i++) {
            adj[parent[i]].push_back(i);
        }

        vector<int> newParent = parent;
        vector<int> last(26, -1);
        vector<int> oldLast(n);

        stack<pair<int, int>> st;
        st.push({0, 0});

        while (!st.empty()) {
            auto [u, state] = st.top();
            st.pop();

            int c = s[u] - 'a';

            if (state == 0) {
                oldLast[u] = last[c];

                if (last[c] != -1) {
                    newParent[u] = last[c];
                }

                last[c] = u;

                st.push({u, 1});

                for (int v : adj[u]) {
                    st.push({v, 0});
                }
            } 
            else {
                last[c] = oldLast[u];
            }
        }

        for (int i = 1; i < n; i++) {
            tree[newParent[i]].push_back(i);
        }

        vector<int> order;
        stack<int> stk;
        stk.push(0);

        while (!stk.empty()) {
            int u = stk.top();
            stk.pop();

            order.push_back(u);

            for (int v : tree[u]) {
                stk.push(v);
            }
        }

        vector<int> ans(n, 1);

        for (int i = n - 1; i >= 0; i--) {
            int u = order[i];

            for (int v : tree[u]) {
                ans[u] += ans[v];
            }
        }

        return ans;
    }
};
