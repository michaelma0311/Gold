#include <bits/stdc++.h>
using namespace std;
#define int long long
vector<int> par;
vector<int> rnk;
map<int,set<int>> curnums;
int find(int x) {
    if (par[x] != x) {
        par[x] = find(par[x]);  
    }
    return par[x];
}

void unite(int x, int y) {
    int curx = find(x);
    int cury = find(y);
    if (curx != cury) {
        if (curnums[curx].size() >= curnums[cury].size()) {
            par[cury] = curx;
            for (auto i : curnums[cury])    {
                curnums[curx].insert(i);
            }
            curnums.erase(cury);
        } else {
            par[curx] = cury;
            for (auto i : curnums[curx])    {
                curnums[cury].insert(i);
            }
            curnums.erase(curx);
        } 
    }
}

signed main()   {
    freopen("fcolor.in", "r", stdin);
    freopen("fcolor.out", "w", stdout);
    int n, m;
    cin >> n >> m;
    par.resize(n);
    rnk.resize(n);

    set<int> bnk;
    for (int i =0 ; i < n; i++) {
        par[i] = i;
        curnums[par[i]] = bnk;
        curnums[par[i]].insert(i);
        rnk[i] = 0;
    }
    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a -= 1;
        b -= 1;
        adj[a].push_back(b);
    }
    
    for (int i =0 ; i < n; i++) {
        bool tof = true;
        set<int> curlis;
        for (int j = 0; j < adj[i].size(); j++)   {
            int a = find(adj[i][j]);
            curlis.insert(a);
        }
        while (curlis.size() > 1)   {
            set<int> temp;
            vector<int> curt;
            int num = 0;
            for (auto& j : curlis)  {
                for (auto k : curnums[j])  {
                    num += 1;
                    curt.push_back(k);
                }
                //curt.push_back(j.second);
            }
            for (int j = 0; j < num; j++)   {
                if (j != num-1)   {
                    unite(curt[j], curt[j+1]);

                }               
                
                for (int k : adj[curt[j]])  {
                    int a = find(k); 
                    temp.insert(a);
                }
            }
            curlis = temp;
        }
        
    }
    int curcol = 1;
    vector<int> ans(n);
    map<int,int> ma;
    for (int i = 0; i < n; i++) {
        if (ma.find(find(i)) == ma.end())   {
            ma[find(i)] = curcol;
            curcol += 1;
        }
        ans[i] = ma[find(i)];
    }
    for (int i : ans)   {
        cout << i << endl;
    }
}