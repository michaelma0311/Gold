#include <bits/stdc++.h>

using namespace std;

 
int n, m, k;
vector<int> adj[100001];
map<pair<int,int>, int> grid;
int H[100000], Y[100000];
 
map<int,int> dist;
 
void dijkstra(int source)
{
    set<pair<int,int>> q;
    q.insert(make_pair(0,source));
    while (!q.empty()) {
        int i = q.begin()->second;
        q.erase(q.begin());
        for (auto j : adj[i])  {
            if (dist.count(j) == 0 || dist[i] + grid[make_pair(i,j)] < dist[j]) {
                dist[j] = dist[i] + grid[make_pair(i,j)];
                q.insert(make_pair(dist[j],j));
            }
        }
    }
}
 
int main()
{
    freopen("dining.in","r",stdin);
	freopen("dining.out","w",stdout);
    cin >> n >> m >> k;
    for (int i=0; i<m; i++) {
        int a, b, t;
        cin >> a >> b >> t;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
        grid[make_pair(a,b)] = t;
        grid[make_pair(b,a)] = t;
    }
    for (int i=0; i<k; i++) {
        cin >> H[i] >> Y[i];
        H[i]--;
    }

    dijkstra (n-1);
    map<int,int> orig_dist = dist;
    for (int i=0; i<k; i++) {
        adj[n].push_back(H[i]);
        grid[make_pair(n,H[i])] = orig_dist[H[i]] - Y[i];
    }
    dist.clear();
    dijkstra (n);
    for (int i=0; i<n-1; i++) {
        cout << (dist[i] <= orig_dist[i]) << "\n";
    }
    return 0;
}