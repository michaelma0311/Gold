#include <bits/stdc++.h>
using namespace std;
struct State {
    long long r, c, s, d;
};

long long n, m;
vector<vector<long long>> grid;
bool vis[1001][1001][2][4];
bool check(long long x, long long y, long long smell, long long direc)    {
    if (0 > x || x >= n || 0 > y || y >= m || vis[x][y][smell][direc] == true || (grid[x][y] == 3 && smell == 0) || grid[x][y] == 0) {
        return false;
    }
    return true;
}

signed main()  {
    freopen("dream.in", "r", stdin);
    freopen("dream.out", "w", stdout);
    cin >> n >> m;
    grid.resize(n);;
    for (long long i = 0; i < n; i++) {
        grid[i].resize(m);
    }
    for (long long i= 0; i < n; i++)  {
        for (long long j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }
    long long dp[n][m][2][4];
    queue<State> q;
    for (long long i = 0; i < n; i++) {
        for (long long j = 0; j < m; j++) {
            for (long long k = 0; k < 2; k++) {
                for (long long p = 0; p < 4; p++) {
                    dp[i][j][k][p] = INT_MAX;
                    vis[i][j][k][p] = false;
                }
            }
        }
    }
    //0 = Down
    //1 = Up
    //2 = Right
    //3 = Left
    q.push({0, 0, 0, 0});
    q.push({0, 0, 0, 2});
    for (int j = 0; j < 4; j++) {
        dp[0][0][0][j] = 0;
    }
    while (q.empty() == false)  {
        State cur = q.front();
        q.pop();
        long long x = cur.r;
        long long y = cur.c;
        long long smell = cur.s;
        long long direc = cur.d;
        //cout << x << ' ' << y << ' ' << smell << ' ' << direc << endl;
        //cout << "HI " << x << ' ' << y << ' ' << smell << ' ' << direc << endl;
        if (vis[x][y][smell][direc] == true)    {
            continue;
        }
        vis[x][y][smell][direc] = true;
        if (grid[x][y] == 1 || grid[x][y] == 3)    {
            if (grid[x][y] == 3 && smell == false)    {
                cout << "THESE IS SOMETHING TERRIBLE WRONG" << endl;
            }
            if (check(x+1, y, smell, 0))    {
                dp[x+1][y][smell][0] = min(dp[x+1][y][smell][0], dp[x][y][smell][direc]+1);
                q.push({x+1, y, smell, 0});
            }
            if (check(x, y+1, smell, 2))    {
                dp[x][y+1][smell][2] = min(dp[x][y+1][smell][2], dp[x][y][smell][direc]+1);
                q.push({x, y+1, smell, 2});
            }
            if (check(x-1, y, smell, 1))    {
                dp[x-1][y][smell][1] = min(dp[x-1][y][smell][1], dp[x][y][smell][direc]+1);
                q.push({x-1, y, smell, 1});
            }
            if (check(x, y-1, smell, 3))    {
                dp[x][y-1][smell][3] = min(dp[x][y-1][smell][3], dp[x][y][smell][direc]+1);
                q.push({x, y-1, smell, 3});
            }
        } else if (grid[x][y] == 2) {
            if (check(x+1, y, true, 0))    {
                dp[x+1][y][true][0] = min(dp[x+1][y][true][0], dp[x][y][smell][direc]+1);
                q.push({x+1, y, true, 0});
            }
            if (check(x, y+1, true, 2))    {
                dp[x][y+1][true][2] = min(dp[x][y+1][true][2], dp[x][y][smell][direc]+1);
                q.push({x, y+1, true, 2});
            }
            if (check(x-1, y, true, 1))    {
                dp[x-1][y][true][1] = min(dp[x-1][y][true][1], dp[x][y][smell][direc]+1);
                q.push({x-1, y, true, 1});
            }
            if (check(x, y-1, true, 3))    {
                dp[x][y-1][true][3] = min(dp[x][y-1][true][3], dp[x][y][smell][direc]+1);
                q.push({x, y-1, true, 3});
            }
        } else if (grid[x][y] == 4) {
            //cout << "THIS IS THE ONE " << x << ' ' << y << ' ' << smell << ' ' << direc << endl;
            pair<long long, long long> die = {0, 0};
            if (direc == 0) {
                die = {1, 0};
            } else if (direc == 1)  {
                die = {-1, 0};
            } else if (direc == 2)  {
                die = {0, 1};
            } else  {
                die = {0, -1};
            }
            if (check(x+die.first, y+die.second, false, direc))  {
                dp[x+die.first][y+die.second][false][direc] = min(dp[x+die.first][y+die.second][false][direc], dp[x][y][smell][direc]+1);
                q.push({x+die.first, y+die.second, false, direc});
            } else  {
                if (check(x+1, y, false, 0))    {
                    dp[x+1][y][false][0] = min(dp[x+1][y][false][0], dp[x][y][smell][direc]+1);
                    q.push({x+1, y, false, 0});
                }
                if (check(x, y+1, false, 2))    {
                    dp[x][y+1][false][2] = min(dp[x][y+1][false][2], dp[x][y][smell][direc]+1);
                    q.push({x, y+1, false, 2});
                }
                if (check(x-1, y, false, 1))    {
                    dp[x-1][y][false][1] = min(dp[x-1][y][false][1], dp[x][y][smell][direc]+1);
                    q.push({x-1, y, false, 1});
                }
                if (check(x, y-1, false, 3))    {
                    dp[x][y-1][false][3] = min(dp[x][y-1][false][3], dp[x][y][smell][direc]+1);
                    q.push({x, y-1, false, 3});
                }
            }
        }
    }
    long long ans = LLONG_MAX;
    for (long long i = 0; i < 2; i++) {
        for (long long j = 0; j < 4; j++) {
            ans = min(ans, (long long)dp[n-1][m-1][i][j]);
        }
    }
    if (ans >= INT_MAX) {
        cout << -1 << endl;
    } else  {
        cout << ans << endl;
    }
    //cout << ans << endl;
}