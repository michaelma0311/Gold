#include <bits/stdc++.h>

using namespace std;
#define int long long
const int mod = 1e9+7;
vector<int> fac;
vector<int> inv_f;
int power(int x, int y)  {
  if (y == 0) {
    return 1;
  }
  int p = power(x, y / 2) % mod;
  p = (p * p) % mod;
  if (y%2 == 0)   {
    return p;
  } else  {
    return (x*p)%mod;
  }
}
int choose(int cur, int k)    {
  return (((fac[cur] * inv_f[k]) % mod) * (inv_f[cur-k])) % mod;
}
signed main()  {
  int n, k, l;
  cin >> k >> n >> l;
  string a;
  cin >> a;
  fac.resize(n+1);
  inv_f.resize(n+1);
  fac[0] = 1;
  for (int i = 1; i <= n; i++)    {
    fac[i] = (fac[i-1] * i)%mod;
  }
  inv_f[n] = power(fac[n], mod-2);
  for (int i = n-1; i >= 0; i--)  {
    inv_f[i] = (inv_f[i+1] * (i+1)) % mod;
  }
  int ans = 1;
  vector<int> lis;
  int cur = 0;
  for (int i = n-1; i >= 0; i--)  {
    if (a[i] == 'M')    {
      lis.push_back(cur);
      cur -= k;
    } else  {
      cur += 1;
    }
  }
  for (int i : lis)   {
    ans *= choose(i, k);
    ans %= mod;
  }
  cout << power(ans, l) << "\n";
}