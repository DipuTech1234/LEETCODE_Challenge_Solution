#include <bits/stdc++.h>
#include <ranges>
using namespace std;

class Solution {
    struct Group {
        int start;
        int length;
    };

    class SparseTable {
    public:
        SparseTable(const vector<int>& nums) {
            n = nums.size();
            if (n == 0) return;
            int lg = std::bit_width((unsigned)n);
            st.assign(lg, vector<int>(n));
            st[0] = nums;
            for (int k = 1; k < lg; k++) {
                for (int i = 0; i + (1 << k) <= n; i++) {
                    st[k][i] = max(st[k - 1][i],
                                   st[k - 1][i + (1 << (k - 1))]);
                }
            }
        }

        int query(int l, int r) const {
            int k = std::bit_width((unsigned)(r - l + 1)) - 1;
            return max(st[k][l], st[k][r - (1 << k) + 1]);
        }

    private:
        int n = 0;
        vector<vector<int>> st;
    };

    pair<vector<Group>, vector<int>> getZeroGroups(const string& s) {
        vector<Group> groups;
        vector<int> idx(s.size());
        for (int i = 0; i < (int)s.size(); i++) {
            if (s[i] == '0') {
                if (i && s[i - 1] == '0')
                    groups.back().length++;
                else
                    groups.push_back({i, 1});
            }
            idx[i] = (int)groups.size() - 1;
        }
        return {groups, idx};
    }

    vector<int> getMerge(const vector<Group>& groups) {
        vector<int> res;
        for (int i = 0; i + 1 < (int)groups.size(); i++)
            res.push_back(groups[i].length + groups[i + 1].length);
        return res;
    }

public:
    vector<int> maxActiveSectionsAfterTrade(string s,
                                            vector<vector<int>>& queries) {
        int ones = ranges::count(s, '1');

        auto [groups, idx] = getZeroGroups(s);
        if (groups.empty()) return vector<int>(queries.size(), ones);

        SparseTable st(getMerge(groups));

        vector<int> ans;

        for (auto& q : queries) {
            int l = q[0], r = q[1];

            int left = (idx[l] == -1)
                           ? -1
                           : groups[idx[l]].length - (l - groups[idx[l]].start);

            int right = (idx[r] == -1)
                            ? -1
                            : (r - groups[idx[r]].start + 1);

            int startAdj = idx[l] + 1;
            int endAdj = (s[r] == '1' ? idx[r] : idx[r] - 1) - 1;

            int cur = ones;

            if (s[l] == '0' && s[r] == '0' && idx[l] + 1 == idx[r]) {
                cur = max(cur, ones + left + right);
            } else if (startAdj <= endAdj) {
                cur = max(cur, ones + st.query(startAdj, endAdj));
            }

            if (s[l] == '0' &&
                idx[l] + 1 <= (s[r] == '1' ? idx[r] : idx[r] - 1)) {
                cur = max(cur,
                          ones + left + groups[idx[l] + 1].length);
            }

            if (s[r] == '0' && idx[l] < idx[r] - 1) {
                cur = max(cur,
                          ones + right + groups[idx[r] - 1].length);
            }

            ans.push_back(cur);
        }

        return ans;
    }
};
