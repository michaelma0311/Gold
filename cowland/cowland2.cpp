#include <bits/stdc++.h>
using namespace std;
#define int long long
//gptcode 
struct SegTree {
    int n;                 // original n
    int size;              // power-of-two size
    vector<int> base;      // initial values padded to size
    vector<int> lazy;      // pending xor tags

    SegTree(const vector<int>& a) {
        n = (int)a.size();
        size = 1;
        while (size < n) size <<= 1;
        base.assign(size, 0);
        for (int i = 0; i < n; i++) base[i] = a[i];
        lazy.assign(2 * size, 0);
    }

    void update(int l, int r, int x) { update(1, 0, size - 1, l, r, x); }

    void update(int node, int nl, int nr, int l, int r, int x) {
        if (r < nl || nr < l) return;
        if (l <= nl && nr <= r) {
            lazy[node] ^= x;     // xor-tag this whole segment
            return;
        }
        int mid = (nl + nr) >> 1;
        update(node << 1, nl, mid, l, r, x);
        update(node << 1 | 1, mid + 1, nr, l, r, x);
    }

    int query(int idx) { return query(1, 0, size - 1, idx, 0); }

    int query(int node, int nl, int nr, int idx, int accXor) {
        accXor ^= lazy[node];    // accumulate tags along path
        if (nl == nr) {
            // leaf corresponds to index nl
            return base[nl] ^ accXor;
        }
        int mid = (nl + nr) >> 1;
        if (idx <= mid) return query(node << 1, nl, mid, idx, accXor);
        else            return query(node << 1 | 1, mid + 1, nr, idx, accXor);
    }
};

int n, q;
const int MAXN = 200000;
const int LOG = 30;
vector<int> lis;
vector<vector<int>> adj;
int up[LOG][MAXN];
int dep[MAXN];
vector<int> siz;
vector<int> arr;
vector<int> tour;
map<int,int> mainds;
int cnt = 0;
void build_lca(int n, int root=0) {
    for (int k = 0; k < LOG;k++)  {
        for (int i = 0; i < n;i++)  {
            up[k][i] = -1;
        }
    }
    vector<bool> vis(n, false);
    queue<int> q;
    q.push(root);
    vis[root] = 1;
    dep[root] = 0;
    up[0][root] = -1;

    while (q.empty() == false)  {
        int v = q.front(); 
        q.pop();
        for (int i : adj[v]){
            if (vis[i] == false)  {
                vis[i] = 1;
                dep[i] = dep[v]+1;
                up[0][i] = v;
                q.push(i);
            }
        }
    }

    for (int i = 1; i < LOG; i++)  {
        for (int j = 0; j < n; j++)  {
            int mid = up[i-1][j];
            if (mid == -1)  {
                up[i][j] = -1;
            } else {
                up[i][j] = up[i-1][mid];
            }
        }
    }
}

int lift(int cur, int len)  {
    for (int k = 0; k < LOG; k++)  {
        if (cur != -1 && (len&(1<<k)))  {
            cur = up[k][cur];
        }
    }
    return cur;
}

int lca(int a, int b)  {
    if (dep[a] < dep[b])  {
        swap(a, b);
    }
    a = lift(a, dep[a]-dep[b]);
    if (a == b)  {
        return a;
    }
    for (int k = LOG-1; k >= 0; k--)  {
        if (up[k][a] != up[k][b])  {
            a = up[k][a];
            b = up[k][b];
        }
    }
    return up[0][a];
}
void dfs1(int cur, int prev)  {
    mainds[cur] = cnt;
    cnt += 1;
    tour.push_back(cur);
    siz[cur] = 1;
    for (int i : adj[cur])  {
        if (i == prev)  {
            continue;
        }
        dfs1(i, cur);
        siz[cur] += siz[i];
    }
}
void dfs(int cur, int prev)  {
    if (prev == -1)  {
        arr[cur] = lis[cur];
    } else  {
        arr[cur] = arr[prev]^lis[cur];
    }
    for (int i : adj[cur])  {
        if (i != prev)  {
            dfs(i, cur);
        }
    }
}

signed main()  {
    freopen("cowland.in", "r", stdin);
    freopen("cowland.out", "w", stdout);
    cin >> n >> q;
    
    adj.resize(n);
    lis.resize(n);
    arr.resize(n);
    siz.resize(n);
    for (int i = 0; i < n; i++)  {
        cin >> lis[i];
    }
    for (int i = 0; i < n-1; i++)  {
        int x, y;
        cin >> x >> y;
        x -= 1;
        y -= 1;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    
    build_lca(n);
    dfs(0, -1);
    dfs1(0, -1);
    vector<int> news(n);
    for (int i = 0; i < n; i++)  {
        news[i] = arr[tour[i]];
    }
    vector<int> ans;
    SegTree seg(news);
    for (int i = 0; i < q; i++)  {
        int typ, x, y;
        cin >> typ >> x >> y;
        x -= 1;
        if (typ == 1)  {
            seg.update(mainds[x], mainds[x]+siz[x]-1, lis[x]);
            seg.update(mainds[x], mainds[x]+siz[x]-1, y);
            lis[x] = y;
        } else  {
            y -= 1;
            int p = seg.query(mainds[x]) ^ seg.query(mainds[y]) ^ lis[lca(x, y)];
            ans.push_back(p);
        }
    }
    for (int i : ans)  {
        cout << i << endl;
    }


}