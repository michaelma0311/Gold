#include <bits/stdc++.h>

using namespace std;
#define int long long
signed main()  {
    freopen("a.in", "r", stdin);
    //freopen("a.out", "w", stdout);
    int n, m;
    cin >> n >> m;
    vector<int> lis(n);
    vector<vector<pair<int, int>>> radj(n);
    vector<vector<pair<int, int>>> adj(n);
    vector<int> degs(n);
    vector<vector<int>> nodes(n);
    for (int i =0 ; i < m; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        x -= 1;
        y -= 1;
        radj[y].push_back({x, z});
        adj[x].push_back({y, z});
    }
    queue<pair<pair<int, int>, pair<pair<int, int>, int>>> q; //  length, sumlabel, curlabel, rank, curind
    vector<vector<pair<pair<int, int>, pair<int, int>>>> ans(n);
    for (int i = 0; i < n; i++) {
        degs[i] = adj[i].size();
        if (adj[i].size() == 0) {
            q.push({{0, 0}, {{0,0}, i}});
            ans[i].push_back( {{0, 0}, {0, 0}});
        }
    }
    //cout << "AAD " << endl;
    while (!q.empty())  {
        vector<pair<pair<int, int>, pair<pair<int, int>, int>>> cur; //length label rank sumlabel curind
        while (!q.empty())  {
            int length = q.front().first.first;
            int sumlabel = q.front().first.second;
            int curlabel = q.front().second.first.first;
            int curnk = q.front().second.first.second;
            int curind = q.front().second.second;
            q.pop();
            for (auto i : radj[curind])   {
                cur.push_back({{(length-1), i.second}, {{curnk, i.second + sumlabel}, i.first}});
            }
        }
        sort(cur.begin(), cur.end());
        int intrnk = 0;
        for (auto i : cur)  {
            int curlen = i.first.first;
            int curlab = i.first.second;
            int cursumlab = i.second.first.second;
            int curind = i.second.second;
            degs[curind] -= 1;
            if (degs[curind] == 0) {
                q.push({{curlen, cursumlab}, {{curlab, intrnk},curind}});
            }
            ans[i.second.second].push_back( {{curlen, curlab}, {intrnk++, cursumlab}});
        }
    }
    //scout << "ADD " << endl;
    vector<pair<int, int>> tot(n);
    for (int i = 0; i < n; i++) {
        sort(ans[i].begin(), ans[i].end());
        tot[i] = {-ans[i][0].first.first, ans[i][0].second.second};
    }
    for (auto i : tot)  {
        cout << i.first << ' ' << i.second << endl;
    }
    


}