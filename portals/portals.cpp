#include <bits/stdc++.h>
using namespace std;
#define int long long
vector<int> parent;
vector<int> imp;
int find(int x) {
  if (parent[x] != x) {
    parent[x] = find(parent[x]);  
  }
  return parent[x];
}

void unite(int x, int y) {
  int curx = find(x);
  int cury = find(y);
  if (curx != cury) {
    if (imp[curx] > imp[cury]) {
      parent[cury] = curx;
  } else if (imp[curx] < imp[cury]) {
      parent[curx] = cury;
  } else {
      parent[cury] = curx;
      imp[curx]++;
    }
  }
}
signed main()  {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  parent.resize(n*2);
  imp.resize(n*2);
  for (int i = 0; i < n*2; i++)   {
      parent[i] = i;
      imp[i] = 0;
  }
  vector<pair<int, int>> costs(n);
  vector<vector<int>> adj(2*n);
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    costs[i] = {x, i};
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    a -= 1;
    b -= 1;
    c -= 1;
    d -= 1;
    adj[a].push_back(i*2);
    adj[b].push_back(i*2);
    adj[c].push_back(i*2+1);
    adj[d].push_back(i*2+1);
  }
  for (auto i : adj)   {
      //cout << "ADAD " << i[0] << ' ' << i[1] << endl;
      unite(i[0], i[1]);
  }
  sort(costs.begin(), costs.end());
  int ans = 0;
  for (int i = 0; i < n; i++) {
    int curam = costs[i].first;
    int cur = costs[i].second;
    if (find(cur*2) != find(cur*2+1))   {
      unite(cur*2, cur*2+1);
      ans += curam;
    }
  }
  cout << ans << '\n';
}