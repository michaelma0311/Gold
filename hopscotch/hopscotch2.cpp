#include <bits/stdc++.h>
using namespace std;
long long mod = 1e9+7;
void update(vector<long long>& tr, long long pos, long long val) {
    for (long long i = pos; i <= tr.size(); i |= (i + 1)) {
        tr[i] += val;		
        tr[i] %= mod;
    }
}
long long query(vector<long long>& tr, long long pos) {
    long long res = 0;
    for (long long i = pos; i >= 0; i = (i&(i + 1)) - 1) {
        res += tr[i];	
        res %= mod;
    }
    return res%mod;
}

signed main()  {
    freopen("hopscotch.in", "r", stdin);
    freopen("hopscotch.out", "w", stdout);
    long long r, c, k;
    cin >> r >> c >> k;
    vector<vector<long long>> grid(r);
    for (long long i = 0; i < r; i++) {
        grid[i].resize(c);
    }
    for (long long i = 0; i < r; i++) {
        for (long long j = 0; j < c; j++) {
            cin >> grid[i][j];
            grid[i][j] -= 1;
        }
    }
    vector<long long> full(c);
    fill(full.begin(), full.end(), 0);
    vector<vector<long long>> colors(k);
    for (long long i = 0; i < k; i++) {
        colors[i].resize(c);
        fill(colors[i].begin(), colors[i].end(), 0);
    }
    update(full, 0, 1);
    update(colors[grid[0][0]], 0, 1);
    for (long long i = 1; i < r-1; i++) {
        for (long long j = c-1; j >= 1; j--)   {
            long long val = query(full, j-1) - query(colors[grid[i][j]], j-1);
            if (val < 0)    {
                val += mod;
            }
            val %= mod;
            //cout << i << ' ' << j << ' ' << val << endl;
            update(full, j, val);
            update(colors[grid[i][j]], j, val);
        }
    }
    //cout << "HI " << query(full, c-1) << ' ' << query(colors[grid[r-1][c-1]], c-1) << endl;
    long long ans = query(full, c-2) - query(colors[grid[r-1][c-1]], c-2);
    if (ans < 0)    {
        ans += mod;
    }
    ans %= mod;
    cout << ans << endl;
}