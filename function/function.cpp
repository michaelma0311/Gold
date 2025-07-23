
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n;
vector<int> lis;
vector<vector<int>> adj;
vector<int> cost;
vector<int> iscyc;
vector<int> visited;
vector<bool> finalvis;
vector<vector<int>> dp;
void mark(int start, int cur, int s)  {
    if (cur == start && s != -1)    {
        return;
    }
    iscyc[cur] = 1;
    if (lis[cur] == cur)    {
        iscyc[cur] = 2;
    }
    if (iscyc[lis[cur]] == false)   {
        mark(start, lis[cur], 1);
    }
}

bool dfs(int cur)   {
    //cout << "HIad " << cur << ' ' << lis[cur] << ' ' << visited[lis[cur]]<< endl;
    visited[cur] = 1;
    if (visited[lis[cur]] == 1) {
        mark(cur, cur, -1);
        visited[cur] = 2;
        return true;
    } else if (visited[lis[cur]] == 0)  {
        dfs(lis[cur]);
    }
    visited[cur] = 2;
    return false;
}

void solve(int start, int cur, int a) {
    //dp[i][0] = is pointing to itself
    //dp[i][1] = is pointing to somehting else
    //cout << "INSIDE " << start << ' ' << cur << ' '<< a << endl;
    if (finalvis[cur])  {
        return;
    }
    if (a < 0)  {
        finalvis[cur] = true;
    }
    if (adj[cur].size() == 0)   {
        dp[cur][0] = cost[cur];
        dp[cur][1] = 0;
        return;
    }
    dp[cur][0] = 0;
    dp[cur][1] = 0;
    for (int i : adj[cur])  {
        if (a != -1 && i == start)   {
            continue;
        }
        if (i == cur)   {
            continue;
        }
        solve(start, i, a);
        dp[cur][0] += min(dp[i][0], dp[i][1]);
        dp[cur][1] += dp[i][0];
    }
    if (lis[cur] != cur)    {
        dp[cur][0] += cost[cur];
    }
}

signed main()  {
    int n;
    cin >> n;
    adj.resize(n);
    cost.resize(n);
    visited.resize(n);
    lis.resize(n);
    iscyc.resize(n);
    visited.resize(n);
    finalvis.resize(n);
    dp.resize(n);
    int ans = 0;
    for (int i = 0; i < n; i++) {
        dp[i].resize(2);
        int a;
        cin >> a;
        a -= 1;
        lis[i] = a;
        adj[a].push_back(i);
    }
    for (int i = 0; i < n; i++) {
        cin >> cost[i];
    }
    for (int i = 0; i < n; i++) {
        if (visited[i] == 0)    {
            //cout << i << endl;
            dfs(i);
        }
    }
    for (int i = 0; i < n; i++) {
        if (finalvis[i])    {
            continue;
        } else if (iscyc[i] == 2)   {
           // cout << "BYE " << i+1 << endl;
            solve(i, i, -1);
            //cout << dp[i][0] << "AGUOW " << endl;
            ans += dp[i][0];
        } else if (iscyc[i] == 1)   {
            //cout <<" HI " << i+1 << endl;
            int p = LLONG_MAX;
            solve(i, i, 1);
            p = min(p, dp[i][0]);
            solve(lis[i], lis[i], -2);
            p = min(p, dp[lis[i]][0]);
            ans += p;
        }
    }
    cout << ans << endl;
}   