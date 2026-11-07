class Solution {
public:
    vector<int> assignTasks(vector<int>& servers, vector<int>& tasks) {
        int n = servers.size();
        int m = tasks.size();

        priority_queue<pair<int, int>,
                       vector<pair<int, int>>,
                       greater<pair<int, int>>> freeServers;

        priority_queue<pair<long long, pair<int, int>>,
                       vector<pair<long long, pair<int, int>>>,
                       greater<pair<long long, pair<int, int>>>> busyServers;

        queue<int> taskQueue;
        vector<int> ans(m);

        for (int i = 0; i < n; i++) {
            freeServers.push({servers[i], i});
        }

        long long time = 0;
        int nextTask = 0;
        int completed = 0;

        while (completed < m) {
            while (nextTask < m && nextTask <= time) {
                taskQueue.push(nextTask);
                nextTask++;
            }

            while (!busyServers.empty() &&
                   busyServers.top().first <= time) {
                auto server = busyServers.top();
                busyServers.pop();

                freeServers.push({server.second.first,
                                  server.second.second});
            }

            while (!freeServers.empty() && !taskQueue.empty()) {
                int task = taskQueue.front();
                taskQueue.pop();

                auto server = freeServers.top();
                freeServers.pop();

                int weight = server.first;
                int index = server.second;

                ans[task] = index;

                busyServers.push({
                    time + tasks[task],
                    {weight, index}
                });

                completed++;
            }

            if (completed == m) {
                break;
            }

            if (!taskQueue.empty() && freeServers.empty()) {
                time = busyServers.top().first;
            } else if (nextTask < m) {
                time = nextTask;
            }
        }

        return ans;
    }
};
