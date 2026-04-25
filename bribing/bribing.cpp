#include <bits/stdc++.h>
using namespace std;

#define int long long

signed main()   {
    int n, a, b;
    cin >> n >> a >> b;
    vector<array<int,3>> lis(n);
    for (int i = 0; i < n; i++) {
        cin >> lis[i][0] >> lis[i][1] >> lis[i][2];
    }
    int dp[n+1][a+1][b+1];
    memset(dp, -1, sizeof(dp));
    dp[0][0][0] = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= a; j++)    {
            for (int k = 0; k <= b; k++) {
                dp[i+1][j][k] = max(dp[i+1][j][k], dp[i][j][k]);
                if (dp[i][j][k] == -1)  {
                    continue;
                }
                for (int x = 0; x <= lis[i][1]; x++)    {
                    if (x * lis[i][2] + k <= b) {
                        if (j + lis[i][1] - x <= a) {
                            dp[i+1][j+(lis[i][1]-x)][k + x * lis[i][2]] = max(dp[i+1][j+(lis[i][1]-x)][k + x * lis[i][2]], dp[i][j][k] + lis[i][0]);
                        }
                    } else  {
                        break;
                    }
                }
            }
        }
    }
    int ans = 0;
    for (int i = 0; i <= a; i++) {
        for (int j = 0; j <= b; j++)    {
            ans = max(ans, dp[n][i][j]);
        }
    }
    cout << ans << endl;
}