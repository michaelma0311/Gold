#include <bits/stdc++.h>

using namespace std;
#define int long long
int n, m;
vector<int> lis;
vector<vector<int>> adj;
map<int, vector<pair<pair<int, int>, int>>> queries;
vector<vector<int>> up;
vector<int> depth;
vector<stack<int>> temp;
vector<int> ans;
const int LOG = 17;

void dfs(int node, int par, int dep) {
    cout << "HI " << node << endl;
    cout << up[node][0] << endl;
    up[node][0] = par;
    depth[node] = dep;

    for (int i = 1; i < LOG; ++i) {
        if (up[node][i - 1] != -1) {
            up[node][i] = up[up[node][i - 1]][i - 1];
        }
    }
    cout << "end" << endl;
    //cout << adj[node].size() << endl;
    for (int child : adj[node]) {
        if (child != par) {
            dfs(child, node, dep + 1);
        }
    }
}


int getLCA(int u, int v) {
    //cout << "HI " << endl;
    if (depth[u] < depth[v]) {
        swap(u, v);
    }

    for (int i = LOG - 1; i >= 0; --i) {
        if (depth[u] - (1 << i) >= depth[v]) {
            u = up[u][i];
        }
    }

    if (u == v) return u;

    for (int i = LOG - 1; i >= 0; --i) {
        if (up[u][i] != up[v][i]) {
            u = up[u][i];
            v = up[v][i];
        }
    }

    return up[u][0];
}

void solve(int cur, int prev)   {
    cout << "HI " << endl;
    temp[lis[cur]].push(depth[cur]);
    for (auto i : queries[cur]) { //pair<pair<int, int>, int>
        int tar = i.first.second;
        int to = i.first.first;
        int ind = i.second;
        if (temp[tar].top() >= depth[getLCA(cur, to)]) {
            ans[ind] = 1;
        }
    }
    for (auto i : adj[cur]) {
        if (i != prev)  {
            solve(i, cur);
        }
    }
    temp[lis[cur]].pop();
}

signed main()  {
    freopen("milkvisits.in", "r", stdin);
    freopen("milkvisits.out", "w", stdout);
    cin >> n >> m;
    lis.resize(n);
    adj.resize(n);
    up.resize(n);
    depth.resize(n);
    temp.resize(n);
    ans.resize(m);
    for (int i = 0; i < n; i++) {
        temp[i].push(-1);
    }
    for (int i = 0; i < n; i++) {
        up[i].resize(18);
        fill(up[i].begin(), up[i].end(), -1);
    }
    for (int i = 0; i < n; i++) {
        cin >> lis[i];
    }
    for (int i = 0; i < n-1; i++) {
        int x, y;
        cin >> x >> y;
        x -= 1;
        y -= 1;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    for (int i = 0; i < m; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        x -= 1;
        y -= 1;
        queries[x].push_back({{y, z}, i});
        queries[y].push_back({{x, z}, i});
    }
    cout << "ADDA " << endl;
    dfs(0, -1, 0);
    cout << "#TGA " << endl;
    solve(0, -1);
    cout << "ADAD a" << endl;
    for (int i = 0; i < m; i++) {
        cout << ans[i];
    }
    cout << endl;
    

}