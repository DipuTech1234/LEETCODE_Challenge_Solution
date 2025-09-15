#include <string>
#include <unordered_set>
#include <sstream>
#include <vector>

using namespace std;

class Solution {
public:
    int canBeTypedWords(string text, string brokenLetters) {
        unordered_set<char> brokenSet(brokenLetters.begin(), brokenLetters.end());
        istringstream iss(text);
        string word;
        int count = 0;
        
        while (iss >> word) {
            bool valid = true;
            for (char c : word) {
                if (brokenSet.find(c) != brokenSet.end()) {
                    valid = false;
                    break;
                }
            }
            if (valid) {
                count++;
            }
        }
        
        return count;
    }
};
