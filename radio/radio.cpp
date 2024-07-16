#include <bits/stdc++.h>

using namespace std;
int dist(pair<int, int> x, pair<int, int> y)    {
    return abs(x.first-y.first)*abs(x.first-y.first) + abs(x.second-y.second) * abs(x.second-y.second);
}
int main()  {
    freopen("radio.in","r",stdin);
	freopen("radio.out","w",stdout);
    int n, m;
    cin >> n >> m;
    int sjx, sjy;
    cin >> sjx >> sjy;
    int sbx, sby;
    cin >> sbx >> sby;
    string john;
    cin >> john;
    string bess;
    cin >> bess;
    vector<pair<int, int>> jmov(n+1);
    int curjx, curjy;
    curjx = sjx;
    curjy = sjy;
    jmov[0].first = curjx;
    jmov[0].second = curjy;
    for (int i = 0; i < n; i++) {
        if (john[i] == 'N') {
            curjy += 1;
        } else if (john[i] == 'S')  {
            curjy -= 1;
        } else if (john[i] == 'E')  {
            curjx += 1;
        } else  {
            curjx -= 1;
        }
        jmov[i+1].first = curjx;
        jmov[i+1].second = curjy;
    }
    vector<pair<int, int>> bmov(m+1);
    int curbx, curby;
    curbx = sbx;
    curby = sby;
    bmov[0].first = curbx;
    bmov[0].second = curby;
    for (int i = 0; i < m; i++) {
        if (bess[i] == 'N') {
            curby += 1;
        } else if (bess[i] == 'S')  {
            curby -= 1;
        } else if (bess[i] == 'E')  {
            curbx += 1;
        } else  {
            curbx -= 1;
        }
        bmov[i+1].first = curbx;
        bmov[i+1].second = curby;
    }
    vector<vector<int>> dp(n+1);
    for (int i = 0; i < n+1; i++) {
        dp[i].resize(m+1);
        fill(dp[i].begin(), dp[i].end(), INT_MAX);
    }

    dp[0][0] = dist(make_pair(sjx, sjy), make_pair(sbx, sby));
    for (int i = 0; i < n+1; i++) {
        for (int j = 0; j < m+1; j++) {
            //cout << i << ' ' << j << ' ' << dp[i][j] << endl;
            if (i+1 < n+1)    {
                //cout << "first " << endl;
                //cout << "AFDADd " << i << ' ' << j << ' ' << n << ' ' << m << endl;
                //cout << dp.size() << ' ' << i+1<< endl;
                //cout << dp[i+1][0] << endl;
                dp[i+1][j] = min(dp[i+1][j], dp[i][j] + dist(jmov[i+1], bmov[j]));
                //cout << i << ' ' << j << ' ' << dp[i+1][j] << ' ' << dp[i][j] << ' ' << dist(jmov[i+1], bmov[i]) <<"RESULT " << i+1 << ' ' << j<< endl;
            }
            if (j+1 < m+1)  {
                //cout << "second"<< endl;
                dp[i][j+1] = min(dp[i][j+1], dp[i][j] + dist(jmov[i], bmov[j+1]));
            }
            if (i+1 < n+1 && j+1 < m+1) {
                //cout << "third "<< endl;
                dp[i+1][j+1] = min(dp[i+1][j+1], dp[i][j] + dist(jmov[i+1], bmov[j+1]));
            }
        }
    }
    cout << dp[n][m] - dp[0][0] << endl;
}