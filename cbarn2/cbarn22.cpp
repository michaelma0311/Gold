#include <bits/stdc++.h>
using namespace std;

signed main()  {
    freopen("cbarn2.in", "r", stdin);
    freopen("cbarn2.out", "w", stdout);
    long long n, k;
    cin >> n >> k;
    deque<long long> lis;
    for (long long i= 0; i < n; i++)  {
        long long x;
        cin >> x;
        lis.push_back(x);
    }
    long long ans=  LLONG_MAX;
    for (long long _ = 0; _ < n; _++) {
        vector<vector<long long>> dp(k+1);
        for (long long i = 0; i < k+1; i++)   {
            dp[i].resize(n+1);
            fill(dp[i].begin(), dp[i].end(), LLONG_MAX);
        }
        dp[0][n] = 0;                   
        for (long long numdoor = 1; numdoor <= k; numdoor++)  {
            for (long long i = 0; i <= n; i++)    {
                long long cursum = 0;
                for (long long j = i+1; j <= n; j++)    {
                    cursum += lis[j-1]*(j-i-1);
                    if (dp[numdoor-1][j] != LLONG_MAX)    {
                        dp[numdoor][i] = min(dp[numdoor][i], dp[numdoor-1][j]+cursum);
                    } else  {
                        dp[numdoor][i] = min(dp[numdoor][i], dp[numdoor-1][j]);
                    }
                }
            }

        }
        ans = min(ans, dp[k][0]);
        long long curroom = lis.front();
        lis.pop_front();
        lis.push_back(curroom);
    }
    
    cout << ans << endl;
}
