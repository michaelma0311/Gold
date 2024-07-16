#include <bits/stdc++.h>

using namespace std;

int main()  {
    freopen("lasers.in","r",stdin);
	freopen("lasers.out","w",stdout);
    int n, xl, yl, xb, yb;
    cin >> n;
    vector<pair<int, int>> points(n+2);
    unordered_map<int, vector<int>> lis[2];
    vector<int> ans(n+2);
    fill(ans.begin(), ans.end(), INT_MAX);
    for (int i = 0; i < n+2; i++) {
        int x, y;
        cin >> x >> y;
        points[i].first = x;
        points[i].second = y;
        lis[0][x].push_back(i);
        lis[1][y].push_back(i);
    }
    queue<pair<int, int>> q;
    q.push({0, -1});
    q.push({0, 1});
    ans[0] = 0;
    while (!q.empty())  {
        pair<int, int> fir = q.front();
        q.pop();
        int cur = fir.first;
        int dir = fir.second;
        //cout << "ADAD " << cur << ' ' << dir << endl;
        int dirs;
        if (dir == -1)  {
            for (int i : lis[0][points[cur].first]) {
                if (i == cur)   {
                    continue;
                }
                //cout << "EGWEGG " << i << endl;
                if (ans[i] == INT_MAX)  {
                    ans[i] = min(ans[i], ans[cur] + 1);
                    q.push({i, 1});
                }
            }
        } else  {
            for (int i : lis[1][points[cur].second])    {
                if (i == cur)   {
                    continue;
                }
                if (ans[i] == INT_MAX)  {
                    ans[i] = min(ans[i], ans[cur] + 1);
                    q.push({i, -1});
                }
            }
        }
    }
    if (ans[1] == INT_MAX)  {
        cout << -1 << endl;
    } else  {
        cout << ans[1] - 1 << endl;
    }
}