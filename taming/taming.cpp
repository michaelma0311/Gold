#include <bits/stdc++.h>

using namespace std;


signed main()  {
    freopen("taming.in","r",stdin);
	freopen("taming.out","w",stdout);
    long long n;
    cin >> n;
    vector<long long> lis(n);
    for (long long i = 0; i < n; i++) {
        cin >> lis[i];
    }
    long long dp[n][n][n];
    for (long long i = 0; i < n; i++) {
        for (long long j = 0; j < n; j++) {
            for (long long k = 0; k < n; k++) {
                dp[i][j][k] = INT_MAX;
            }
        }
    }
    dp[0][0][0] = (lis[0] != 0);
    for (long long i = 1; i < n; i++) {
        for (long long j = 0; j <= i; j++)    {
            for (long long k = 0; k <= i; k++)    {
                if (j != i) {
                    dp[i][j][k] = dp[i-1][j][k];
                } else  {
                    for (long long tempj = 0; tempj <= i-1; tempj++)  {
                        if (k == 0) {
                            break;
                        }
                        dp[i][j][k] = min(dp[i][j][k], dp[i-1][tempj][k-1]);
                    }
                }
                if (lis[i] != (i-j))    {
                    dp[i][j][k] += 1;
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        //cout << "THJIS IS " << i << endl;
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                //cout << "WGEGW " << j << ' ' << k << ' ' << dp[i][j][k] << endl; 
            }
        }
    }
    for (long long k = 0; k < n; k++) {
        long long ans = INT_MAX;
        for (long long j = 0; j < n; j++) {
            //cout << "HI MY NAME IS " << j << ' ' << k << ' ' << dp[n-1][j][k] << endl;
            ans = min(ans, dp[n-1][j][k]);
        }
        cout << ans << endl;
    }
}