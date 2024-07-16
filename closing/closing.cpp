#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> e;
    DSU(int N) : e(N, -1) {}

    int get(int x) { return e[x] < 0 ? x : e[x] = get(e[x]); }

    bool same_set(int a, int b) { return get(a) == get(b); }

    int size(int x) { return -e[get(x)]; }

    bool unite(int x, int y) {
        x = get(x), y = get(y);
        if (x == y) return false;
        if (e[x] > e[y]) swap(x, y);
        e[x] += e[y];
        e[y] = x;
        return true;
    }
};

int main() {
    freopen("closing.in", "r", stdin);
    freopen("closing.out", "w", stdout);
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<bool> col(n);
    vector<int> lis(n);
    for (int i = 0; i < n; i++) {
        cin >> lis[i];
        lis[i]--;
    }

    DSU dsu(n);
    reverse(lis.begin(), lis.end());

    col[lis[0]] = 1;
    vector<string> ans = {"YES"};
    int cc = 1;
    for (int i = 1; i < n; i++) {
        cc++;
        col[lis[i]] = 1;
        for (int j : adj[lis[i]])   {
            if (col[j])    {
                if (dsu.unite(lis[i], j))   {
                    cc -= 1;
                }
            }
        }
        ans.push_back(cc == 1 ? "YES" : "NO");
    }
    reverse(ans.begin(), ans.end());

    
    for (const string &i : ans) { 
        cout << i << '\n';
    }
}
