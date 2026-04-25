
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n;
vector<int> lis;
vector<int> cost;
vector<int> comp;
vector<bool> visited;
map<int, pair<int,int>> endpoints;
map<int,vector<vector<int>>> adj;
set<int> curvis;
vector<vector<int>> par;
vector<int> child;
vector<bool> visited2;
int tot;
int typ;
int endvis;
map<int,int> siz;
vector<pair<int,int>> dp;
void dfs(int cur) {
    curvis.insert(cur);
    if (lis[cur] == cur)    {
        typ = -1;
        endvis = cur;
        return;
    } 
    if (curvis.find(lis[cur]) != curvis.end())  {
        typ = 1;
        endvis = cur;
        return;
    }
    if (visited[lis[cur]] == true)  {
        typ = 2;
        endvis = lis[cur];
        return;
    }
    dfs(lis[cur]);
}

void dfs1(int cur, int prev, int start)  {
    //cout << "ADAD " << cur << ' ' << prev << endl;
    if (cur == start && prev != -1) {
        return;
    }
    if (par[cur].size() == 0)   {
        
        dp[cur].first = cost[cur];
        dp[cur].second = 0;
        //cout << "HI " << dp[cur].first << ' ' << dp[cur].second << ' ' << cost[cur] << endl;
        return;
    }
    int cursu = 0;
    int su1 = 0;
    for (int i : par[cur])  {
        dfs1(i, cur, start);
        if (i == start) {
            continue;
        }
        //cout << "ADADFGWGWG " << i << ' ' << cur << ' ' <<start << ' ' << dp[i].first << ' ' << dp[i].second << endl;
        cursu += min(dp[i].first, dp[i].second);
        su1 += dp[i].first;
    }
    if (lis[cur] == cur)    {
        dp[cur].first = cursu;
    } else  {
        dp[cur].first = cursu + cost[cur];
    }
    dp[cur].second = su1;
}

signed main()  {
    cin >> n;
    lis.clear();
    cost.clear();
    comp.clear();
    comp.resize(n);
    lis.resize(n);
    cost.resize(n);
    endpoints.clear();
    visited.clear();
    par.clear();
    par.resize(n);
    child.clear();
    child.resize(n);
    visited.resize(n);
    visited2.clear();
    visited2.resize(n);
    adj.clear();
    for (int i = 0; i < n; i++) {
        cin >> lis[i];
        lis[i] -= 1;
        par[lis[i]].push_back(i);
    }
    for (int i = 0; i < n; i++) {
        cin >> cost[i];
    }
    //cout << "ADAD " << endl;
    int num = 0;
    siz[0] = 0;
    for (int i = 0; i < n; i++) {
        //cout << i << endl;
        if (!visited[i])    {
            typ = 0;
            endvis = -1;
            curvis.clear();
            dfs(i);
            //cout << endvis << ' ' << typ << endl;
            if (typ == -1)  {
                for (const auto& i : curvis)    {
                    comp[i] = num;
                    siz[num] += 1;
                    visited[i] = true;
                }
                endpoints[num] = {endvis, -1};
                num += 1;
                siz[num] = 0;
            } else if (typ == 1)    {
                for (const auto& i : curvis)    {
                    comp[i] = num;
                    siz[num] += 1;
                    visited[i] = true;
                }
                endpoints[num] = {endvis, lis[endvis]};
                num += 1;
                siz[num] = 0;
            } else  {
                for (const auto& i : curvis)    {
                    comp[i] = comp[endvis];
                    visited[i] = true;
                    siz[comp[endvis]] += 1;
                }
            }

        }
    }
    int totsum = 0;
    dp.clear();
    pair<int,int> blank = {LLONG_MAX, LLONG_MAX};
    dp.resize(n);
    fill(dp.begin(), dp.end(), blank);
    for (int i = 0; i < num; i++)   {
        //cout << "HI " << i << endl;
        tot =0;
        
       // cout << endpoints[i].first << endl;
        dfs1(endpoints[i].first, -1, endpoints[i].first);
        /*for (int j = 0; j < n; j++) {
            cout << dp[j].first << ' ' << dp[j].second << endl;
        }*/
        int curmi = dp[endpoints[i].first].first;
        if (endpoints[i].second != -1)  {
            fill(dp.begin(), dp.end(), blank);
            dfs1(endpoints[i].second, -1, endpoints[i].second);
            curmi = min(curmi, dp[endpoints[i].second].first);
        }
        totsum += curmi;
    }
    cout << totsum << endl;
    
}