#include <bits/stdc++.h>

using namespace std;
int n, m;
vector<int> par;
vector<int> rnk;
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
vector<pair<int,int>> ans;
vector<vector<int>> adj;
vector<vector<int>> adj2;
vector<int> depths;
vector<bool> alive;
vector<int> depths1;
int mxcnt;
vector<bool> del;
vector<vector<bool>> dp;
void calcans(int cur, int par2)   {
    //cout << "INHERE " << cur << ' ' << par2 << endl;
    for (int i : adj[par2])    {
        if (dp[cur][i] == true) {
            ans.push_back({cur, i});
            del[cur] = true;
            for (int j : adj[cur])  {
                if (alive[j] == false)  {
                    calcans(j, i);
                }
            }
            break;
        }
    }
}
void dfs(int cur, int prev,int cnt) {
    depths[cur] = cnt;
    mxcnt = max(mxcnt, cnt);
    for (int i : adj[cur])  {
        if (i != prev)  {
            dfs(i, cur, cnt+1);
        }
    }
}
void dfs1(int cur, int prev,int cnt) {
    depths1[cur] = cnt;

    mxcnt = max(mxcnt, cnt);
    for (int i : adj2[cur])  {
        if (i != prev)  {
            dfs1(i, cur, cnt+1);
        }
    }
}


void solve()    {
    
    cin >> n;
    adj.clear();
    adj2.clear();
    adj.resize(n);
    adj2.resize(n);
    alive.clear();
    alive.resize(n);
    depths.clear();
    depths.resize(n);
    depths1.clear();
    depths1.resize(n);
    par.clear();
    rnk.clear();
    dp.clear();
    par.resize(n);
    rnk.resize(n);
    del.clear();
    del.resize(n);
    ans.clear();
    mxcnt = 0;
    vector<int> parent(n);
    vector<int> parent2(n);
    vector<bool> tof(n, false);
    for (int i =0 ; i < n-1; i++)   {
        int x, y;
        cin >> x >> y;
        x -= 1;
        y -= 1;
        adj[y].push_back(x);
        parent[x] = y;
        tof[x] = true;
    }
    cin >> m;
    for (int i =0 ; i < m-1; i++)   {
        int x, y;
        cin >> x >> y;
        x -= 1;
        y -= 1;
        parent2[x] = y;
        adj2[y].push_back(x);
        alive[x] = true;
        alive[y] = true;
    }
    int root = 0;
    for (int i = 0; i < n; i++) {
        if (tof[i] == false)   {
            root = i;
            break;
        }
    }
    vector<int> siz(n);
    for (int i = 0; i < n; i++) {
        siz[i] = adj[i].size();
        /*for (int j : adj[i])    {
            if (alive[j] == false)  {
                siz[i] += 1;
            }
        }*/
    }
    //cout << "root " <<  root << endl;
    
    dfs(root, -1, 0);
    dfs1(root, -1, 0);
    //cout << "GWEGWE " << mxcnt << endl;
    vector<vector<int>> nums(mxcnt+1);
    for (int i = 0; i < n; i++) {
        //cout << "A " << i << endl;
        //cout << "EWGE " << depths[i] << ' ' << nums.size()<< endl;
        nums[depths[i]].push_back(i);
        //cout << "A " << endl;
    }
    vector<vector<int>> nums1(mxcnt+1);
    dp.resize(n);
    vector<vector<set<int>>> can(n);
    for (int i = 0; i < n; i++) {
        dp[i].resize(n);
        can[i].resize(n);
        if (alive[i])   {
            nums1[depths1[i]].push_back(i);
        }
    }
    
    for (int i = mxcnt; i >= 0; i--)  {
        for (int j = 0; j < nums[i].size(); j++)    {
            //cout << "WEGEWG " << ' '  << nums[i].size()  << endl;
            int cur = nums[i][j];
            //cout << "WEGWEGA " << endl;
            for (int k = 0; k < nums1[i].size(); k++)    {
                int comp = nums1[i][k];
                if (i == mxcnt)   {
                    //cout << "INSIDE " << cur << ' ' << comp << endl;

                    if (cur == comp)    {
                        //cout << cur << ' ' << comp << endl;
                        dp[cur][comp] = true;
                    } else  {
                        if (!alive[cur])    {
                            if (cur < comp) {
                                //cout << cur << ' ' << comp << endl;
                                dp[cur][comp] = true;
                            }
                        }
                    }
                } else  {
                    //cout << "HIbuwbugo " << cur << ' ' << comp << ' ' <<can[cur][comp].size() << ' ' << siz[cur] << endl;
                    if (cur <= comp && can[cur][comp].size() == siz[cur])    {
                        dp[cur][comp] = true;
                    }
                }
            }
            for (int k = 0; k < n; k++) {
                if (dp[cur][k] == true) {
                    //cout << "DP " << cur+1 << ' ' << k+1 << ' ' <<parent[cur]+1 << ' ' << parent2[k]+1<< endl;
                    can[parent[cur]][parent2[k]].insert(cur);
                }
            }

        }
    }
    /*for (int i = 0; i < n; i++) {
        cout << "INSIDE " << i << endl;
        for (int j = 0; j < n; j++) {
            if (dp[i][j] == true)   {
                cout << "j " << j << endl;
            }
        }
    }*/
    for (int i = 0; i <= mxcnt; i++)    {
        for (int j : nums[i])  {
            if (!alive[j] && !del[j])  {
                for (int k : nums1[i]) {
                    if (dp[j][k] == true)   {
                        del[j] = true;
                        //cout << "ADA " <<i << ' ' << j << ' ' << k << endl;
                        ans.push_back({j, k});
                        for (int p : adj[j])    {
                            if (!alive[p] && !del[p])   {
                                calcans(p, k);
                            }
                        }
                        break;
                    }
                }
            }
        }
    }
    //cout << "AAD" << endl;
    cout << ans.size() << endl;
    for (auto i : ans)  {
        cout << i.first+1 << ' ' << i.second+1 << endl;
    }
}

int main()  {
    //freopen("test.in", "r", stdin);
    //freopen("test.out", "w", stdout);
    int t;
    cin >> t;
    for (int i =0 ; i < t; i++) {
        solve();
    }
}
