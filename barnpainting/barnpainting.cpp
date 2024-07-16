#include <bits/stdc++.h>

using namespace std;
long long n, k;
vector<vector<long long>> adj;
vector<vector<long long>> dp;
const long long mx = 1e5 + 1, MOD = 1e9 + 7;
void dfs(long long cur, long long prev) {
    for (long long i : adj[cur])  {
        if (i != prev)  {
            dfs(i, cur);
            dp[cur][0] *= dp[i][1] + dp[i][2];
            dp[cur][1] *= dp[i][0] + dp[i][2];
            dp[cur][2] *= dp[i][0] + dp[i][1];
            dp[cur][0] %= MOD;
            dp[cur][1] %= MOD;
            dp[cur][2] %= MOD;
        }
    }
}
int main()  {
    freopen("barnpainting.in","r",stdin);
	freopen("barnpainting.out","w",stdout);

    cin >> n >> k;
    adj.resize(n);
    dp.resize(n);
    for (long long i = 0; i < n; i++) {
        dp[i].resize(3);
        dp[i][0] = 1;
        dp[i][1] = 1;
        dp[i][2] = 1;
    }
    for (long long i = 0; i < n-1; i++) {
        long long x, y;
        cin >> x >> y;
        x -= 1;
        y -= 1;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    for (long long i = 0; i < k; i++) {
        long long a, b;
        cin >> a >> b;
        a -= 1;
        dp[a][0] = 0;
        dp[a][1] = 0;
        dp[a][2] = 0;
        dp[a][b-1] = 1; 
    }
    dfs(0, -1);
    cout << (dp[0][0] + dp[0][1] + dp[0][2]) % MOD;
}