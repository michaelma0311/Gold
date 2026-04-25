#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main()   {
    string s;
    cin >> s; //A = 0, G = 1, C = 2, T = 3
    const int mod = 1e9+7;
    map<char,vector<int>> ma;
    ma['A'] = {0};
    ma['G'] = {1};
    ma['C'] = {2};
    ma['T'] = {3};
    ma['?'] = {0,1,2,3};
    int n = s.length();
    int dp[n][4][4][4];
    memset(dp, 0, sizeof(dp));
    for (int j : ma[s[0]])  {
        for (int k = 0; k < 4; k++) {
            dp[0][j][j][k] = 1;
        }
    }
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                for (int p : ma[s[i-1]])    {
                    for (int q : ma[s[i]])    {
                        if (p == q && k == p) {
                            dp[i][q][q][j] += dp[i-1][j][p][k];
                            dp[i][q][q][j] %= mod;
                        } else  {
                            if (p != q) {
                                dp[i][j][q][k] += dp[i-1][j][p][k];
                                dp[i][j][q][k] %= mod;
                            }
                        }
                        if (p != q && k == p) {
                            dp[i][q][q][j] += dp[i-1][j][p][k];
                            dp[i][q][q][j] %= mod;
                        }
                    }
                }
            }
        }
    }
    /*for (int i = 0; i < n; i++) {
        cout << "I " << i << endl;
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                for (int p = 0; p < 4; p++) {
                    cout << dp[i][j][k][p] << ' ';
                }
                cout << endl;
            }
            cout << "----" << endl;
        }
    }*/
    int ans = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            ans += dp[n-1][i][j][j];
            ans %= mod;
        }
    }
    cout << ans << endl;
}