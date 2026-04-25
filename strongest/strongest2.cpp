#include <bits/stdc++.h>
using namespace std;
#define int long long
vector<int> par;
vector<int> rnk;
vector<map<int,int>> mp1;
vector<map<int,int>> mp2;
int find(int x) {
    if (par[x] != x) {
        par[x] = find(par[x]);  
    }
    return par[x];
}

void unite(int x, int y) {
    int curx = find(x);
    int cury = find(y);
    int ox = mp1[curx][x];
    int oy = mp1[cury][y];
    mp2[curx][ox] -= 1;
    mp1[curx][x] += 1;
    mp2[curx][mp1[curx][x]] += 1;
    mp2[cury][oy] -= 1;
    mp1[cury][y] += 1;
    mp2[cury][mp1[cury][y]] += 1;
    if (mp2[curx][ox] == 0) {
        mp2[curx].erase(ox);
    }
    if (mp2[cury][oy] == 0) {
        mp2[cury].erase(oy);
    }
    if (curx != cury) {
        if (mp1[curx].size() > mp1[cury].size()) {
            par[cury] = curx;
            for (auto &p : mp1[cury]) {
                int node = p.first;
                int deg = p.second;
                mp2[curx][deg] += 1;
                mp1[curx][node] = deg;
            }
        } else if (mp1[curx].size() < mp1[cury].size()) {
            par[curx] = cury;
            for (auto &p : mp1[curx]) {
                int node = p.first;
                int deg = p.second;
                mp2[cury][deg] += 1;
                mp1[cury][node] = deg;
            }
        } else {
            par[cury] = curx;
            for (auto &p : mp1[cury]) {
                int node = p.first;
                int deg = p.second;
                mp2[curx][deg] += 1;
                mp1[curx][node] = deg;
            }
        }
    } 
}
int n, m;
vector<vector<int>> adj;
vector<int> col;

void dfs(int cur, int prev, int colr) {
    if (col[cur] == -1) {
        col[cur] = colr;
    } else {
        return;
    }
    for (int i : adj[cur]) {
        if (i != prev) {
            dfs(i, cur, colr);
        }
    }
}

int check(vector<int> lis)  {
    map<int,int> cnts;
    for (int i : lis)   {
        cnts[i] = adj[i].size();
    }
    sort(lis.begin(), lis.end(), [&cnts](const int& x, const int& y) {
        return cnts[x] > cnts[y];
    });
    int siz = lis.size();
    int ans = 0;
    vector<int> ord;
    map<int,int> a1;
    map<int,set<int>> a2;
    set<int> used;
    for (int i = 0; i < siz; i++)   {
        a1[lis[i]] = adj[lis[i]].size();
        a2[a1[lis[i]]].insert(lis[i]);

    }
    for (int i = 0; i < siz; i++) {
        while (a2.begin()->second.empty()) {
            a2.erase(a2.begin()->first);
        }
        int cur = *a2.begin()->second.begin();
        a2.begin()->second.erase(cur);
        ord.push_back(cur);
        used.insert(cur);
        for (int j : adj[cur])   {
            if (used.find(j) != used.end()) {
                continue;
            }
            int olddeg = a1[j];
            a2[olddeg].erase(j);
            a1[j] -= 1;
            a2[a1[j]].insert(j);
        }
    }
    reverse(ord.begin(), ord.end());
    set<int> active;
    for (int i = 0; i < siz; i++)   {
        //cout << "INSIDE " << ord[i] << endl;
        active.insert(ord[i]);
        for (int j : adj[ord[i]])   {
            
            if (active.find(j) != active.end())    {
                //cout << "ADD " << j << endl;
                unite(ord[i], j);
            }
        }
        for (auto& p : mp1[find(ord[i])]) {
            //cout << "NODE " << p.first << ' ' << p.second << endl;
        }
        for (auto& p : mp2[find(ord[i])]) {
            //cout << "DEG " << p.first << ' ' << p.second << endl;
        }
        ans = max(ans, (int)mp1[find(ord[i])].size() * mp2[find(ord[i])].begin()->first);
    }
    return ans;
}

signed main()   {
    cin >> n >> m;
    //cout << n << ' ' << m << endl;
    adj.resize(n);
    col.resize(n, -1);
    par.resize(n);
    rnk.resize(n);
    mp1.resize(n);
    mp2.resize(n);
    for (int i = 0; i < n; i++) {
        par[i] = i;
        mp1[i][i] = 0;
        mp2[i][0] = 1;
        rnk[i] = 1;
    }
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a -= 1;
        b -= 1;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (col[i] != -1) {
            continue;
        }
        dfs(i, -1, cnt);
        cnt += 1;
    }
    vector<vector<int>> subs(cnt);
    for (int i = 0; i < n; i++) {
        //cout << "ADDA " <<i << ' ' << col[i] << endl;
        subs[col[i]].push_back(i);
    }
    int ans = 0;
    for (auto i : subs) {
        if (i.size() == 0) {
            continue;
        }
        ans = max(ans, check(i));
    }
    cout << ans << endl;
}