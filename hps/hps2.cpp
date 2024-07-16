#include <bits/stdc++.h> 
using namespace std;
const int MX = 1e5 + 5;

int dp[MX][25][3];  
                         

int main()  {
    freopen("hps.in","r",stdin);
	freopen("hps.out","w",stdout);
    int n, m;
    cin >> n >> m;
    vector<int> lis(n);
    for (int i = 0; i < n; i++) {
        char x;
        cin >> x;
        if (x == 'H')   {
            lis[i] = 0;
        } else if (x == 'P')    {
            lis[i] = 1;
        } else  {
            lis[i] = 2;
        }
    }
    dp[0][0][lis[0]] = 1;
    dp[0][1][lis[0]] = 1;
    int ans = 0;
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < m+1; j++) {
            for (int k = 0; k < 3; k++) {
                if (k == lis[i])    {
                    dp[i][j][k] = max(dp[i][j][k], dp[i-1][j][k]+1);
                } else  {
                    dp[i][j+1][lis[i]] = max(dp[i-1][j][k]+1, dp[i][j+1][lis[i]]);
                    dp[i][j][k] = max(dp[i][j][k], dp[i-1][j][k]);
                }
                ans = max(ans, dp[i][j][k]);
            }
        }
    }
    cout << ans << endl;
    
}