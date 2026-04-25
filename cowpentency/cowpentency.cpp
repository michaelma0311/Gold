#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve()    {
    int n, q, c;
    cin >> n >> q >> c;
    const int mod = 1e9+7;
    vector<vector<int>> lis(n);
    vector<int> bad(n);
    vector<int> diff(n+1);
    for (int i = 0; i < q; i++)    {
        int a, b;
        cin >> a >> b;
        a -= 1;
        b -= 1;
        lis[b].push_back(a);
        if (b-a > 1)    {
            diff[a+1] += 1;
            diff[b] -= 1;
        }
        
    }
    int cur = 0;
    for (int i = 0; i < n; i++)    {
        cur += diff[i];
        bad[i] = cur;
        //cout << "JWEIGE " << bad[i] << endl;
    }
    vector<vector<int>> dp(n);
    for (int i = 0; i < n; i++)    {
        dp[i].resize(c);
    }
    for (int i = 0; i < c; i++)    {
        dp[0][i] = 1;
    }
    vector<int> pref(c);
    pref[0] = 1;
    for (int i = 1; i < c; i++) {
        pref[i] = pref[i-1] + dp[0][i];
    }
    vector<int> temp(c);
    for (int i = 1; i < n; i++)    {
        //case 2, val >= k
        fill(temp.begin(), temp.end(), 0);
        if (bad[i] <= 0)    {
            //cout << "AF" << endl;
            for (int j = 1; j < c; j++)    {
                dp[i][j] += ((pref[j] - dp[i-1][j])+mod)%mod;
                dp[i][j] %= mod;
                /*for (int k = 0; k < j; k++)    {
                    dp[i][j] += dp[i-1][k];
                    dp[i][j] %= mod;
                }*/
            }
        }
        //case 1, val < k
        if (lis[i].size() == 0)    {
            //cout << "INSIDE" << i << endl;
            for (int j = 0; j < c; j++)    {
                //cout << "CUR " << j << ' ' << dp[i-1][j] << endl;
                dp[i][j] += dp[i-1][j]*(j+1);
                dp[i][j] %= mod;
            }
        } 
        temp[0] = dp[i][0];
        for (int j = 1; j < c; j++) {
            temp[j] = temp[j-1] + dp[i][j];
            temp[j] %= mod;
        }
        /*cout << "BREAK" << endl;
        for (int j = 0; j < c; j++) {
            cout << dp[i][j] << ' ';
        }
        cout << endl;*/
        pref = temp;
        
    }
    /*for (int i = 0; i < n; i++) {
        for (int j = 0; j < c; j++) {
            cout << dp[i][j] << ' ';
        }
        cout << endl;
    }*/ 
    int ans = 0;
    for (int i = 0; i < c; i++)    {
        ans += dp[n-1][i];
        ans %= mod;
    }
    cout << ans << endl;
}

signed main()  {
    int t;
    t = 1;
    //cin >> t;
    for (int i =0 ; i < t; i++) {
        solve();
    }
}