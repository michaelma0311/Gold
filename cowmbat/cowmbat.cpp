#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, m, k;
string a;
vector<vector<int>> adj;
vector<vector<int>> dist;
signed main()  {
  freopen("cowmbat.in", "r", stdin);
  freopen("cowmbat.out", "w", stdout);
  cin >> n >> m >> k;
  adj.resize(m);
  dist.resize(m);
  cin >> a;
  for (int i = 0; i < m; i++) {
    adj[i].resize(m);
    dist[i].resize(m);
    fill(dist[i].begin(), dist[i].end(), INT_MAX);
  }
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < m; j++) {
        cin >> adj[i][j];
    }
  }
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < m; j++) {
      dist[i][j] = adj[i][j];
    }
  }
  for (int b = 0; b < m; b++) {
    for (int i = 0; i < m; i++)  {
      for (int j = 0; j < m; j++) {
        dist[i][j] = min(dist[i][j], dist[i][b] + dist[b][j]);
      }
    }
  }
  vector<vector<int>> psum(n+1, vector<int> (m));
  for (int i = 1; i <= n; i++)  {
    for (int j = 0; j < m; j++){
      psum[i][j] = psum[i-1][j] + dist[a[i-1] - 'a'][j];
    }
  }
  vector<vector<int>> dp(n+1, vector<int> (m));
  fill(dp[0].begin(), dp[0].end(), 0);
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < m; j++) {
      dp[i][j] = dp[i-1][j] + dist[a[i-1]-'a'][j];
      if (i >= k) {
        for (int e = 0; e < m; e++){
          dp[i][j] = min(dp[i][j], dp[i-k][e] + psum[i][j] - psum[i-k][j]);
        }
      }
    }
  }
  //cout << "AD d" << "\n";
  int bes = INT_MAX;
  for (int j = 0; j < m; j++) {
    bes = min(bes, dp[n][j]);
  }
  cout << bes << "\n";

}