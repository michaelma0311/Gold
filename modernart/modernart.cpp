#include <bits/stdc++.h>

using namespace std;

int main()  {
    int n;
    cin >> n;
    vector<int> lis(n);
    for (int i = 0; i < n; i++) {
        cin >> lis[i];
    }
    vector<vector<int>> dp(n);
    for (int i = 0; i < n; i++) {
        dp[i].resize(n);
        for (int j = 0; j < n; j++) {
            dp[i][j] = INT_MAX;
        }
        dp[i][i] = 1;
    }
    for (int len = 0; len < n; len++) {
        for (int i = 0; i < n-len; i++)   {
            for (int j = i; j < i+len; j++) {
                int en = i+len;
                if (lis[i] != lis[en]) {
                    dp[i][en] = min(dp[i][en], dp[i][j] + dp[j+1][en]);
                } else  {
                    dp[i][en] = min(dp[i][en], dp[i][j] + dp[j+1][en]-1);
                }
            }
        }
    }
    cout << dp[0][n-1] << endl; 
}