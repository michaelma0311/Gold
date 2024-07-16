#include <bits/stdc++.h>

using namespace std;

signed main()  {
    freopen("hayfeast.in","r",stdin);
	freopen("hayfeast.out","w",stdout);

    long long n, m;
    cin >> n >> m;
    vector<long long> flavor(n);
    vector<long long> spicy(n);
    for (long long i = 0; i < n; i++) {
        long long x, y;
        cin >> x >> y;
        flavor[i] = x;
        spicy[i] = y;
    }
    long long lo = 0;
    long long hi = 0;
    long long ans = INT_MAX;
    long long cursum = flavor[0];
    multiset<long long> nums = {spicy[0]};
    while (true)    {
        if (hi == n)  {
            break;
        }
        hi += 1;
        while (cursum >= m)    {
            ans = min(ans, *nums.rbegin());
            cursum -= flavor[lo];
            nums.erase(nums.find(spicy[lo]));
            lo += 1;
            if (lo > hi)    {
                break;
            }
        }
        
        nums.insert(spicy[hi]);
        cursum += flavor[hi];
        //cout << lo << ' ' << hi << ' ' << cursum << endl;

    }
    cout << ans << endl;
}