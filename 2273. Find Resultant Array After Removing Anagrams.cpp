class Solution {
public:
    vector<string> removeAnagrams(vector<string>& words) {
        vector<string> result;
        
        for (const string& word : words) {
            // If result is empty, add the first word
            if (result.empty()) {
                result.push_back(word);
                continue;
            }
            
            // Get the last word in result and current word
            string lastWord = result.back();
            string currentWord = word;
            
            // Sort both strings to check if they are anagrams
            sort(lastWord.begin(), lastWord.end());
            sort(currentWord.begin(), currentWord.end());
            
            // If they are not anagrams, add current word to result
            if (lastWord != currentWord) {
                result.push_back(word);
            }
        }
        
        return result;
    }
};
