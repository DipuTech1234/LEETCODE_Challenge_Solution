class Solution {
    struct Node {
        int pref, suff, best, len;
        char lc, rc;
    };

    vector<Node> st;
    string s;

    Node merge(const Node &L, const Node &R) {
        if (L.len == 0) return R;
        if (R.len == 0) return L;

        Node res;
        res.len = L.len + R.len;
        res.lc = L.lc;
        res.rc = R.rc;

        res.pref = L.pref;
        if (L.pref == L.len && L.rc == R.lc)
            res.pref = L.len + R.pref;

        res.suff = R.suff;
        if (R.suff == R.len && L.rc == R.lc)
            res.suff = R.len + L.suff;

        res.best = max(L.best, R.best);
        if (L.rc == R.lc)
            res.best = max(res.best, L.suff + R.pref);

        return res;
    }

    void build(int idx, int l, int r) {
        if (l == r) {
            st[idx] = {1, 1, 1, 1, s[l], s[l]};
            return;
        }
        int mid = (l + r) / 2;
        build(idx * 2, l, mid);
        build(idx * 2 + 1, mid + 1, r);
        st[idx] = merge(st[idx * 2], st[idx * 2 + 1]);
    }

    void update(int idx, int l, int r, int pos, char c) {
        if (l == r) {
            s[pos] = c;
            st[idx] = {1, 1, 1, 1, c, c};
            return;
        }
        int mid = (l + r) / 2;
        if (pos <= mid)
            update(idx * 2, l, mid, pos, c);
        else
            update(idx * 2 + 1, mid + 1, r, pos, c);

        st[idx] = merge(st[idx * 2], st[idx * 2 + 1]);
    }

public:
    vector<int> longestRepeating(string S, string queryCharacters, vector<int>& queryIndices) {
        s = S;
        int n = s.size();
        st.resize(4 * n + 4);
        build(1, 0, n - 1);

        vector<int> ans;
        for (int i = 0; i < queryIndices.size(); i++) {
            update(1, 0, n - 1, queryIndices[i], queryCharacters[i]);
            ans.push_back(st[1].best);
        }
        return ans;
    }
};
