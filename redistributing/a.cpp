#include <bits/stdc++.h>

using namespace std;

#define int long long

signed main()   {
    int n;
    cin >> n;
    vector<vector<int>> lis(n);
    for (int i = 0; i < n; i++) {
        bool tof = true;
        for (int j = 0; j < n; j++) {
            int x;
            cin >> x;
            x -= 1;
            if (tof == false)   {
                continue;
            }
            lis[i].push_back(x);
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
            vector<int> alr;
            //cout << "BEGIN " << mask << endl;
            map<int,int> ma;
            int cnt = 0;
            for (int i = 0; i < n; i++) {
                if (mask & (1 << i))    {
                    //cout << i << endl;
                    alr.push_back(i);
                    ma[i] = cnt;
                    cnt += 1;
                }
            }
            vector<int> temp((1 << alr.size()), 0);
            temp[0] = 1;
            for (int i = 0; i < alr.size(); i++)    {
                for (int curmask = (1<<alr.size())-1; curmask >= 0; curmask--)   {
                    for (int k : lis[alr[i]])   {
                        if (ma.find(k) == ma.end() || curmask & (1<<ma[k]))  {
                            continue;
                        }
                        temp[curmask ^ (1<<ma[k])] += temp[curmask];
                    }
                }
            }
            dp[mask] = temp[(1<<alr.size())-1];
        }
    }
    /*for (int i= 0 ; i < (1<<n); i++)    {
        cout << i << ' ' <<dp[i] << endl;
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
        cout << dp[fir] * dp[sec] <<endl;
    }
}