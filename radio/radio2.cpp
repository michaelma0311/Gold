#include <bits/stdc++.h>
using namespace std;

int dist(pair<int, int> a, pair<int, int> b)	{
    return (a.first-b.first)*(a.first-b.first) + (a.second-b.second) * (a.second-b.second);
}

int main()	{
    freopen("radio.in","r",stdin);
	freopen("radio.out","w",stdout);
    int n, m;
    cin >> n >> m;
    pair<int, int> ns;
    pair<int, int> bs;
    cin >> ns.first >> ns.second;
    cin >> bs.first >> bs.second;
    vector<pair<int, int>> ncords(n+1);
    vector<pair<int, int>> bcords(m+1);
    ncords[0] = ns;
    bcords[0] = bs;
    string s;
    cin >> s;
    map<char, pair<int, int>> direcs;
    direcs['W'] = {-1, 0};
    direcs['E'] = {1, 0};
    direcs['N'] = {0, 1};	
    direcs['S'] = {0, -1};
    for (int i = 0; i < n; i++)	{
        ns.first += direcs[s[i]].first;
        ns.second += direcs[s[i]].second;
        ncords[i+1] = ns;
        //cout << ns.first << ' ' << ns.second << endl;
    }
    string b;
    cin >> b;
    for (int i = 0; i < m; i++)	{
        bs.first += direcs[b[i]].first;
        bs.second += direcs[b[i]].second;
        bcords[i+1] = bs;
        //cout << bs.first << ' ' << bs.second << endl;
    }
    vector<vector<int>> dp(n+1);
    for (int i = 0; i <= n; i++)	{
        dp[i].resize(m+1);
        fill(dp[i].begin(), dp[i].end(), INT_MAX);
    }
    dp[0][0] = 0;
    for (int i = 0; i <= n; i++)	{
        for (int j = 0; j <= m; j++)	{
            //cout << i << ' ' << j << endl;
            if (i+1 <= n)	{
                dp[i+1][j] = min(dp[i+1][j], dp[i][j] + dist(ncords[i+1], bcords[j]));
            }
            if (j+1 <= m)	{
                dp[i][j+1] = min(dp[i][j+1], dp[i][j] + dist(ncords[i], bcords[j+1]));
            }
            if (i+1 <= n && j+1 <= m)	{
                dp[i+1][j+1] = min(dp[i+1][j+1], dp[i][j] + dist(ncords[i+1], bcords[j+1]));
            }
        }
    }
    cout << dp[n][m] << endl;
}