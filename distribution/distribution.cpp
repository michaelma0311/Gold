#include <bits/stdc++.h>
using namespace std;
#define int long long
int n;
vector<int> lis;
vector<pair<int, int>> nums;

int solve(int x, int y) {
  int lo = 0;
  int hi = n;
  int ans = 0;
  while (lo+1 < hi) {
    int mid = (lo+hi)/2;
    if (mid + 1 == n || mid-1 < 0)  {
        ans = mid;
        break;
    }
    //cout << "ADAD " << lo << ' ' << hi << "\n";
    int prevind = mid-1;
    int cur = nums[mid].first * x + nums[mid].second * y;
    while (prevind != -1 && nums[prevind].first * x + nums[prevind].second * y == cur)  {
        prevind -= 1;
    }
    int prev = nums[prevind].first * x + nums[prevind].second * y;
    int nextind = mid+1;
    while (nextind != n && nums[nextind].first * x + nums[nextind].second * y == cur)  {
        nextind += 1;
    }
    int next = nums[nextind].first * x + nums[nextind].second * y;
    //cout << prev << ' ' << cur << ' ' << next << "\n";
    if (prev > cur && cur < next)   {
        ans = mid;
        break;
    } else if (prev >= cur && cur >= next)    {
        ans = mid;
        lo = mid;
    } else if (prev <= cur && cur <= next)  {
        ans = mid;
        hi = mid;
      }
  }
  int curans  = x * nums[ans].first + y * nums[ans].second;
  if (nums[0].first * x + nums[0].second * y < curans)    {
    ans = 0;
  }
  if (nums[n-1].first * x + nums[n-1].second * y < curans)    {
    ans = n-1;
  }
  return x * nums[ans].first + y * nums[ans].second;
}

signed main()  {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);   
  cin >> n;
  lis.resize(n);
  nums.resize(n);
  int sumleft = 0;
  int sumright = 0;
  for (int i = 0; i < n; i++) {
      cin >> lis[i];
      sumright += lis[i];
  }
  sort(lis.begin(), lis.end());
  for (int i = 0; i < n; i++) {
      int x = lis[i] * i - sumleft;
      int y = sumright - lis[i] * (n-i);
      nums[i] = {x, y};
      sumleft += lis[i];
      sumright -= lis[i];
  }
  int q;
  cin >> q;
  vector<int> ans(q);
  for (int i = 0; i < q; i++) {
      int x, y;
      cin >> x >> y;
      ans[i] = solve(x, y);
      //cout << ans[i] << "\n";
  }
  for (int i : ans)   {
      cout << i << "\n";
  }
}