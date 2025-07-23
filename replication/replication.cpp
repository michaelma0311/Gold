#include <bits/stdc++.h>

using namespace std;
int n, d;
vector<vector<char>> grid;
vector<vector<int>> nearest;
vector<vector<bool>> visited;
vector<vector<int>> ans;
bool inbounds(int x, int y) {
    if (0 <= x && x < n && 0 <= y && y < n && grid[x][y] != '#' && nearest[x][y] == -1) {
        return true;
    }
    return false;
}
bool inbounds2(int x, int y) {
    //cout << "HIEWG " << x << ' ' << y << ' ' << grid[x][y] << ' ' << visited[x][y] << endl;
    if (0 <= x && x < n && 0 <= y && y < n && grid[x][y] != '#' && visited[x][y] == false) {
        return true;
    }
    return false;
}

void solve(int x, int y, int siz)   {
    for (int i = x-siz; i < x; i++) {
        ans[i][y-(i-(x-siz))] += 1;
        ans[i][y+(i-(x-siz))+1] -= 1;
    }
    ans[x][y-siz] += 1;
    ans[x][y+siz+1] -= 1;
    for (int i = x+siz; i >= x+1; i--) {
        ans[i][y-((x+siz)-i)] += 1;
        ans[i][y+((x+siz)-i)+1] -= 1;
    }
}

int main()  {
    cin >> n >> d;
    nearest.resize(n);
    grid.resize(n);
    ans.resize(n);

    vector<vector<bool>> can(n);
    vector<vector<int>> numcan(n);
    vector<vector<bool>> sol(n);
    visited.resize(n);
    queue<pair<int, pair<int, int>>> starting;
    for (int i = 0; i < n; i++) {
        nearest[i].resize(n);
        grid[i].resize(n);
        can[i].resize(n);
        visited[i].resize(n);
        sol[i].resize(n);
        ans[i].resize(n);
        fill(visited[i].begin(), visited[i].end(), false);
        numcan[i].resize(n);
        fill(nearest[i].begin(), nearest[i].end(), -1);
    }
    queue<pair<int, pair<int, int>>> q;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];  
            if (grid[i][j] == 'S')  {
                starting.push({0, {i, j}});
                can[i][j] = true;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == '#')  {
                nearest[i][j] = 0;
                if (inbounds(i+1, j))   {
                    q.push({1, {i+1, j}});
                }
                if (inbounds(i-1, j))   {
                    q.push({1, {i-1, j}});
                }
                if (inbounds(i, j+1))   {
                    q.push({1, {i, j+1}});
                }
                if (inbounds(i, j-1))   {
                    q.push({1, {i, j-1}});
                }
            }
        }
    }
    while (q.empty() == false)  {
        int cnt = q.front().first;
        int i = q.front().second.first;
        int j = q.front().second.second;
        q.pop();
        //cout << "hi " << i << ' ' << j << ' ' << grid[i][j] << endl;
        if (nearest[i][j] != -1)    {
            continue;
        }
        nearest[i][j] = cnt;
        if (inbounds(i+1, j))   {
            q.push({cnt+1, {i+1, j}});
        }
        if (inbounds(i-1, j))   {
            q.push({cnt+1, {i-1, j}});
        }
        if (inbounds(i, j+1))   {
            q.push({cnt+1, {i, j+1}});
        }
        if (inbounds(i, j-1))   {
            q.push({cnt+1, {i, j-1}});
        }
    }
    /*for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << grid[i][j] << ' ' << nearest[i][j] << ' ';
        }
        cout << endl;
    }
    cout << "AD " << endl;
    */
    while (starting.empty() == false)   {
        int curnum = starting.front().first;
        int curx = starting.front().second.first;
        int cury = starting.front().second.second;
        starting.pop();
        if (!inbounds2(curx, cury)) {
            continue;
        }
        visited[curx][cury] = true;
        //cout << "HI " << curx << ' ' << cury << endl;
        int near = nearest[curx][cury];
        int expand = 0;
        int maex = 0;
        if (curnum == 0)    {
            expand = 0;
            maex=0;
        } else if (curnum%d == 0)    {
            expand = (curnum-1)/d;
            maex = curnum/d;
        } else  {
            expand = curnum/d;
            maex = curnum/d;
        }
        if (near > expand)  {
            can[curx][cury] = true;
            numcan[curx][cury] = min(near-1, maex);
            if (maex >= near)    {
                continue;
            }
            starting.push({curnum+1, {curx+1, cury}});
            starting.push({curnum+1, {curx-1, cury}});
            starting.push({curnum+1, {curx, cury+1}});
            starting.push({curnum+1, {curx, cury-1}});
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (can[i][j])  {
                solve(i, j, numcan[i][j]);
            }
        }
    }
    int tot = 0;
    for (int i = 0; i < n; i++) {
        int cur = 0;
        for (int j = 0; j < n; j++) {
            cur += ans[i][j];
            if (cur != 0)   {
                sol[i][j] = true;
                tot += 1;
            }
        }
    }
    /*
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << grid[i][j] << ' ' << can[i][j] << ' ';
        }
        cout << endl;
    }
    cout << "AF " << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << grid[i][j] << ' ' << numcan[i][j] << ' ';
        }
        cout << endl;
    }
        
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << sol[i][j] << ' ';
        }
        cout << endl;
    }*/
    cout << tot << endl;

}