#include <bits/stdc++.h>

using namespace std;
#define int long long

int n, m;
vector<vector<int>> adj;
vector<int> lis;
vector<int> can;
vector<vector<int>> quers;
map<int, array<int,3>> inds;
map<int,vector<pair<int,int>>> inds2; ///inds[i] = {a,b,c}; inds2[a].push_back({b,i}); inds2[b].push_back({a,i});
map<int,set<int>> active;
vector<bool> curactive;
pair<map<int,set<int>>, set<int>> dfs(int cur, int prev)  {
    map<int,set<int>> active; //current things that are using the key
    set<int> curactive;
    //cout << "HI  " << cur << endl;
    for (int i : adj[cur])  {
        if (i == prev)  {
            continue;
        }
        auto [newactive, newcuractive] = dfs(i, cur);
        for (auto& j : newactive)  {
            if (active.find(j.first) == active.end())  {
                active[j.first] = set<int>();
            }
            if (active[j.first].size() < j.second.size())  {
                swap(active[j.first], j.second);
            }
            active[j.first].insert(j.second.begin(), j.second.end());
        }
        //cout << "HI " << cur << endl;
        if (newcuractive.size() > curactive.size())  {
            swap(newcuractive, curactive);
        }
        for (const auto& j : newcuractive)  {
            if (curactive.find(j) != curactive.end())  {
                //cout << "WEUBGEW " << j << endl;
                if (active[inds[j][2]].find(j) != active[inds[j][2]].end())  {
                    active[inds[j][2]].erase(j);
                    if (lis[cur] == inds[j][2])  {
                        can[j] = 1;
                    }
                }
            } else  {
                curactive.insert(j);
            }
        }
    }
    //cout << "WGBOWEG " << cur << endl;
    for (auto i : inds2[cur])  { //activate or deactivate the current thing
        int other = i.first;
        int ind = i.second;
        //cout << "WEGWE " << other << ' ' << ind << endl;
        if (curactive.find(ind) != curactive.end())  { //before active, now turning it false
            if (lis[cur] == inds[ind][2])  {
                can[ind] = 1;
            }
            if (active[inds[ind][2]].find(ind) != active[inds[ind][2]].end())  {
                active[inds[ind][2]].erase(ind);
            }
            curactive.erase(ind);
        } else  {
            if (lis[cur] == inds[ind][2])  {
                can[ind] = 1;
            } else  {
                //cout << "ALAST " << endl;
                if (active.find(inds[ind][2]) == active.end())  {
                    active[inds[ind][2]] = set<int>();
                }
                active[inds[ind][2]].insert(ind);
                //cout << "WEG " << endl;
            }
            curactive.insert(ind);
        }
    }
    for (auto i : active[lis[cur]])  {
        //cout << i << endl;
        can[i] = 1;
    }
    active[lis[cur]].clear();
    return {active, curactive};
}

signed main()  {
    freopen("milkvisits.in", "r", stdin);
    freopen("milkvisits.out", "w", stdout);
    cin >> n >> m;
    adj.resize(n);
    lis.resize(n);
    can.resize(m);
    quers.resize(n);
    curactive.resize(m,false);
    for (int i =0 ; i < n; i++)  {
        cin >> lis[i];
        lis[i] -= 1;
    }
    for (int i = 0; i < n-1; i++)  {
        int x, y;
        cin >> x >> y;
        x -= 1;
        y -= 1;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    for (int i =0 ; i < m; i++)  {
        int a, b, c;
        cin >> a >> b >> c;
        a -= 1;
        b -= 1;
        c -= 1;
        if (a == b)  {
            if (lis[a] != c)  {
                can[i] = 0;
            } else  {
                can[i] = 1;
            }
            continue;
        }
        inds[i] = {a,b,c};
        inds2[a].push_back({b,i});
        inds2[b].push_back({a,i});
    }
    dfs(0, -1);
    for (int i = 0; i < m-1; i++)  {
        cout << can[i];
    }
    cout << can[m-1] <<endl;

}