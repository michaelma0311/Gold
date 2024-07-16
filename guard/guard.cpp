#include <bits/stdc++.h>
using namespace std;

struct Cow {
    int height;
    int weight;
    int strength;
};

int main() {
    freopen("guard.in", "r", stdin);
    freopen("guard.out", "w", stdout);

    int n;
    int h;
    cin >> n >> h;

    vector<Cow> lis(n);
    for (int i = 0; i < n; i++) {
        cin >> lis[i].height >> lis[i].weight >> lis[i].strength;
    }

    vector<pair<int, int>> dp(1 << n);

    dp[0] = {0, INT32_MAX};
    for (int i = 1; i < (1 << n); i++) {
        dp[i] = make_pair(0, -1);
        for (int j = 0; j < n; j++) {
            if (i & (1 << j))   {
                dp[i].first += lis[j].height;
                int prev = i ^ (1 << j);
                //cout << prev << ' ' << dp.size()<< endl;
                dp[i].second = max(dp[i].second, min(dp[prev].second - lis[j].weight, lis[j].strength));
            }
        }
    }

    int ans = -1;
    for (int i = 1; i < (1 << n); i++) {
        if (dp[i].first >= h) { 
            ans = max(dp[i].second, ans); 
        }
    }

    if (ans < 0) {
        cout << "Mark is too tall" << endl;
    } else {
        cout << ans << endl;
    }
}