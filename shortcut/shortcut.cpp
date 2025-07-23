#include <bits/stdc++.h>

using namespace std;
long long n, m, t;
vector<vector<pair<long long, long long>>> adj;
vector<set<pair<long long, long long>>> adj2;
vector<long long> cows;
vector<long long> dist;
vector<vector<long long>> adj3;
vector<long long> agr;

long long dfs(long long cur)   {
    for (long long i : adj3[cur]) {
        agr[cur] += dfs(i);
    }
    agr[cur] += cows[cur];
    return agr[cur];
}

signed main()  {
    freopen("shortcut.in","r",stdin);
	freopen("shortcut.out","w",stdout);
    cin >> n >> m >> t;
    cows.resize(n);
    adj.resize(n);
    dist.resize(n);
    adj2.resize(n);
    adj3.resize(n);
    agr.resize(n);
    for (long long i = 0; i < n; i++) {
        cin >> cows[i];
    }
    for (long long i = 0; i < m; i++) {
        long long x, y, a;
        cin >> x >> y >> a;
        x -= 1;
        y -= 1;
        adj[x].push_back(make_pair(y, a));
        adj[y].push_back(make_pair(x, a));
        adj2[x].insert(make_pair(y, a));
        adj2[y].insert(make_pair(x, a));
    }
    priority_queue<pair<long long, long long>, vector<pair<long long, long long>>, greater<pair<long long, long long>>> q;
    q.push(make_pair(0, 0));
    vector<bool> visited(n);
    while (q.empty() == false)  {
        auto i = q.top();
        long long weig = i.first;
        long long num = i.second;
        q.pop();
        if (visited[num])   {
            continue;
        }
        visited[num] = true;
        dist[num] = weig;
        for (auto j : adj[num]) {
            if (visited[j.first])   {
                continue;
            }   
            q.push(make_pair(weig + j.second, j.first));
        }
    }
    for (long long i = 1; i < n; i++) {
        for (auto j : adj2[i])  {
            long long nxt = j.first;
            long long weg = j.second;
            //cout << i << ' ' << nxt << ' ' << weg << ' ' << dist[i] << ' ' << dist[nxt] << endl;
            if (dist[i] == dist[nxt] + weg)   {
                adj3[nxt].push_back(i);
                break;
            }
        }
    }
    dfs(0);
    long long ans = 0;
    for (long long i = 0; i < n; i++)   {
        ans = max(ans, agr[i] * (dist[i]-t));
    }
    cout << ans << endl;


}