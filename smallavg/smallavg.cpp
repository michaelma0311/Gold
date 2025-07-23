#include <bits/stdc++.h>

using namespace std;
#define int long long
signed main()  {
    int n;
    cin >> n;
    vector<int> a(n);
    vector<int> b(n);
    int mod = 1e9+7;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    vector<int> prefa(n);
    vector<int> prefb(n);
    prefa[0] = a[0];
    prefb[0] = b[0];
    for (int i = 1; i < n; i++) {
        prefa[i] = prefa[i-1] + a[i];
        prefb[i] = prefb[i-1] + b[i];
    }
    vector<vector<int>> dp(n);
    for (int i =0; i < n; i++)  {
        dp[i].resize(n);
    }
    for (int i = 0; i < n; i++) {
        if (prefa[i] / (i+1) <= prefb[0])   {
            dp[0][i] = 1;
        }    
        if (prefb[i]/(i+1) >= prefa[0]) {
            dp[i][0] = 1;
        }
    }
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            if (prefa[i] * (j+1) <= prefb[i] * (i+1))    {
                dp[i][j] += 1;
                dp[i][j] %= mod;
            }
            for (int len = 1; len <= min(i, j); len++)  {
                
                if (dp[i-len][j-len] == 0)  {
                    continue;
                }
                int counta = prefa[i] - prefa[i-len];
                int countb = prefb[j] - prefb[j-len];
                if (counta <= countb)   {
                    dp[i][j] += dp[i-len][j-len];
                    dp[i][j] %= mod;
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << dp[i][j] << ' ';
        }
        cout << endl;
    }
    cout << dp[n-1][n-1] << endl;
}