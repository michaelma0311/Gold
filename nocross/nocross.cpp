#include <bits/stdc++.h>

using namespace std;

int main()  {
    freopen("nocross.in", "r", stdin);
	freopen("nocross.out", "w", stdout);
    int n;
    cin >> n;
    vector<int> lef(n);
    vector<int> rig(n);
    for (int i = 0; i < n; i++) {
        cin >> lef[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> rig[i];
    }
    vector<vector<int>> dp(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (abs(lef[i] - rig[i]) <= 4)  {
                dp[i][j] = dp[i-1][j-1] + 1;
            } else  {
                dp[i][j] = max(dp[i-1][j], max(dp[i][j-1], dp[i-1][j-1]));
            }
        }
    }
    cout << dp[n-1][n-1] << endl;
}