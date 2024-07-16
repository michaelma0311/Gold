#include <bits/stdc++.h>
using namespace std;

int main() {
	freopen("snakes.in", "r", stdin);
	freopen("snakes.out", "w", stdout);

	int n, k;
	cin >> n >> k;
	vector<int> groups(n + 1);
	for (int i = 1; i <= n; i++) { cin >> groups[i]; }
	vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));

	int largest_group = -1;
	int space_used = 0;
	for (int i = 1; i <= n; i++) {
		largest_group = max(largest_group, groups[i]);
		dp[i][0] = largest_group * i;

		for (int j = 1; j <= k; j++) {
			dp[i][j] = INT32_MAX;
			int net_size = groups[i];
			for (int c = i - 1; c >= 0; c--) {
				dp[i][j] = min(dp[i][j], dp[c][j - 1] + net_size * (i - c));
				net_size = max(net_size, groups[c]);
			}
		}
		space_used += groups[i];
	}
	cout << dp[n][k] - space_used << "\n";
}
