#include <bits/stdc++.h>

using namespace std;
#define int long long
int dist(pair<int, int> a, pair<int, int> b)    {
    return (a.first-b.first) * (a.first - b.first) + (a.second-b.second) * (a.second-b.second);
}

signed main()  {
    freopen("moocast.in","r",stdin);
	freopen("moocast.out","w",stdout);
    int n;
    cin >> n;
    vector<pair<int, int>> lis(n);
    for (int i = 0; i < n; i++) {
        cin >> lis[i].first >> lis[i].second;
    }
    vector<vector<pair<int,int>>> adj(n);
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++)   {
            adj[i].push_back(make_pair(dist(lis[i], lis[j]), j));
            adj[j].push_back(make_pair(dist(lis[i], lis[j]), i));
        }
    }
    int ma = 0;
    vector<bool> cont(n);
    cont[0] = true;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    for (auto i : adj[0])   {
        q.push(i);
    }
    while (!q.empty())  {
        pair<int, int> cur = q.top();
        int dis = cur.first;
        int num = cur.second;
        q.pop();
        if (cont[num] == true)  {
            continue;
        }
        //cout << dis << ' ' << num << endl;
        cont[num] = true;
        ma = max(ma, dis);
        for (auto i : adj[num]) {
            q.push(i);
        }
    }
    cout << ma << endl;
}