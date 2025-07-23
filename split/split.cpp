#include <bits/stdc++.h>

using namespace std;
#define int long long
bool cmp(const pair<int, int>& a, const pair<int, int>& b) {
    return a.second < b.second;
}

signed main()  {
    freopen("split.in", "r", stdin);
	freopen("split.out", "w", stdout);
    int n;
    cin >> n;
    vector<pair<int, int>> lis(n);
    for (int i = 0; i < n; i++) {
        cin >> lis[i].first >> lis[i].second;
    }
    sort(lis.begin(), lis.end());
    vector<int> ymax(n);
    vector<int> ymin(n);
    ymax[n-1] = lis[n-1].second;
    ymin[n-1] = lis[n-1].second;
    for (int i = n-2; i >= 0; i--) {
        ymax[i] = max(ymax[i+1], lis[i].second);
        ymin[i] = min(ymin[i+1], lis[i].second);
    }
    int curmin = LLONG_MAX;
    int curmax = 0;
    int ans = LLONG_MAX;
    for (int i = 0; i < n-1; i++) {
        curmin = min(curmin, lis[i].second);
        curmax = max(curmax, lis[i].second);
        ans = min(ans, ((lis[i].first - lis[0].first) * (curmax-curmin)) + (lis.back().first - lis[i+1].first) * (ymax[i+1] - ymin[i+1]));
    }
    int ansx = lis.back().first - lis[0].first;
    sort(lis.begin(), lis.end(), cmp);
    vector<int> xmax(n);
    vector<int> xmin(n);
    xmax[n-1] = lis[n-1].first;
    xmin[n-1] = lis[n-1].first;
    for (int i = n-2; i >= 0; i--)  {
        xmax[i] = max(xmax[i+1], lis[i].first);
        xmin[i] = min(xmin[i+1], lis[i].first);
    }
    curmin = LLONG_MAX;
    curmax = 0;
    for (int i = 0; i < n-1; i++)   {
        curmin = min(curmin, lis[i].first);
        curmax = max(curmax, lis[i].first);
        ans = min(ans, ((lis[i].second - lis[0].second) * (curmax-curmin)) + (lis.back().second - lis[i+1].second) * (xmax[i+1] - xmin[i+1]));
    }
    int ansy = lis.back().second - lis[0].second;
    cout << ansx*ansy - ans << endl;

}