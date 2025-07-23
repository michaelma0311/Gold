#include <bits/stdc++.h>
using namespace std;

void solve()    {
    int n;
    cin >> n;
    vector<pair<int, int>> lis(n);
    for (int i = 0; i < n; i++) {
        cin >> lis[i].first >> lis[i].second;
    }
    sort(lis[i].begin(), lis[i].end());
}

int main()  {
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        solve();
    }
}