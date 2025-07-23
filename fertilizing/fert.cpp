#include <bits/stdc++.h>
using namespace std;

#define int long long

vector<int> par;
vector<vector<int>> child;
vector<int> siz;
vector<int> rates;

bool cmp(int b, int c)  {
    return rates[c] * siz[b] > rates[b] * siz[c];
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, t;
    cin >> n >> t;
    par.resize(n);
    child.resize(n);
    siz.resize(n);
    rates.resize(n);
    fill(siz.begin(), siz.end(), 0);
    fill(rates.begin(), rates.end(), 0);
    for (int a = 1; a < n; a++) {
        int cur;
        int rateSum;
        cin >> cur >> rateSum;
        cur -= 1;
        par[a] = cur;
        rates[a] = rateSum;
        child[cur].push_back(a);
    }

    vector<vector<int>> dp(2, vector<int>(n, 0));
    vector<int> depth(n, 0);
    for (int i = n - 1; i >= 0; i--) {
        siz[i] = 1;
        for (int j : child[i]) {
            siz[i] += siz[j];
            rates[i] += rates[j];
            dp[0][i] += dp[0][j];
            depth[i] = max(depth[i], depth[j] + 1);
        }

        sort(child[i].begin(), child[i].end(), cmp);

        int cursum = 0;
        for (int j : child[i]) {
            dp[0][i] += ((int)2 * siz[j]) * cursum;
            cursum += rates[j];
        }
        dp[0][i] += cursum;

        if (!child[i].empty()) {
            dp[1][i] = LLONG_MAX;

            cursum = 0;
            int curdept = 0;
            for (int j : child[i]) {
                if (depth[j] + 1 == depth[i]) {
                    dp[1][i] = min(dp[1][i], dp[0][i] - (((int)2 * siz[j]) * cursum) + (curdept * rates[j]) - dp[0][j] + dp[1][j]);
                }
                cursum += rates[j];
                curdept += (int)2 * siz[j];
            }
        }
    }
    if (t == 0) {
        cout << (2 * (n - 1)) << " " << dp[0][0] << "\n";
    } else {
        cout << ((2 * (n - 1)) - depth[0]) << " " << dp[1][0] << "\n";
    }

    return 0;
}
