#include <bits/stdc++.h>

using namespace std;
#define int long long
vector<int> parent;
vector<int> rk;
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
        if (rk[curx] > rk[cury]) {
            parent[cury] = curx;
        } else if (rk[curx] < rk[cury]) {
            parent[curx] = cury;
        } else {
            parent[cury] = curx;
            rk[curx]++;
        }
    }
}
int square(int x)   {
    return x*x;
}
signed main()  {
    //freopen("a.in", "r", stdin);
    int n;
    cin >> n;
    parent.resize(n);
    rk.resize(n);
    vector<set<int>> maps(11);
    vector<set<int>> tempmaps(11);
    vector<vector<int>> adj(n);
    vector<pair<int, int>> lis(n);
    map<pair<int, int>, int> remap;
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        lis[i] = {a, b};
        maps[b].insert(a);
        remap[{a, b}] = i;
        tempmaps[b].insert(a);
    }
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rk[i] = 0;
    }
    long long ans=  0;
    
    priority_queue<
    pair<int, pair<int,int>>,
    vector<pair<int, pair<int,int>>>,
    greater<pair<int, pair<int,int>>>> pq;
    for (int i = 0; i < 11; i++)    {
        int x = lis[0].first;
        int y = lis[0].second;
        if (maps[i].empty())    {
            continue;
        }
        if (i == y) {
            auto it = maps[y].find(x);
            if (it != maps[y].begin())  {
                pq.push({square(x-(*prev(it))), {remap[{*prev(it), y}], 0}});
            }
            if (it != maps[i].end() && next(it) != maps[y].end())  {
                pq.push({square((*next(it))-x), {remap[{*next(it), y}], 0}});
            }
        } else  {
            //cout << i << endl;
            auto it = maps[i].lower_bound(x);
            if (it != maps[i].begin())  {
                pq.push({square(x-(*prev(it))) + square(i-y), {remap[{*prev(it), i}], 0}});
            }
            if (it != maps[i].end())    {
                pq.push({square((*(it))-x) + square(i-y), {remap[{*(it), i}], 0}});
            }
            
        }
    }
    tempmaps[lis[0].second].erase(lis[0].first);
    //cout << "HI " << endl;
    while (!pq.empty()) {
        int curcost = pq.top().first;
        int to = pq.top().second.first;
        int from = pq.top().second.second;
        //cout << to << ' ' << from << endl;
        pq.pop();
        if (find(to) == find(from) || tempmaps[lis[to].second].find(lis[to].first) == tempmaps[lis[to].second].end()) {
            continue;
        }
        //cout << "HI" << endl;
        ans += curcost;
        unite(to, from);
        //cout << "ADD " << curcost << ' ' << to << ' ' << from<< endl;
        
        //cout << "ADa d" << endl;
        for (int i = 0; i < 11; i++)    {
            int x = lis[to].first;
            int y = lis[to].second;
            //scout << x << ' ' << y << ' ' << i << endl;
            if (tempmaps[i].empty())    {
                continue;
            }    
            if (i == y) {
                auto it = tempmaps[y].find(x);
                //cout << "HI "  << *it << ' ' << ' ' << y << ' ' << tempmaps.size() << ' ' << tempmaps[y].size() << ' ' << (next(it) == tempmaps[y].end())<< endl;
                if (it != tempmaps[y].begin())  {
                    //cout << "TIA a" << *prev(it) << endl;
                    pq.push({square(x-(*prev(it))), {remap[{*prev(it), y}], to}});
                }
                if (it != tempmaps[i].end() && next(it) != tempmaps[y].end())  {
                    pq.push({square((*next(it))-x), {remap[{*next(it), y}], to}});
                }
            } else  {
                //cout << i << endl;
                auto it = tempmaps[i].lower_bound(x);
                if (it != tempmaps[i].begin())  {
                    pq.push({square(x-(*prev(it))) + square(i-y), {remap[{*prev(it), i}], to}});
                }
                if (it != tempmaps[i].end())    {
                    pq.push({square((*(it))-x) + square(i-y), {remap[{*(it), i}], to}});
                }
            }
            //cout << "END " << endl;
        }
        tempmaps[lis[to].second].erase(lis[to].first);    
    }
    cout << ans << endl;
}