#include <bits/stdc++.h>

using namespace std;

int main()  {
    freopen("cowrun.in","r",stdin);
	freopen("cowrun.out","w",stdout);
    int n;
    cin >> n;
    vector<int> lis(n);
    for (int i = 0; i < n; i++) {
        cin >> lis[i];
    }
    sort(lis.begin(), lis.end());
    vector<vector<vector<int>>> dp(
        n + 1, vector<vector<int>>(n + 1, vector<int>(2, INT32_MAX)));
    for (int i = n-1; i >= 0; i--)  {
        for (int j = i; j < n; j++) {
            if (i == j) {
                dp[i][j][0] = abs(lis[i]) * n;
                dp[i][j][1] = abs(lis[i]) * n;
            } else  {
                int rem = n-(j-i);
                if (i < n)  {
                    dp[i][j][0] = min(dp[i+1][j][1] + abs(lis[j]-lis[i]) * rem, dp[i+1][j][0] + abs(lis[i+1] - lis[i]) * rem);  
                }
                if (j > 0)  {
                    dp[i][j][1] = min(dp[i][j-1][1] + abs(lis[j-1] - lis[j]) * rem, dp[i][j-1][0] + abs(lis[j]-lis[i]) * rem);
                }
            }
        }
    }
    cout << min(dp[0][n-1][0], dp[0][n-1][1]) << endl;
}