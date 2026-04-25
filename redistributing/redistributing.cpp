#include <bits/stdc++.h>

using namespace std;

#define int long long

signed main()   {
    int n;
    cin >> n;
    vector<set<int>> lis(n);
    for (int i = 0; i < n; i++) {
        bool tof = true;
        for (int j = 0; j < n; j++) {
            int x;
            cin >> x;
            x -= 1;
            if (tof == false)   {
                continue;
            }
            //cout << "WGEG " << i << ' ' << x << endl;
            lis[i].insert(x);
            if (x == i) {
                tof = false;
            }
        }
    }
    /*for (int i = 0; i < n; i++) {
        cout << "I " << i << endl;
        for (int j : lis[i])    {
            cout << j << ' ';
        }
        cout << endl;
    }*/
    vector<vector<int>> dp(1 << n);
    vector<int> ans(1<<n);
    for (int i = 0; i < (1<<n); i++)    {
        dp[i].resize(n);
    }
    ans[0] = 1;
    for (int i =0 ; i < n; i++) {
        dp[(1<<i)][i] = 1;
    }
    for (int i = 0; i < n; i++) {
        vector<vector<int>> temp(1<<n);
        for (int j = 0; j < (1<<n); j++)    {
            temp[j].resize(n);
            temp[j][i] = dp[j][i];
        }
        for (int mask = 1; mask < (1<<n); mask++)    {
            for (int last = 0; last < n; last++)    {
                if (temp[mask][last] == 0)  {
                    continue;
                }
                //cout << "HI " << mask << ' ' << last << endl;
                if (lis[last].find(i) != lis[last].end())   {
                    ans[mask] += temp[mask][last];
                    for (int k = i+1; k < n; k++) {
                        if ((mask & (1 << k)) == 0)   {
                            dp[mask ^ (1<<k)][k] += temp[mask][last];
                        }
                    }
                }
                for (int k = 0; k < i; k++) {
                    //cout << mask << ' ' << i << ' ' << last << ' ' << k << ' ' << (mask&(1<<k)) << endl;
                    if ((mask & (1 << k)) == 0 && lis[last].find(k) != lis[last].end())   {
                        //cout << "SPERAD " << endl;
                        temp[mask^(1<<k)][k] += temp[mask][last];
                    }
                }
            }
        }
    }
    /*for (int i= 0 ; i < (1<<n); i++)    {
        cout << i << ' ' <<ans[i] << endl;
    }*/
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        string s;
        cin >> s;
        int fir = 0;
        int sec = 0;
        for (int j = 0; j < n; j++) {
            if (s[j] == 'H')    {
                fir ^= (1 << j);
            } else  {
                sec ^= (1 << j);
            }
        }
        cout << ans[fir] * ans[sec] <<endl;
    }
}