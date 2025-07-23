#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main()  {
    freopen("exercise.in","r",stdin);
	freopen("exercise.out","w",stdout);
    int n, mod;
    cin >> n >> mod;
    vector<bool> isp(n+1);
    fill(isp.begin(), isp.end(), true);
    isp[0] = false;
    isp[1] = false;
    for (int p = 2; p*p <= n; p++)  {
        if (isp[p] == true) {
            for (int i = p*p; i <= n; i+=p) {
                isp[i] = false;
            }
        }
    }
    vector<int> nums;
    for (int i = 2; i <= n; i++)    {
        if (isp[i]) {
            //cout << "HIE FAS" << endl;
            nums.push_back(i);
        }
    }
    int numprimes = nums.size();
    vector<vector<int>> dp(numprimes+1);
    for (int i = 0; i < numprimes+1; i++)   {
        dp[i].resize(n+1);
        fill(dp[i].begin(), dp[i].end(), -1);
    }
    dp[0][0] = 0;
    for (int i = 0; i < numprimes; i++) {
        for (int j = 0; j <= n; j++) {
            if (dp[i][j] == -1) {
                continue;
            }
            if (dp[i+1][j] == -1)   {
                dp[i+1][j] = dp[i][j];
            } else  {
                dp[i+1][j] += dp[i][j];
            }
            dp[i+1][j] %= mod;
            //cout << "HI " << i << ' ' << j << ' ' << dp[i+1][j] << ' ' << dp[i][j] << endl;
            int k = nums[i];
            while (j+k <= n)    {
                dp[i+1][j+k] = max(dp[i+1][j+k], (long long)0);
                dp[i+1][j+k] %= mod;
                if (j == 0) {
                    dp[i+1][j+k] += k;

                } else  {
                    dp[i+1][j+k] += (dp[i][j]*k)%mod;
                }
                dp[i+1][j+k] %= mod;
                k *= nums[i];
                k %= mod;
            }
        }
        //cout << "end " << nums[i] << endl;
    }
    int ans = 0;
    for (int i = 0; i <= n; i++)    {
        //cout << i << ' ' << dp[numprimes][i] << endl;
        if (dp[numprimes][i] == -1) {
            if (i == n) {
                ans += n;
                ans %= mod;
            } else if (i == 1)  {
                ans += 1;
                ans %= mod;
            }
            continue;
        }
        ans += dp[numprimes][i];
        ans %= mod;
    }
    cout << ans << endl;
}