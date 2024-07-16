#include <bits/stdc++.h>

using namespace std;
int n, m, c;
vector<int> topor;
vector<int> start;
vector<vector<pair<int, int>>> back;
vector<vector<pair<int, int>>> adj;
vector<int> visited;
vector<int> ans;
void dfs(int cur)   {
    //cout << cur << endl;
    if (visited[cur] == true)   {
        return;
    }
    visited[cur] = true;
    if (adj[cur].size() == 0)   {
        topor.push_back(cur);
        return;
    }
    for (auto i : adj[cur])  {
        if (!visited[i.first])  {
            dfs(i.first);
        }
    }
    topor.push_back(cur);
}

int main()  {
    freopen("timeline.in","r",stdin);
	freopen("timeline.out","w",stdout);
    cin >> n >> m >> c;
    start.resize(n);
    back.resize(n);
    adj.resize(n);
    visited.resize(n);
    ans.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> start[i];
    }
    for (int i = 0; i < c; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        x -= 1;
        y -= 1;
        adj[x].push_back(make_pair(y, z));
        back[y].push_back(make_pair(x, z));
    }
    for (int i = 0; i < n; i++) {
        if (!visited[i])    {
            dfs(i);
        }
    }
    //cout << "ADAD" << endl;
    reverse(topor.begin(), topor.end());
    for (int i : topor) {
        if (back[i].size() == 0)    {
            ans[i] = start[i];
        } else  {
            int temp = 0;
            for (auto j : back[i])   {
                temp = max(temp, ans[j.first] + j.second);
            }
            ans[i] = max(start[i], temp);
        }
    }
    for (int i : ans)   {
        cout << i << endl;
    }
    
}