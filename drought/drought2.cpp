#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main()  {
    int n;
    cin >> n;
    const int mod = 1e9+7;
    int mina = INT_MAX;
    vector<int> lis(n);
    int maxa = 0;
    for (int i = 0; i < n; i++)  {
        cin >> lis[i];
        maxa = max(maxa, lis[i]);
        mina = min(mina, lis[i]);
    }
    if (n%2 == 0)  {
        vector<vector<int>> dp(n);
        for (int i = 0; i < n; i++)  {
            dp[i].resize(maxa+1);
        }
        for (int i = 0; i <= lis[0]; i++)  {
            dp[0][i] = 1;
        }
        for (int i = 1; i < n; i++)  {
            for (int j = 0; j <= maxa; j++)  {
                for (int k = j; k <= lis[i]; k++)  {
                    dp[i][k-j] += dp[i-1][j];
                    dp[i][k-j] %= mod;
                }
            }
        }
        cout << dp[n-1][0] << endl;
        return 0;
    } else  {
        int ans = 0;
        for (int delt = 0; delt <= mina; delt++)  {
            vector<vector<int>> dp(n);
            vector<int> pref(maxa+1);
            for (int i = 0; i < n; i++)  {
                dp[i].resize(maxa+1);
            }
            for (int i = 0; i <= lis[0]-delt; i++)  {
                dp[0][i] = 1;
                if (i != 0)   {
                    pref[i] = pref[i-1];
                }
                pref[i] += dp[0][i];
                pref[i] %= mod;
            }
            for (int j = lis[0]-delt+1; j <= maxa; j++)  {
                pref[j] = pref[j-1];
            }
            vector<int> temp(maxa+1);
            for (int i = 1; i < n; i++)  {
                for (int j = 0; j <= maxa; j++)  {
                    if (lis[i]-delt-j < 0)  {
                        temp[j] = temp[j-1];
                        continue;
                    }
                    dp[i][j] = pref[lis[i]-delt-j];
                    if (j != 0)  {
                        temp[j] = temp[j-1];
                    }
                    temp[j] += dp[i][j];
                    temp[j] %= mod;
                    /*for (int k = j; k <= lis[i]-delt; k++)  {
                        dp[i][k-j] += dp[i-1][j];
                        dp[i][k-j] %= mod;
                    }*/
                }
                pref = temp;
                fill(temp.begin(), temp.end(), 0);
            }
            ans += dp[n-1][0];
            ans %= mod;     
        }
        cout << ans << endl;
    }
}