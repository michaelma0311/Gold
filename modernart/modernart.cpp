#include <bits/stdc++.h>
using namespace std;
 
int main(){
    int n;
    cin >> n;
    vector<int> lis(n);
    for (int i = 0; i < n; i++) {
        cin >> lis[i];
    }
    vector<vector<int>> dp(n);
    for (int i = 0; i < n; i++) {
        dp[i].resize(n);
    }
    for (int i = 0; i < n; i++) {
        dp[i][i] = 1;
    }
    for (int siz = 1; siz < n; siz++)   {
        for (int i = 0; i+siz < n; i++) {
            int j = i+siz;
            dp[i][j] = dp[i+1][j] + 1;
            for (int k = i+1; k <j; k++)   {
                if (lis[i] == lis[k])   {
                    dp[i][j] = min(dp[i][j], dp[i+1][k-1] + dp[k][j]);
                }
            }
            if (lis[i] == lis[j])   {
                dp[i][j] = min(dp[i][j], dp[i+1][j-1]+1);
            }
            if (lis[i] == lis[i+1]) {
                dp[i][j] = min(dp[i][j], dp[i+1][j]);
            }
        }
    }
    cout << dp[0][n-1] << endl;
}
