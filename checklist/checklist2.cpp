#include <bits/stdc++.h>
using namespace std;
int dist(pair<int, int> a, pair<int, int> b)    {
    return (a.first-b.first)*(a.first-b.first) + (a.second-b.second) * (a.second-b.second);
}
int main()  {
    int h, g;
    cin >> h >>  g;
    vector<pair<int, int>> lish(h);
    vector<pair<int, int>> lisg(g);
    for (int i =0 ; i < h; i++) {
        int x, y;
        cin >> x >> y;
        lish[i] = {x, y};
    }
    for (int j = 0; j < g; j++) {
        int x, y;
        cin >> x >> y;
        lisg[j] = {x, y};
    }
    vector<vector<int>> dp(h);
    for (int i = 0; i < h; i++) {
        dp[i].resize(g);
        fill(dp[i].begin(), dp[i].end(), INT_MAX);
    }
    dp[0][0] = dist(lish[0], lisg[0]);
    for (int i = 1; i < h; i++) {
        dp[i][0] = dp[i-1][0] + dist(lish[i-1], lish[i]);
    }
    for (int i = 1; i < g; i++) {
        dp[0][i] = dp[0][i-1] + dist(lisg[i-1], lisg[i]);
    }
    for (int i = 1; i < h; i++) {
        for (int j = 1; j < g; j++) {
            cout << i << ' ' << j << endl;
            dp[i][j] = min(dp[i-1][j] + dist(lish[i-1], lish[i]), dp[i][j-1] + dist(lisg[j-1], lisg[j]));
            cout << dp[i][j] << endl;
        }
    }
    for (int i = 0; i < h; i++) {
        cout << "ADAD  " << endl;
        for (int j = 0; j < g; j++) {
            cout << dp[i][j] << ' ';
        }
        cout << endl;
    }
    cout << dp[h-1][g-1] << endl;
}