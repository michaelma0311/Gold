#include <bits/stdc++.h>
using namespace std;

#define int long long
vector<vector<int>> adj;
vector<pair<int,int>> lis;
vector<pair<int,int>> ords;
int b;
bool tof;
vector<int> sol;
vector<pair<int,int>> ansma;
pair<int,int> dfs(int cur, int prev, int diff, int can)   {
    //cout << "GWEG " << cur << ' ' << prev << ' ' << diff << ' ' << can << endl;
    if (adj[cur].size() == 1 && prev != -1) {
        if (can == 1)    {
            //cout << "DIFF " << diff << endl;
            ords[cur] = {lis[cur].first-diff, lis[cur].second+diff};
        }
        return {lis[cur].first-diff, lis[cur].second+diff};
    }
    int l = 0;
    int r = INT_MAX;
    for (int i : adj[cur])  {
        if (i == prev)  {
            continue;
        }
        auto p = dfs(i, cur, diff, can);
        l = max(p.first, l);
        r = min(p.second, r);
    }
    if (r < lis[cur].first || l > lis[cur].second)  {
        tof = false;
    }
    if (can == 1)    {
        //cout << "DIFF " << diff << endl;
        ords[cur] = {max(l, lis[cur].first-diff), min(r, lis[cur].second+diff)};
    }
    return {max(l, lis[cur].first-diff), min(r, lis[cur].second+diff)};
}

bool check(int mid) {
    tof = true;
    pair<int,int> a = dfs(0, -1, mid, 0);
    //cout << "EC " << mid << ' ' << a.first << ' ' << a.second<<endl;
    return (a.first <= a.second && tof == true);
}
void dfs1(int cur, int prev, int ans)    {
    if (prev != -1) {
        int l = max(ansma[prev].first, max(ords[cur].first,lis[cur].first));
        int r = min(ansma[prev].second, min(ords[cur].second, lis[cur].second));
        //cout << "HERE " << cur << ' ' << l << ' ' <<r << endl;
        if (sol[prev]-ans<= lis[cur].first) {
            //cout << "SOLCURa " << cur << ' '<< lis[cur].second << ' ' << sol[prev]+ans << endl;
            sol[cur] = min(l, sol[prev]+ans);
            ansma[cur].first = max(ansma[prev].first,sol[cur]-ans);
            ansma[cur].second = min(ansma[prev].second, sol[cur]+ans);
            ///cout << sol[cur] << endl;
        } else  {
            //cout << "SOLCUR " <<cur << ' ' << lis[cur].bsecond << ' ' << sol[prev]+ans << endl;
            sol[cur] = min(r, sol[prev]+ans);
            ansma[cur].first = max(ansma[prev].first, sol[cur]-ans);
            ansma[cur].second = min(ansma[prev].second, sol[cur]+ans);
        }
    }
    for (int i : adj[cur])  {
        if (i == prev)  {
            continue;
        }
        dfs1(i, cur, ans);
    }
}
void solve()    {
    int n;
    cin >> n;
    adj.clear();
    adj.resize(n);
    lis.clear();
    lis.resize(n);
    ords.clear();
    ords.resize(n);
    sol.clear();
    sol.resize(n);
    ansma.clear();
    ansma.resize(n);
    for (int i = 1; i < n; i++) {
        int x;
        cin >> x;
        adj[i].push_back(x-1);
        adj[x-1].push_back(i);
    }
    for (int i = 0; i < n; i++) {
        cin >> lis[i].first >> lis[i].second;
    }
    int lo = 0;
    int hi = 1e9;
    int ans = 0;
    while (lo <= hi) {
        int mid = (lo+hi)/2;
        if (check(mid)) {
            ans = mid;
            hi = mid-1;
        } else  {
            lo = mid+1;
        }
    }
    if (b == 0) {
        cout << ans << endl;
        return;
    }
    cout<<ans << endl;
    pair<int,int> a = dfs(0, -1, ans, 1);
    for (int i = 0; i < n; i++) {
        //cout << "HER " << i << ' ' << ords[i].first << ' ' << ords[i].second << endl;
    }
    sol[0] = max(lis[0].first, ords[0].first);
    ansma[0] = {sol[0]-ans, sol[0]+ans};
    dfs1(0, -1, ans);
    for (int i = 0; i < n-1; i++)   {
        cout << sol[i] << ' ';
    }
    cout << sol[n-1] << endl;
}

signed main()   {
    int t;
    cin >> t >> b;
    for (int i = 0; i < t; i++) {
        solve();
    }
}