class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();

        int orientation = -1, k = 0;

        bool a = true, b = true;

        for (int i = 0; i < n; i++) {
            if (nums[i] != (nums[0] + i) % n)
                a = false;

            if (nums[i] != (nums[0] - i + n) % n)
                b = false;
        }

        if (a) {
            orientation = 0;
            k = nums[0];
        } else if (b) {
            orientation = 1;
            k = (n - 1 - nums[0] + n) % n;
        } else {
            return -1;
        }

        vector<int> dist(2 * n, -1);
        queue<int> q;

        int start = orientation * n + k;
        dist[start] = 0;
        q.push(start);

        while (!q.empty()) {
            int state = q.front();
            q.pop();

            int o = state / n;
            int pos = state % n;

            if (state == 0)
                return dist[state];

            int next = o * n + (pos + 1) % n;

            if (dist[next] == -1) {
                dist[next] = dist[state] + 1;
                q.push(next);
            }

            next = (1 - o) * n + (n - pos) % n;

            if (dist[next] == -1) {
                dist[next] = dist[state] + 1;
                q.push(next);
            }
        }

        return -1;
    }
};
