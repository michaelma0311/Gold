#include <bits/stdc++.h>

using namespace std;
int n;
const int maxV = 21;
vector<vector<int>> grid;
int dist[maxV][maxV][4][maxV][maxV][4];
struct state    {
    int x1;
    int y1;
    int dir1;
    int x2;
    int y2;
    int dir2;
};
queue<state> lis;
int main()  {
    cin >> n;
    grid.resize(n);
    for (int i = 0; i < n; i++) {
        grid[i].
    }
}