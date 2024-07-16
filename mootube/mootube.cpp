#include <bits/stdc++.h>

using namespace std;
struct DSU {
    vector<long long> e;
    void init(long long n) { e = vector<long long>(n, -1); }
    long long get(long long x) { return e[x] < 0 ? x : e[x] = get(e[x]); };
    bool sameSet(long long x, long long y) { return get(x) == get(y); };
    long long size(long long x) { return -e[get(x)]; }
    bool unite(long long x, long long y) {
        x = get(x), y = get(y);
        if (x == y) return false;
        if (e[x] > e[y]) swap(x, y);
        e[x] += e[y];
        e[y] = x;
        return true;
    }
};

bool cmp(const pair<long long, pair<long long, long long>> &a,
         const pair<long long, pair<long long, long long>> &b) {
    return a.second.second > b.second.second;
}

int main()  {
    freopen("mootube.in","r",stdin);
	freopen("mootube.out","w",stdout);
    long long n, q;
    cin >> n >> q;
    vector<pair<long long, pair<long long, long long>>> adj(n-1);
    for (long long i = 0; i < n-1; i++)   {
        long long x, y, w;
        cin >> x >> y >> w;
        x -= 1;
        y -= 1;
        adj[i] = make_pair(w, make_pair(x, y));
    }
    //cout << "ADAD" << endl;
    DSU lis;
    lis.init(n);
    //cout << "ADADAD" << endl;
    vector<pair<long long, pair<long long, long long>>> que(q);
    for (long long i = 0; i < q; i++) {
        long long x, y;
        cin >> x >> y;
        y -= 1;
        que[i] = make_pair(i, make_pair(y, x));
    }
    //cout << "ADAD" << endl;
    sort(que.begin(), que.end(), cmp);
    sort(adj.begin(), adj.end(), greater<pair<long long, pair<long long, long long>>>());
    vector<long long> ans(q);
    long long ind = 0;
    //cout << "ADAD" << endl;
    for (auto i : que)  {
        long long curk = i.second.second;
        long long curnum = i.second.first;
        //cout << "ADAD" << endl;
        while (ind < que.size() && adj[ind].first >= curk)    {
            //cout << "AD" << endl;
            lis.unite(adj[ind].second.first, adj[ind].second.second);
            ind += 1;
        }
        ans[i.first] = lis.size(curnum)-1;
    }
    for (long long i = 0; i < q; i++) {
        cout << ans[i] << endl;
    }

}