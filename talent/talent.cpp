#include <bits/stdc++.h>

using namespace std;

int main()  {
    freopen("talent.in", "r", stdin);
    freopen("talent.out", "w", stdout);
    int n, w;
    cin >> n >> w;
    vector<int> weight(n);
    vector<int> talent(n);
    int tott = 0;
    for (int i = 0; i < n; i++) {
        cin >> weight[i] >> talent[i];
        tott += talent[i];
    }
    vector<vector<int>> dp(n+1);
    for (int i = 0; i <= n; i++) {
        dp[i].resize(tott+1);
        fill(dp[i].begin(), dp[i].end(), INT_MAX);
    }
    dp[0][0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= tott; j++) {
            dp[i][j] = min(dp[i][j], dp[i-1][j]);
            if (j-talent[i-1] >= 0 && dp[i-1][j-talent[i-1]] != INT_MAX)   {
                dp[i][j] = min(dp[i][j], dp[i-1][j-talent[i-1]] + weight[i-1]);
            }
        }
    }
    double ans = 0;
    for (int j = 0; j <= tott; j++) {
        
        if (dp[n][j] != 0 && dp[n][j] != INT_MAX && dp[n][j] >= w)  {
            // /cout << j << ' ' << dp[n][j] << endl;
            ans = max(ans, (double)j/(double)dp[n][j]);
            
        }
    }
    int sol = ans*1000;
    //cout << ans << endl;
    cout <<sol << endl;
}