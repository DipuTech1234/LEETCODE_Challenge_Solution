class Solution {
public:
    int getDecimalValue(ListNode* head) {
        int decimalValue = 0;
        while (head != nullptr) {
            decimalValue = (decimalValue << 1) | head->val;
            head = head->next;
        }
        return decimalValue;
    }
};
