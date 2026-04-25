#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, m, k;
vector<vector<pair<int,int>>> adj;
vector<pair<int,int>> dist;
signed main()  {
    freopen("dining.in", "r", stdin);
    freopen("dining.out", "w", stdout);
    cin >> n >> m >> k;
    adj.resize(n);
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a -= 1;
        b -= 1;
        adj[a].push_back({b, c});
        adj[b].push_back({a, c});
    }
    vector<int> nums(n, -1);
    for (int i = 0; i < k; i++)  {
        int a, b;
        cin >> a >> b;
        a -= 1;
        nums[a] = max(nums[a], b);
    }
    priority_queue<pair<int,pair<int,bool>>, vector<pair<int,pair<int,bool>>>, greater<pair<int,pair<int,bool>>>> q;
    q.push({0, {n-1, ((nums[n-1] == -1) ? false : true)}});
    dist.resize(n, {INT_MAX, INT_MAX});
    dist[n-1] = {0,0};
    while (!q.empty()) {
        int cur = q.top().second.first;
        bool hasnum = q.top().second.second;
        int curdist = q.top().first;
        q.pop();
        if (hasnum == true)  { //already visited a special one
            if (curdist > dist[cur].first)  {
                continue;
            }
        } else  {
            if (curdist > dist[cur].second)  {
                continue;
            }
        }
        for (auto i : adj[cur]) {
            if (hasnum == true)  {
                if (curdist + i.second < dist[i.first].first)  {
                    dist[i.first].first = curdist + i.second;
                    q.push({curdist + i.second, {i.first, true}});
                }
            } else  {
                if (curdist + i.second < dist[i.first].second)  {
                    dist[i.first].second = curdist + i.second;
                    q.push({curdist + i.second, {i.first, false}});
                }
                if (nums[cur] != -1)  {
                    if (curdist + i.second - nums[cur] < dist[i.first].first)  {
                        dist[i.first].first = curdist + i.second - nums[cur];
                        q.push({curdist + i.second - nums[cur], {i.first, true}});
                    }
                }
            }
        }
    }
    for (int i = 0; i < n-1; i++)  {
        if (dist[i].first <= dist[i].second)  {
            cout << 1 << endl;
        } else  {
            cout << 0 << endl;
        }
    }
}