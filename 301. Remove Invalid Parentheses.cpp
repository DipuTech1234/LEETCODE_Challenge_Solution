class Solution {
public:
    vector<string> removeInvalidParentheses(string s) {
        vector<string> ans;
        unordered_set<string> vis;
        queue<string> q;
        q.push(s);
        vis.insert(s);

        bool found = false;

        while (!q.empty()) {
            string cur = q.front();
            q.pop();

            int balance = 0;
            bool valid = true;

            for (char c : cur) {
                if (c == '(') balance++;
                else if (c == ')') {
                    balance--;
                    if (balance < 0) {
                        valid = false;
                        break;
                    }
                }
            }

            if (valid && balance == 0) {
                ans.push_back(cur);
                found = true;
            }

            if (found) continue;

            for (int i = 0; i < cur.size(); i++) {
                if (cur[i] != '(' && cur[i] != ')')
                    continue;

                string next = cur.substr(0, i) + cur.substr(i + 1);

                if (!vis.count(next)) {
                    vis.insert(next);
                    q.push(next);
                }
            }
        }

        return ans;
    }
};
