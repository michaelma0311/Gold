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
    sort(lis.begin(), lis.end(), [](const array<int,3>& x, const array<int,3>& y) {
        return x[2] < y[2];
    });
    int dp[n+1][a+b+1];
    memset(dp, -1, sizeof(dp));
    dp[0][0] = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= a+b; j++)    {
            dp[i+1][j] = max(dp[i+1][j], dp[i][j]);
            if (dp[i][j] == -1)  {
                continue;
            }
            if (j >= b) {
                if (j + lis[i][1] <= a+b)   {
                    //cout << "INSIDE " << i << ' ' << lis[i][0] << ' ' << j + lis[i][1] << ' '  << dp[i][j]+lis[i][0]<< endl;
                    dp[i+1][j+lis[i][1]] = max(dp[i+1][j+lis[i][1]], dp[i][j] + lis[i][0]);
                }
            } else  {
                if (j + (lis[i][2]*lis[i][1]) <= b) {
                    dp[i+1][j+lis[i][2]*lis[i][1]] = max(dp[i+1][j+lis[i][2]*lis[i][1]], dp[i][j] + lis[i][0]);
                } else  {
                    int y = (b-j)/lis[i][2];
                    //cout <<"ADAD " <<  i << ' ' << lis[i][0] << ' ' << j + y*lis[i][2] + lis[i][1]-y << endl;
                    if (b+ lis[i][1]-y <= a+b)   {
                        dp[i+1][b+lis[i][1]-y] = max(dp[i+1][b+lis[i][1]-y], dp[i][j] + lis[i][0]);
                    }

                }
            }
        }
    }
    int ans = 0;
    for (int i = 0; i <= a+b; i++) {
        ans = max(ans, dp[n][i]);
    }
    cout << ans << endl;
}