#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main()  {
    //freopen("test.in", "r", stdin);
    string s;
    cin >> s;
    string b = "bessie";
    int curon = 0;
    int n = s.length();
    vector<int> cost(n);
    for (int i =0 ; i < n; i++) {
        cin >> cost[i];
    }
    for (int i = 0; i < n; i++) {
        if (s[i] == b[curon%6])   {
            curon += 1;
        }
    }
   
    int ma = curon/6;
    //cout << ma << endl;
    vector<vector<pair<int,int>>> dp(n+1);
    //cout << "WGWEG " << endl;
    for (int i = 0; i <= n; i++) {
        dp[i].resize(6);
        fill(dp[i].begin(), dp[i].end(), make_pair(0, INT_MAX));
    }
    //cout << n << ' ' << ma << endl;
    dp[0][0] = {0, 0};
    for (int i = 0; i < n; i++)   {
        dp[i+1][0] = dp[i][0];
        //dp[i+1][0][k] = dp[i][0][k];
        for (int j = 0; j < 6; j++) {
            int cursu = dp[i][j].second;
            int val = dp[i][j].first;
            //cout << i << ' ' << j << ' ' << cursu << ' ' << val << endl;
            if (cursu != INT_MAX)   {
                if (dp[i+1][j].first == val)    {
                    dp[i+1][j] = {val, min(dp[i+1][j].second, cursu+cost[i])};
                } else if (dp[i+1][j].first < val) {
                    dp[i+1][j] = {val, cursu+cost[i]};
                }
            }
            //dp[i+1][j][k] = min(dp[i+1][j][k], dp[i][j][k] + cost[i]);
            if (j != 5) {
                if (b[j] == s[i])   {
                    if (cursu != INT_MAX)   {
                        if (dp[i+1][j+1].first == val)    {
                            dp[i+1][j+1] = {val, min(dp[i+1][j+1].second, cursu)};
                        } else if (dp[i+1][j+1].first < val)   {
                            dp[i+1][j+1] = {val, cursu};
                        }
                    }
                    //dp[i+1][j+1][k] = min(dp[i+1][j+1][k], dp[i][j][k]);
                }
            } else  {
                if (b[j] == s[i])   {
                    //cout << "HI " << ' ' << val << ' ' << cursu << endl;
                    if (cursu != INT_MAX)   {
                        if (dp[i+1][0].first == val+1)    {
                            dp[i+1][0] = {val+1, min(dp[i+1][0].second, cursu)};
                        } else if (dp[i+1][0].first < val+1)   {
                            dp[i+1][0] = {val+1, cursu};
                        }
                    }
                    //dp[i+1][0][k+1] = min(dp[i+1][0][k+1], dp[i][j][k]);
                }
            }
        }
    }
    int ans = INT_MAX;
    for (int i = 0; i < 6; i++) {
        if (dp[n][i].first == ma)   {
            ans = min(ans, dp[n][i].second );
        }
        //ans = min(ans, dp[n][i][ma]);
    }
    cout << ma << endl;
    cout << ans << endl;
}