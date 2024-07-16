#include <bits/stdc++.h>

using namespace std;
int dx[] = {1, 0, -1, 0, 3, 0, -3, 0, 2, 2, 1, 1, -1, -1, -2, -2};
int dy[] = {0, 1, 0, -1, 0, 3, 0, -3, 1, -1, 2, -2, 2, -2, 1, -1};
int main()  {
    freopen("visitfj.in","r",stdin);
	freopen("visitfj.out","w",stdout);
    int n, t;
    cin >> n >> t;
    vector<vector<int>> grid(n);
    vector<vector<int>> visited(n);
    vector<vector<int>> dist(n);
    for (int i = 0; i < n; i++) {
        grid[i].resize(n);
        visited[i].resize(n);
        dist[i].resize(n);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
            dist[i][j] = INT_MAX;
        }
    }
    priority_queue<pair<int, pair<int, int>>> q;
    q.push(make_pair(0, make_pair(0, 0)));
    dist[0][0] = 0;
    while (q.empty() == false)  {
        int curdist = q.top().first;
        //cout << curdist << endl;
        int curx = q.top().second.first;
        int cury = q.top().second.second;
        q.pop();
        if (visited[curx][cury])    {
            continue;
        }
        visited[curx][cury] = true;
        for (int i = 0; i < 16; i++)    {
            int r = curx + dx[i];
            int c = cury + dy[i];
            if (r < 0 || r >= n || c < 0 || c >= n) {
                continue;
            }
            if (dist[r][c] > dist[curx][cury] + 3 * t + grid[r][c]) {
                dist[r][c] = dist[curx][cury] + 3*t + grid[r][c];
                q.push(make_pair(-dist[r][c], make_pair(r, c)));
            }
        }
        int dists = n-curx-1+n-cury-1;
        if (dists < 3)  {
            dist[n-1][n-1] = min(dist[n-1][n-1], dist[curx][cury] + dists*t);
        }
    }
    cout << dist[n-1][n-1] << endl;
}