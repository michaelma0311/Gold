#include <bits/stdc++.h>
using namespace std;
int n, k;
vector<vector<int>> adj;
vector<int> distb;
vector<int> distf;

void dfs(int cur, int prev, int cnt)   {
    distb[cur] = cnt;
    for (int i : adj[cur])  {
        if (i != prev)  {
            dfs(i, cur, cnt+1);
        }
    }
}

int main()  {
    freopen("atlarge.in","r",stdin);
	freopen("atlarge.out","w",stdout);
    cin >> n >> k;
    k -= 1;
    adj.resize(n);
    distb.resize(n);
    distf.resize(n);
    fill(distf.begin(), distf.end(), INT_MAX);
    for (int i = 0; i < n-1; i++)   {
        int a, b;
        cin >> a >> b;
        a -= 1;
        b -= 1;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(k, -1, 0);
    queue<pair<int, int>> q;
    for (int i = 0; i < n; i++) {
        if (adj[i].size() == 1) {
            distf[i] = 0;
            q.push({i, -1});
        }
    }
    while (!q.empty())  {
        int cur = q.front().first;
        int prev = q.front().second;
        q.pop();
        for (int i : adj[cur]) {
            if (i == prev)  {
                continue;
            }
            if (distf[i] > distf[cur] + 1)  {
                distf[i] = distf[cur] + 1;
                q.push({i, cur});
            }
        }
    }
    q.push({k, -1});
    int ans = 0;
    while (!q.empty())  {
        int cur = q.front().first;
        int prev = q.front().second;
        q.pop();
        if (distf[cur] <= distb[cur])   {
            ans += 1;
            continue;
        }
        for (int i : adj[cur])  {
            if (i != prev)  {
                q.push({i, cur});
            }
        }
    }
    cout << ans << endl;

    
}