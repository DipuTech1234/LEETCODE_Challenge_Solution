class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        vector<int> ans = {-1, -1};
        if (!head || !head->next || !head->next->next) return ans;

        ListNode* prev = head;
        ListNode* curr = head->next;

        int pos = 1;
        int first = -1, last = -1;
        int minDist = INT_MAX;

        while (curr->next) {
            ListNode* next = curr->next;

            if ((curr->val > prev->val && curr->val > next->val) ||
                (curr->val < prev->val && curr->val < next->val)) {

                if (first == -1) {
                    first = pos;
                } else {
                    minDist = min(minDist, pos - last);
                }

                last = pos;
            }

            prev = curr;
            curr = next;
            pos++;
        }

        if (first == -1 || first == last)
            return ans;

        return {minDist, last - first};
    }
};
