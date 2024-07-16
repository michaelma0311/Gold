#include <bits/stdc++.h>
using namespace std;

int main()  {
    freopen("248.in", "r", stdin);
    freopen("248.out", "w", stdout);
    int n;
    cin >> n;
    vector<int> lis(n);
    for (int i = 0; i < n; i++) {
        cin >> lis[i]; 
    }
    vector<vector<int>> dp(n);
    for (int i = 0; i < n; i++) {
        dp[i].resize(n);
        fill(dp[i].begin(), dp[i].end(), -1);
    }
    for (int len = 1; len <= n; len++)  {
        for (int i = 0; i < n-len+1; i++)   {
            int j = i+len-1;
            if (len == 1)   {
                dp[i][j] = lis[i];
            } else  {
                for (int cur = i; cur < j; cur++)   {
                    if (dp[i][cur] != -1 && dp[i][cur] == dp[cur+1][j]) {
                        dp[i][j] = max(dp[i][j], dp[i][cur]+1);
                    }
                }
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ans = max(ans, dp[i][j]);
        }
    }
    cout << ans << endl;
}