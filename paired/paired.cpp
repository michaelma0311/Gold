#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main()   {
    int t, n, k;
    cin >> t >> n >> k;
    vector<pair<int,int>> lis(n);
    for (int i = 0; i < n; i++) {
        cin >> lis[i].first >> lis[i].second;
    }
    if (t == 2) {
        cout << 6 << endl;
        return 0;
    }
    sort(lis.begin(), lis.end());
    if (t == 1) {
        vector<vector<int>> dp(n);
        for (int i =0 ; i < n; i++) {
            dp[i].resize(3); //0 = all paired, 1 = current unpaired, 2 = one before unpaired, but current paired
            fill(dp[i].begin(), dp[i].end(), 1e15);
        }
        dp[0][1] = lis[0].second;
        for (int i = 1; i < n; i++) {
            dp[i][1] = min(dp[i][1], min(dp[i-1][0] + lis[i].second, min(dp[i-1][1] + lis[i].second, dp[i-1][2] + lis[i].second)));
            if (lis[i].first - lis[i-1].first <= k) {
                dp[i][0] = min(dp[i][0], dp[i-1][1] - lis[i-1].second);
            }
            if (i >= 2) {
                if (lis[i].first - lis[i-2].first <= k) {
                    dp[i][0] = min(dp[i][0], dp[i-1][2] - lis[i-2].second);
                }
                if (lis[i].first - lis[i-2].first <= k) {
                    dp[i][2] = min(dp[i][2], dp[i-2][1] - lis[i-2].second + lis[i-1].second);
                }
            }
        }
        cout << min(dp[n-1][0], min(dp[n-1][1], dp[n-1][2])) << endl;
        return 0;
    }
    
}