#include <bits/stdc++.h>

using namespace std;
#define int long long
vector<int> parent;
vector<int> rnk;
int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);  
    }
    return parent[x];
}

void unite(int x, int y) {
    int curx = find(x);
    int cury = find(y);
    if (curx != cury) {
        if (rnk[curx] > rnk[cury]) {
            parent[cury] = curx;
        } else if (rnk[curx] < rnk[cury]) {
            parent[curx] = cury;
        } else {
            parent[cury] = curx;
            rnk[curx]++;
        }
    }
}
int sq(int cur) {
    return cur*cur;
}
signed main()   {
    int n;
    cin >> n;
    parent.resize(n);
    rnk.resize(n);
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rnk[i] = 0;
    }
    vector<vector<pair<int,int>>> lis(11);
    vector<pair<int,int>> cur;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        cur.push_back({x, y});
        lis[y].push_back({x, i});
    }
    vector<int> siz;
    for (int i = 0; i < 11; i++)    {
        sort(lis[i].begin(), lis[i].end());
        siz.push_back(lis[i].size());
    }
    vector<pair<int,pair<int,int>>> edges;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= 10; j++)   {
            if (cur[i].second == j) {
                int p = lower_bound(lis[j].begin(), lis[j].end(), make_pair(cur[i].first, (int)-INT_MAX)) - lis[j].begin();
                if (p != 0) {
                    edges.push_back({sq(lis[j][p-1].first - cur[i].first), {lis[j][p-1].second, i}});
                }
                if (p < siz[j]-1)   {
                    edges.push_back({sq(lis[j][p+1].first - cur[i].first), {lis[j][p+1].second, i}});
                }
            } else  {
                int p = lower_bound(lis[j].begin(), lis[j].end(), make_pair(cur[i].first, (int)-INT_MAX)) - lis[j].begin();
                if (p != siz[j])    {
                    edges.push_back({sq(lis[j][p].first - cur[i].first) + sq(cur[i].second-j), {lis[j][p].second, i}});
                }
                if (p != 0)   {
                    edges.push_back({sq(lis[j][p-1].first - cur[i].first) + sq(cur[i].second-j), {lis[j][p-1].second, i}});
                }
            }
        }
    }
    sort(edges.begin(), edges.end());
    int ans = 0;
    for (int i = 0; i < edges.size(); i++)  {
        if (find(edges[i].second.first) != find(edges[i].second.second))    {
            unite(edges[i].second.first, edges[i].second.second);
            ans += edges[i].first;
        }
    }
    cout << ans << endl;
}