#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main()  {
    int n;
    cin >> n;
    vector<int> lis(n);
    int big = 0;
    for (int i= 0; i < n; i++)  {
        cin >> lis[i];
        big = max(big, lis[i]);
    }
    vector<int> arr(big+1);
    for (int i = 0; i < n; i++) {
        arr[lis[i]] += 1;
    }
    for (int i = 1; i <= big; i++)    {
        arr[i] += arr[i-1];
    }
    int ans = 0;
    for (int x = 1; x <= big; x++)  {
        vector<pair<int, int>> cnt;
        for (int y = 1; y*x <= big; y++)    {
            cnt.push_back({y, arr[min(big, x*(y+1)-1)] - arr[x*y-1]});
            //cout << "ADD " << x  << endl;
        }
        vector<pair<int, int>> odds;
        for (pair<int, int> i : cnt)   {
            if (i.second%2 == 1)   {
                odds.push_back(i);
            }
        }
        if (odds.size() == 1)   {
            if (odds[0].first == 1)   {
                ans += odds[0].second;
            }
        } else if (odds.size() == 2)    {
            if (odds[0].first+1 == odds[1].first)   {
                ans += odds[1].second;
            }
        }
    }
    cout << ans << endl;
}