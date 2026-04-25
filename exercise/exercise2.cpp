#include <bits/stdc++.h>
using namespace std;
#define int long long
vector<int> gen(int n) {
    vector<bool> can(n+1, true);
    can[0] =false;
    can[1] = false;

    for (int i = 2; i*i <= n; i++) {
        if (can[i]) {
            for (int j = i*i; j <= n; j+=i) {
                can[j] = false;
            }
        }
    }
    vector<int> ans;
    for (int i = 2; i <= n; i++) {
        if (can[i]) {
            ans.push_back(i);
        }
    }
    return ans;
}
signed main()   {
    freopen("exercise.in", "r", stdin);
    freopen("exercise.out", "w", stdout);
    int n, mod;
    cin >> n >> mod;
    vector<int> dp(n+1, 0);
    map<int,int> most;
    
    dp[0] = 1;
    vector<int> primes = gen(n);
    for (int i = 2; i <= n; i++)    {
        if (find(primes.begin(), primes.end(), i) == primes.end())  {
            primes.push_back(i);
        }
    }
    for (int i = 2; i <= n; i++)    {
        int mos = 0;
        int cur = i;
        for (int ind = 0; ind < n; ind++)   {
            if (cur == 1)   {
                break;
            }
            int p = 0;
            while (cur%primes[ind] == 0)    {
                p += 1;
                cur /= primes[ind];
            }
            most[primes[ind]] = max(most[primes[ind]], p);
        }
    }
    for (int i : primes)    {
        //cout << "HI " << i << ' ' << most[i] << endl;
        for (int j = n; j >= 0; j--)    {
            if (dp[j] == 0)    {
                continue;
            }
            for (int p = most[i]; p >= 1; p--)  {
                if (j+pow(i, p) > n)  {
                    continue;
                }
                int a = (dp[j]*pow(i, p));
                a %= mod;
                dp[j+pow(i, p)] += a;
                dp[j+pow(i, p)] %= mod;
            }
            /*dp[j+i] += dp[j] * i;
            dp[j+i] %= mod;*/
        }
    }
    int ans = 0;
    for (int i = 0; i <= n; i++)    {
        if (dp[i] == -1)    {
            continue;
        }
        //cout << i << ' ' << dp[i] << endl;
        ans += dp[i];
        ans %= mod;
    }
    
    cout << ans << endl;

}