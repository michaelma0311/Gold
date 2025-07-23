#include <bits/stdc++.h>
using namespace std;
int n, m;
vector<int> par;
vector<int> rnk;
vector<vector<int>> adj;
vector<pair<int, int>> edgs;
vector<int> par2;
vector<int> rnk2;
vector<int> degs;
vector<int> sz;
int curnum = 0;
map<int, vector<int>> nums;
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
        if (rnk[curx] > rnk[cury]) {
            par[cury] = curx;
        } else if (rnk[curx] < rnk[cury]) {
            par[curx] = cury;
        } else {
            par[cury] = curx;
            rnk[curx]++;
        }
    }
}

int find2(int x) {
    if (par2[x] != x) {
        par2[x] = find2(par2[x]);  
    }
    return par2[x];
}

void unite2(int x, int y) {
    int curx = find2(x);
    int cury = find2(y);
    if (curx != cury) {
        if (rnk2[curx] > rnk2[cury]) {
            par2[cury] = curx;
            sz[curx] += sz[cury];
        } else if (rnk2[curx] < rnk2[cury]) {
            par2[curx] = cury;
            sz[cury] += sz[curx];
        } else {
            par2[cury] = curx;
            rnk2[curx]++;
            sz[curx] += sz[cury];
        }
    }
}

int solve(int rank)    {
    vector<int> curnums = nums[rank];
    /*for (int i : curnums)   {
        //cout << "AD " << i+1 << endl;
    }*/
        
    set<pair<int, int>> pq;
    int curn = curnums.size();
    for (int i = 0; i < curn; i++) {
        pq.insert({degs[curnums[i]], curnums[i]});
        //cout << degs[curnums[i]] << ' ' << curnums[i] << endl;
    }
    int siz = curn;
    int tot = 0;
    vector<int> ord;
    vector<pair<int, int>> ordedgs;
    while (!pq.empty()) {
        int curdeg = (*pq.begin()).first;
        int cur = (*pq.begin()).second;
        ord.push_back(cur);
        pq.erase({curdeg, cur});
        //cout << "DAD " << curdeg << ' ' << cur+1 << endl;
        for (int i : adj[cur])  {
            if (pq.find({degs[i], i}) == pq.end())    {
                continue;
            }
            //cout << "DAFA " << cur+1 << ' ' << i+1 << endl;
            ordedgs.push_back({cur, i});
            pq.erase({degs[i], i});
            degs[i] -= 1;
            pq.insert({degs[i], i});
        }
    }
    map<int, int> deggs;
    for (int i = 0; i < curn; i++)  {
        deggs[curnums[i]] = 0;
    }
    par2.clear();
    rnk2.clear();
    pq.clear();
    fill(sz.begin(), sz.end(), 1);
    int ind = 0;
    reverse(ord.begin(), ord.end());
    reverse(ordedgs.begin(), ordedgs.end());
    for (int i = 0; i < curn; i++)  {
        par2[curnums[i]] = curnums[i];
        rnk2[curnums[i]] = 0;
    }
    set<int> alrin;
    for (int i = 0; i < ordedgs.size(); i++)  {
        int x, y;
        x = ordedgs[i].first;
        y = ordedgs[i].second;
        unite2(x, y);
        //cout << "INHERE " << x+1 << ' ' << y+1 << endl;
        if (alrin.find(x) == alrin.end())   {
            alrin.insert(x);
        } else  {
            pq.erase({deggs[x], x});
        }
        if (alrin.find(y) == alrin.end())   {
            alrin.insert(y);
        } else  {
            pq.erase({deggs[y], y});
        }
        deggs[x] += 1;
        deggs[y] += 1;
        pq.insert({deggs[x], x});
        pq.insert({deggs[y], y});
        
        int a = sz[find2((*pq.begin()).second)];
        //cout << "INHEegewgeRE " << (*pq.begin()).first << ' ' << a << endl;
        tot = max(tot, ((*pq.begin()).first * a));
    }
    return tot;
}

int main()  {
    //freopen("a.in", "r", stdin);
    cin >> n >> m;
    par.resize(n);
    rnk.resize(n);
    adj.resize(n);
    degs.resize(n);
    edgs.resize(m);
    par2.resize(n);
    rnk2.resize(n);
    sz.resize(n);
    for (int i = 0; i < n; i++) {
        par[i] = i;
        rnk[i] = 0;
    }
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        //cout << "FIRST " << x << ' ' << y << endl;
        x -= 1;
        y -= 1;
        adj[x].push_back(y);
        adj[y].push_back(x);
        degs[x] += 1;
        degs[y] += 1;
        edgs[i] = {x, y};
        if (find(x) != find(y)) {
            unite(x, y);
        }
        //unite(x, y);
    }
    
    vector<int> blank;
    for (int i = 0; i < n; i++) {
        if (nums.find(find(par[i])) == nums.end())    {
            nums[find(par[i])] = blank;
        }
        nums[find(par[i])].push_back(i);
    }
    vector<int> visited(n+1);
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (!visited[find(par[i])])   {
            visited[find(par[i])] = true;
            ans = max(ans, solve(find(par[i])));
        }
    }
    cout << ans << endl;
    

}