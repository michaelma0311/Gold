#include <bits/stdc++.h>
using namespace std;

signed main()  {
    long long n, m, c, r, k;
    cin >> n >> m >> c >> r >> k;
    vector<pair<pair<long long, long long>, long long>> lis(m);
    vector<vector<pair<long long, long long>>> adj(n);
    unordered_map<long long, set<long long>> ma;
    for (long long i = 0; i < m; i++) {
        long long a, b, c;
        cin >> a >> b >> c;
        a -= 1;
        b -= 1;
        lis[i] = make_pair(make_pair(a, b), c);
        adj[a].push_back(make_pair(b, c));
        adj[b].push_back(make_pair(a, c));
    }
    priority_queue<pair<long long, pair<long long, long long>>> q;
    vector<long long> times(n);
    for (long long i = 0; i < n; i++) {
        set<long long> g;
        ma[i] = g;
    }
    for (long long i = 0; i < c; i++) {
        q.push(make_pair(0, make_pair(i, i)));
    }
    while (!q.empty())  {
        pair<long long, pair<long long, long long>> cu = q.top();
        long long dis = -cu.first;
        long long ver = cu.second.first;
        long long rt = cu.second.second;
        // /cout << "start " << dis << ' ' << ver << ' ' << rt << endl;
        q.pop();
        if (dis > r || ma[ver].find(rt) != ma[ver].end() || times[ver] >= k)    {
            continue;
        }
        //cout << "second " << ver << ' ' << rt << ' ' << dis << endl;
        ma[ver].insert(rt);
        times[ver] += 1;
        for (auto i : adj[ver]) {
            // /cout << "LOOP " << i.first << ' ' << i.second << ' ' << times[i.first] << ' ' << dis << endl;
            if (dis+i.second <= r && times[i.first] < k)  {
                q.push(make_pair(-(dis+i.second), make_pair(i.first, rt)));
            }
        }
    }
    long long ans = 0;
    vector<long long> sol;
    for (long long i = c; i < n; i++) {
        if (times[i] >= k)  {
            ans += 1;
            sol.push_back(i+1);
        }
    }
    //cout << "ADAD" << endl;
    cout << ans << endl;
    for (long long i : sol)   {
        cout << i << endl;
    }

}