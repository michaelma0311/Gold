#include <bits/stdc++.h>
using namespace std;

int main()  {
    freopen("feast.in","r",stdin);
	freopen("feast.out","w",stdout);
    int t, a, b;
    cin >> t >> a >> b;
    vector<vector<bool>> dp(2);
    dp[0].resize(t+1);
    dp[1].resize(t+1);
    dp[0][0] = true;
    for (int i = 0; i < dp.size(); i++)   {
        for (int j = 0; j < dp[i].size(); j++)  {
            if (!dp[i][j])  {
                continue;
            }
            if (j+a <= t)   {
                dp[i][j+a] = true;
            }
            if (j+b <= t)   {
                dp[i][j+b] = true;
            }
            if (i == 0) {
                dp[i+1][j/2] = true;
            }    
        }  
    }   
    int cur = t;
    while (!dp[1][cur])  {
        cur -= 1;
    }
    cout << cur << endl;
}