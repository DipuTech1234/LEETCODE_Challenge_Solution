class Solution {
public:
    vector<string> braceExpansionII(string expression) {
        set<string> st;
        
        function<set<string>(int&)> parseExpr;
        function<set<string>(int&)> parseTerm;
        function<set<string>(int&)> parseFactor;
        
        parseFactor = [&](int& i) -> set<string> {
            set<string> res;
            
            if (expression[i] == '{') {
                i++;
                res = parseExpr(i);
                i++; // '}'
            } else {
                res.insert(string(1, expression[i]));
                i++;
            }
            
            return res;
        };
        
        parseTerm = [&](int& i) -> set<string> {
            set<string> res = {""};
            
            while (i < expression.size() &&
                   expression[i] != '}' &&
                   expression[i] != ',') {
                
                set<string> cur = parseFactor(i);
                set<string> temp;
                
                for (const string& a : res)
                    for (const string& b : cur)
                        temp.insert(a + b);
                
                res = temp;
            }
            
            return res;
        };
        
        parseExpr = [&](int& i) -> set<string> {
            set<string> res = parseTerm(i);
            
            while (i < expression.size() && expression[i] == ',') {
                i++;
                set<string> cur = parseTerm(i);
                res.insert(cur.begin(), cur.end());
            }
            
            return res;
        };
        
        int i = 0;
        st = parseExpr(i);
        
        return vector<string>(st.begin(), st.end());
    }
};
