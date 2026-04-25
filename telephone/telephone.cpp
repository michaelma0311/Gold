#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main()  {
    //freopen("a.in", "r", stdin);
    int n, k;
    cin >> n >> k;
    vector<int> lis(n);
    map<int,vector<int>> ma;
    for (int i = 0; i < n; i++) {
        cin >> lis[i];
        lis[i] -= 1;
        ma[lis[i]].push_back(i);
    }
    vector<vector<int>> adj(n);
    for (int i = 0; i < k; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < k; j++) {
            if (s[j] == '1') {
                adj[i].push_back(j);
            }
        }
    }
    vector<int> dist(n, LLONG_MAX);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push({0,0});
    dist[0] = 0;
    while (!pq.empty()) {
        int curweg = pq.top().first;
        int cur = pq.top().second;
        pq.pop();
        if (curweg > dist[cur]) {
            continue;
        }
        for (int col : adj[lis[cur]]) {
            int p = ma[col].size();
            if (p != 0) {
                p -= 1;
                int newdis = curweg + abs(ma[col][p]-cur);
                if (newdis < dist[ma[col][p]]) {
                    dist[ma[col][p]] = newdis;
                    pq.push({newdis, ma[col][p]});
                }
            }
            if (lis[cur] == col)    {
                auto it = upper_bound(ma[col].begin(), ma[col].end(), cur);
                if (it == ma[col].end())    {
                    int p = it-ma[col].begin();
                    p -= 2;
                    if (p < 0) {
                        continue;
                    }
                    int newdis = curweg + abs(ma[col][p]-cur);
                    if (newdis < dist[ma[col][p]]) {
                        dist[ma[col][p]] = newdis;
                        pq.push({newdis, ma[col][p]});
                    }
                } else {
                    int p = it-ma[col].begin();
                    if (p >= 0) {
                        int newdis = curweg + abs(ma[col][p]-cur);
                        if (newdis < dist[ma[col][p]]) {
                            dist[ma[col][p]] = newdis;
                            pq.push({newdis, ma[col][p]});
                        }
                    }
                    p -= 2;
                    if (p >= 0) {
                        int newdis = curweg + abs(ma[col][p]-cur);
                        if (newdis < dist[ma[col][p]]) {
                            dist[ma[col][p]] = newdis;
                            pq.push({newdis, ma[col][p]});
                        }
                    }
                }
                continue;
            }
            auto it = lower_bound(ma[col].begin(), ma[col].end(), cur);
            if (ma[col].empty()) {
                continue;
            }
            if (it == ma[col].end())    {
                it--;
            }
            p = it-ma[col].begin();
            if (p >= 0) {
                int newdis = curweg + abs(ma[col][p]-cur);
                if (newdis < dist[ma[col][p]]) {
                    dist[ma[col][p]] = newdis;
                    pq.push({newdis, ma[col][p]});
                }
            }
            if (p != 0) {
                p--;
                int newdis = curweg + abs(ma[col][p]-cur);
                if (newdis < dist[ma[col][p]]) {
                    dist[ma[col][p]] = newdis;
                    pq.push({newdis, ma[col][p]});
                }
            }
        }
    }
    cout << ((dist[n-1] == LLONG_MAX) ? -1 : dist[n-1]) << endl;
}