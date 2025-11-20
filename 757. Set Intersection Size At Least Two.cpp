class Solution {
public:
    int intersectionSizeTwo(vector<vector<int>>& intervals) {
        // Sort intervals by end point, if equal then by start point descending
        sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[1] == b[1] ? a[0] > b[0] : a[1] < b[1];
        });
        
        vector<int> nums;
        
        for (const auto& interval : intervals) {
            int start = interval[0];
            int end = interval[1];
            
            // Count how many numbers from nums are in current interval
            int count = 0;
            for (int num : nums) {
                if (num >= start && num <= end) {
                    count++;
                }
            }
            
            // If we already have 2 numbers in this interval, skip
            if (count >= 2) continue;
            
            // Add numbers from the end to satisfy the requirement
            if (count == 0) {
                // Need to add 2 numbers
                nums.push_back(end - 1);
                nums.push_back(end);
            } else if (count == 1) {
                // Need to add 1 more number
                // Add the largest possible number that's not already included
                if (nums.back() == end) {
                    nums.push_back(end - 1);
                } else {
                    nums.push_back(end);
                }
            }
        }
        
        return nums.size();
    }
};
