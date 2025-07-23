#include <bits/stdc++.h>
using namespace std;
//faster version
int main()  {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);   
  int n, m;
  cin >> n >> m;
  vector<vector<int>> adj(n);
  for (int i = 0; i < n; i++) {
    adj[i].resize(n);
  }
  for (int i = 0; i < m; i++) {
    int x, y;
    cin >> x >> y;
    x -= 1;
    y -= 1;
    adj[x][y] = 1;
    adj[y][x] = 1;
  }
  vector<int> subcost((1 << n));
  for (int i = 0; i < (1 << n); i++)  {
    int curnum = 0;
    for (int j = 0; j < n; j++) {
      for (int k = j+1; k < n; k++)   {
        if (((1 << j) & i) && ((1 << k) & i))   {
          if (adj[j][k] == 1) {
            curnum += 1;
          } else  {
            curnum -= 1;
          }
        } 
      }
    }
    //cout << "curnum " <<i << ' '  << curnum << "\n";
    subcost[i] = curnum;
  }
  vector<int> dp((1 << n));
  dp[0] = n*(n-1)/2 - m;
  for (int i = 1; i < (1 << n); i++) {
    dp[i] = INT_MAX;
    for (int j = i; j; j = (j-1) & i) {
      dp[i] = min(dp[i], dp[i&~j] + subcost[j]);
    }
  }
  cout << dp[(1 << n) - 1] << "\n";
}