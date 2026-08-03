class Solution {
public:
    string stoneGameIII(vector<int>& stoneValue) {
        int n = stoneValue.size();
        vector<int>dp(3,0);
        for(int i=n-1;i>=0;i--){
            int t1 = stoneValue[i]-dp[(i+1)%3];
            int t2 = INT_MIN;
            if(i+1<n) t2 = stoneValue[i]+stoneValue[i+1]-dp[(i+2)%3];
            int t3 = INT_MIN;
            if(i+2<n) t3 = stoneValue[i]+stoneValue[i+1]+stoneValue[i+2]-dp[(i+3)%3];
            dp[i%3] =  max({t1,t2,t3});
        }
        int ans = dp[0];
        if(ans>0) return "Alice";
        else if(ans<0) return "Bob";
        else return "Tie";
    }
};
