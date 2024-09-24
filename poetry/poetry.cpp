#include <bits/stdc++.h>
using namespace std;
long long power(long long x, long long y, long long M)
{
    if (y == 0)
        return 1;

    long long p = power(x, y / 2, M) % M;
    p = (p * p) % M;

    return (y % 2 == 0) ? p : (x * p) % M;
}
int main()  {
    freopen("poetry.in", "r", stdin);
	freopen("poetry.out", "w", stdout);
    long long n, m, k;
    cin >> n >> m >> k;
    vector<pair<long long, long long>> lis(n);
    for (long long i = 0; i < n; i++) {
        long long x, y;
        cin >> x >> y;
        y -= 1;
        lis[i] = make_pair(x, y);
    }
    sort(lis.begin(), lis.end());
    long long colors[5001] = {0};
    long long dp[k+1] = {0};
    dp[0] = 1;
    long long result[5001];
    const long long mo = 1e9+7;
    for (long long i = 0; i < k; i++) {
        for (auto j : lis)  {
            if (j.first + i > k)    {
                break;
            } else if (j.first + i == k)    {
                //cout << j.first << ' ' << j.second+1 << ' ' << i << ' ' << dp[i] << endl;
                dp[j.first+i] += dp[i];
                dp[j.first+i]%= mo;
                //cout << "INSIDE " << dp[k] << endl;
                //result[j.second] = dp[k];
                colors[j.second] += dp[i];
                colors[j.second] %= mo;
            } else  {
                dp[j.first+i] += dp[i];
                dp[j.first+i] %= mo;
            }
        }
    }
    long long arr[26];
    for (long long i = 0; i < m; i++) {
        char a;
        cin >> a;
        char b = (char)tolower(a);
        arr[b-'a'] += 1;
    }
    long long ans = 1;
    
    for (long long i = 0; i < 26; i++) {
        long long temp = 0;
        for (long long j : colors)  {
            //cout << j << ' ' << arr[i] << ' ' << endl;
            if (arr[i] == 0)    {
                continue;
            }
            temp += power(j, arr[i], mo);
            temp %= mo;
            //cout << "INSDE " << temp << endl;
        }
        if (temp == 0)  {
            continue;
        }
        ans *= temp;
        ans %= mo;
        //cout << ans << endl;
    }
    cout << ans << endl;
}