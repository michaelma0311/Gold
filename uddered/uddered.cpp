#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main() {
	//freopen("a.in", "r", stdin);
	string s;
	cin >> s;
	map<int, int> ma;
	int ind = 0;
	for (int i = 0; i < s.size(); i++)	{
		if (ma.find(s[i]) == ma.end())	{
			ma[s[i]] = ind++;
		}
	} 
	int n = ind;
	vector<vector<int>> adj(n);
	for (int i = 0; i < n; i++)	{
		adj[i].resize(n);
	}
	for (int i = 1; i < s.size(); i++)	{
		adj[ma[s[i-1]]][ma[s[i]]] += 1;
	}
	vector<int> dp(1 << n);
	fill(dp.begin(), dp.end(), LLONG_MAX);
	dp[0] = 1;
	for (int mask = 1; mask < (1 << n); mask++)	{
		for (int j = 0; j < n; j++)	{
			if (mask & (1 << j))	{
				int cursum = dp[mask ^ (1 << j)];
				for (int k = 0; k < n; k++)	{
					if (mask & (1 << k))	{
						cursum += adj[j][k];
					}
				}
				dp[mask] = min(dp[mask], cursum);
			}
		}
	}
	/*for (int i = 0; i < (1 << n); i++)	{
		cout << i << ' ' << dp[i] << endl;
	}
		*/
	cout << dp[(1 << n)-1] << "\n";
}