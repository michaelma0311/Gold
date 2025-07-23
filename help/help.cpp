#include <bits/stdc++.h>

using namespace std;
#define int long long
long long power(long long x, long long y, long long M)
{
    if (y == 0)
        return 1;

    long long p = power(x, y / 2, M) % M;
    p = (p * p) % M;

    return (y % 2 == 0) ? p : (x * p) % M;
}
signed main()  {
    freopen("help.in", "r", stdin);
	freopen("help.out", "w", stdout);
    int n;
    cin >> n;
    const int mod = 1e9+7;
    vector<pair<int, int>> lis;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        lis.push_back({x, 1});
        lis.push_back({y, -1});
    }
    sort(lis.begin(), lis.end());
    for (auto i : lis)  {
        //cout << i.first << ' ' << i.second << "AD " << endl;
    }
    int cur = 0;
    int ans = 0;
    for (int i = 0; i < 2*n; i++) {
        int a, b;
        a = lis[i].first;
        b = lis[i].second;
        //cout << cur << ' ' << ans << endl;
        if (b == 1) {
            ans += power(2, n-1-cur, mod);
            ans %= mod;
        }
        cur += b;
    }
    cout << ans << endl;

}