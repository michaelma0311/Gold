#include <bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 1e9+7;
signed main()   {
    int n;
    cin >> n;
    vector<int> lis(n);
    for (int i = 0; i < n; i++) {
        cin >> lis[i];
    }
    if (n%2 == 1)  {

    
        vector<vector<vector<int>>> dp(n);
        const int curm = 101; 
        for (int i = 0; i < n; i++) {
            dp[i].resize(curm);
            for (int j = 0; j < curm; j++)  {
                dp[i][j].resize(curm);
            }
        }
        for (int i = 0; i <= lis[0]; i++)   {
            dp[0][i][lis[0]-i] = 1;
        }
        //cout << "A" << endl;
        for (int i = 1; i < n; i++) {
            //cout << i << endl;
            for (int curdiff = 0; curdiff < curm; curdiff++)  {
                for (int k = 0; k < curm; k++)  {
                    if (i%2 == 0)   { //even, curdiff has to be positive
                        for (int cur = curdiff; cur <= lis[i]; cur++)  {
                            //cout << i << ' ' << curdiff << ' ' << k << ' ' << cur << endl;
                            if (lis[i]-cur >= k)    {
                                dp[i][cur-curdiff][k] += dp[i-1][curdiff][k];
                                dp[i][cur-curdiff][k] %= mod;
                                /*for (int p = curm; p >= k; p--) {
                                    if (dp[i-1][curdiff][p] == 0)   {
                                        continue;
                                    }
                                    dp[i][curdiff+cur][k] += dp[i-1][curdiff][p];
                                }*/
                                //dp[i][curdiff+cur][k] += dp[i-1][curdiff][k];
                            } else  {
                                dp[i][cur-curdiff][lis[i]-cur] += dp[i-1][curdiff][k];
                                dp[i][cur-curdiff][lis[i]-cur] %= mod;
                            }
                        }
                    } else  { //odd, curdiff has to be negative
                        for (int cur = curdiff; cur <= lis[i]; cur++)   {
                            //cout << cur << ' ' << curdiff << endl;
                            if (lis[i]-cur >= k)    {
                                /*for (int p = curm; p >= k; p--) {
                                    if (dp[i-1][curdiff][p] == 0)   {
                                        continue;
                                    }
                                    dp[i][-(curdiff-cur)][k] += dp[i-1][curdiff][p];
                                }*/
                                dp[i][cur-curdiff][k] += dp[i-1][curdiff][k];
                                dp[i][cur-curdiff][k] %= mod;
                            } else  {
                                dp[i][cur-curdiff][lis[i]-cur] += dp[i-1][curdiff][k];
                                dp[i][cur-curdiff][lis[i]-cur] %= mod;
                            }
                        }
                    }
                }
            }
        }
        int ans = 0;
        for (int i = 0; i < 10; i++)  {
            ans += (dp[n-1][0][i] * (i+1))%mod;
            ans %= mod;
        }
        cout << ans << endl;
    } else  {
        vector<vector<vector<pair<int,int>>>> dp(n);
        const int curm = 101; 
        for (int i = 0; i < n; i++) {
            dp[i].resize(curm);
            for (int j = 0; j < curm; j++)  {
                dp[i][j].resize(curm);
            }
        }
        for (int i = 0; i <= lis[0]; i++)   { //last is 0 if one value is 0
            if (i == 0)  {
                dp[0][i][lis[0]-i] = {1,0};
            } else  {
                dp[0][i][lis[0]-i] = {0,1};
            }
        }
        //cout << "A" << endl;
        for (int i = 1; i < n; i++) {
            //cout << i << endl;
            for (int curdiff = 0; curdiff < curm; curdiff++)  {
                for (int k = 0; k < curm; k++)  {
                    //even, curdiff has to be positive
                    for (int cur = curdiff; cur <= lis[i]; cur++)  {
                        //cout << i << ' ' << curdiff << ' ' << k << ' ' << cur << endl;
                        if (lis[i]-cur >= k)    {
                            if (cur == 0)  {
                                dp[i][cur-curdiff][k].first += dp[i-1][curdiff][k].second;
                                dp[i][cur-curdiff][k].first %= mod;
                                dp[i][cur-curdiff][k].second += dp[i-1][curdiff][k].second;
                                dp[i][cur-curdiff][k].second %= mod;
                            } else  {
                                dp[i][cur-curdiff][k].first += dp[i-1][curdiff][k].first;
                                dp[i][cur-curdiff][k].first %= mod;
                                dp[i][cur-curdiff][k].second += dp[i-1][curdiff][k].second;
                                dp[i][cur-curdiff][k].second %= mod;
                            }
                            /*for (int p = curm; p >= k; p--) {
                                if (dp[i-1][curdiff][p] == 0)   {
                                    continue;
                                }
                                dp[i][curdiff+cur][k] += dp[i-1][curdiff][p];
                            }*/
                            //dp[i][curdiff+cur][k] += dp[i-1][curdiff][k];
                        } else  {
                            if (cur == 0)  {
                                dp[i][cur-curdiff][lis[i]-cur].first += dp[i-1][curdiff][k].second;
                                dp[i][cur-curdiff][lis[i]-cur].first %= mod;
                                dp[i][cur-curdiff][lis[i]-cur].second += dp[i-1][curdiff][k].second;
                                dp[i][cur-curdiff][lis[i]-cur].second %= mod;
                            } else  {
                                dp[i][cur-curdiff][lis[i]-cur].first += dp[i-1][curdiff][k].first;
                                dp[i][cur-curdiff][lis[i]-cur].first %= mod;
                                dp[i][cur-curdiff][lis[i]-cur].second += dp[i-1][curdiff][k].second;
                                dp[i][cur-curdiff][lis[i]-cur].second %= mod;
                            }
                        }
                    
                    } 
                }
            }
        }
        int ans = 0;
        for (int i = 0; i < 10; i++)  {
            cout << dp[n-1][0][i].first  << endl;
            ans += (dp[n-1][0][i].first * (i+1))%mod;
            ans %= mod;
        }
        cout << ans << endl;
    }
    
}