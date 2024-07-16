#include <bits/stdc++.h>
using namespace std;

int N, L;
vector<vector<int>> schedule;
vector<vector<vector<int>>> next_show;
vector<int> length;
vector<pair<int, int>> dp;

int pct(int x) { return __builtin_popcount(x); }
int setbit(int n, int k) { return (n | (1 << k)); }
int getbit(int n, int k) { return (n & (1 << k)) >> k; }

int find_show_time(int t, int m) {
    auto it = upper_bound(schedule[m].begin(), schedule[m].end(), t);
    if (it == schedule[m].begin()) { return -1; }

    int start = *(it - 1);
    if (start + length[m] < t || start > t) { return -1; }

    return (it - 1) - schedule[m].begin();
    }

int main() {
    ifstream cin("movie.in");
    ofstream cout("movie.out");
    cin >> N >> L;

    length.resize(N);
    schedule.resize(N);
    next_show.resize(N, vector<vector<int>>(N, vector<int>(0, -1)));

    for (int i = 0; i < N; i++) {
        int t, v;
        cin >> t >> v;
        length[i] = t;
        int a;
        while (v) {
            cin >> a;
            schedule[i].push_back(a);
            v--;
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j) continue;
            for (int k = 0; k < schedule[i].size(); k++)    {
                next_show[i][j].push_back(find_show_time(schedule[i][k]+length[i], j));
            }
        }
    }

    dp.resize(1 << N, {-1, -1});

    int ans = N + 1;
    dp[0] = {0, 0};

    for (int i = 0; i < 1 << N; i++) {
        if (dp[i].first == -1) continue;
        for (int j = 0; j < N; j++) {
            if (getbit(i, j)) {
                continue;
            }
            int cur = setbit(i, j);

            int x;
            if (i == 0) {
                x = schedule[j][0] == 0 ? 0 : -1;
            } else {
                x = next_show[dp[i].first][j][dp[i].second];
            }
            if (x != -1) {
                if (dp[cur].first == -1 ||
                    schedule[dp[cur].first][dp[cur].second] + length[dp[cur].first] < schedule[j][x] + length[j]) {
                    dp[cur] = {j, x};
                }
                if (schedule[dp[cur].first][dp[cur].second] + length[dp[cur].first] >= L) {
                    ans = min(ans, pct(cur));
                }
            }
        }
    }

    cout << (ans == N + 1 ? -1 : ans) << endl;
}