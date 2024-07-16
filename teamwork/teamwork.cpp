#include <bits/stdc++.h>
using namespace std;

int main()  {
    freopen("teamwork.in","r",stdin);
	freopen("teamwork.out","w",stdout);
    int n, k;
    cin >> n >> k;
    vector<int> lis(n);
    for (int i = 0; i < n; i++) {
        cin >> lis[i];
    }
    vector<int> dp(n);
    dp[0] = 0;
    for (int i = 0; i < n; i++) {
        int temp = 0;
        int cur = i;
        int cnt = 1;
        int masu = lis[i];
        while (cur >= 0 && cur >= i-k+1) {
            masu = max(masu, lis[cur]);
            temp = max(temp, dp[cur] + cnt * masu);
            cur -= 1;
            cnt += 1;
        }
        dp[i+1] = temp;
        //cout << i << ' ' << temp << endl;
    }
    cout << dp[n] << endl;
}