#include <bits/stdc++.h> 
using namespace std;
#define int long long

signed main()  {
    int n;
    cin >> n;
    string s;
    cin >> s;
    const int mod = 1e9+7;
    vector<int> dp(n+1);
    dp[0] = 1;
    vector<int> a(n+1);
    vector<int> b(n+1);
    for (int i = 1; i <= n; i++)    {
        a[i] = a[i-1] + (s[i-1] == 'R');
        b[i] = b[i-1] + (s[i-1] == 'B');
    }
    /*for (int i = 0; i <= n; i++)    {
        cout << a[i] << ' ';
    }
    cout << endl;
    for (int i = 0; i <= n; i++) {
        cout << b[i] << ' ';
    }
    cout << endl;*/
    queue<pair<int,int>> even;
    queue<pair<int,int>> odd;
    int cursumeven = 0;
    int cursumodd = 0;
    int lastr = -1;
    int bafterr = -1;
    int lastb = -1;
    for (int i = 1; i <= n; i++) {
        if (s[i-1] == 'R')  {
            lastr = i-1;
            bafterr = lastb;
            even.clear();
            odd.clear();
            cursumeven = 0;
            cursumodd = 0;
            continue;
        }
        if (s[i-1] == 'X')  {
            dp[i] += dp[i-1];
            dp[i] %= mod;
        }
        if (i%2 ==0)    {
            if (even.empty() == false)  {
                if (even.front())
            }
        }   
    }
    /*for (int i : dp)    {
        cout << i << ' ';
    }
    cout << endl;*/
    cout << dp[n] << endl;
}