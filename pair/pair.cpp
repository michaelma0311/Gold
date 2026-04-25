#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve()    {
    int n;
    cin >> n;
    string s, t;
    cin >> s >> t;
    const int mod = 1e9+7;
    vector<vector<int>> dp(n+1);
    vector<vector<bool>> cont(n+1);
    for (int i = 0; i <= n; i++)    {
        dp[i].resize(n+1);
        cont[i].resize(n+1);

    }
    for (int i = 0; i <= n; i++)    {
        dp[0][i] = 1;
        dp[i][0] = 1;
        cont[0][i] = true;
        cont[i][0] = true;
    }
    set<char> p;
    for (int i =0; i < 10; i++) {
        p.insert(char('0'+i));
    }
    for (int i = 1; i <= n; i++)    {
        for (int j = 1; j <= n; j++)    {
            if (s[i-1] != '0' && t[j-1] != '0') {
                dp[i][j] = dp[i-1][j] + dp[i][j-1];
                dp[i][j] %= mod;
                //cout << "in " << i << ' ' << j << ' '<< s[i-1] << ' ' << t[j-1] << ' '<< dp[i][j] << endl;
                if (cont[i-1][j] == true || cont[i][j-1] == true)   {
                    if (p.find(t[j-1]) != p.end() || p.find(s[i-1]) != p.end()) {
                        cont[i][j] = true;
                    } else  {
                        cont[i][j] = false;
                    }
                } else  {
                    cont[i][j] = false;
                }
                if (s[i-1] == t[j-1] && s[i-1] == '+')  {
                    dp[i][j] -= dp[i-1][j-1];
                    dp[i][j] += mod;
                    dp[i][j] %= mod;
                } else if ((s[i-1] == '1' && t[j-1] == '+') || (s[i-1] == '+' && t[j-1] == '1') || (s[i-1] == '1' && t[j-1] == '1') || (s[i-1] != '+' && t[j-1] != '+'))    {
                    dp[i][j] -= dp[i-1][j-1];
                    dp[i][j] += mod;
                    dp[i][j] %= mod;
                }
            } else if (s[i-1] == '0' && t[j-1] == '0')  {
                dp[i][j] = 1;
                cont[i][j] = true;
            } else if (s[i-1] == '0')   {
                if (p.find(t[j-1]) != p.end())  {
                    dp[i][j] = dp[i][j-1] + ((cont[i][j-1] == true) ? 0 : 1);
                    dp[i][j] %= mod;
                } else  {
                    dp[i][j] = dp[i][j-1] + 1;
                    dp[i][j] %= mod;
                }
                cont[i][j] = true;
            } else {
                if (p.find(s[i-1]) != p.end())  {
                    dp[i][j] = dp[i-1][j] + ((cont[i-1][j] == true) ? 0 : 1);
                    dp[i][j] %= mod;
                } else  {
                    dp[i][j] = dp[i-1][j] + 1;
                    dp[i][j] %= mod;
                }
                cont[i][j] = true;
            }
        }
    }
    /*for (int i = 0; i <= n; i++)    {
        for (int j = 0; j <= n; j++)    {
            cout << dp[i][j] << ' ';
        }
        cout << endl;
    }*/
    cout << dp[n][n] << endl;
}

signed main()   {
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        solve();
    }
}