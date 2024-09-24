#include <bits/stdc++.h>
using namespace std;

signed main()  {
    freopen("cowjog.in", "r", stdin);
    freopen("cowjog.out", "w", stdout);
    long long n, t;
    cin >> n >> t;
    vector<pair<long long, long long>> lis(n);
    for (long long i = 0; i < n; i++) {
        cin >> lis[i].first >> lis[i].second;
        lis[i].second = lis[i].second * t + lis[i].first;
        //cout << "ADAD " << lis[i].first << ' ' << lis[i].second << endl;
    }
    sort(lis.begin(), lis.end());
    multiset<long long> nums;
    for (long long i = 0; i < n; i++) {
        long long ind = lis[i].first;
        long long val = lis[i].second;
        //cout << ind << ' ' << val << ' ' << *nums.lower_bound(val)<< endl;
        if (nums.lower_bound(val) == nums.begin()) {
            nums.insert(val);
        } else  {
            nums.erase(--nums.lower_bound(val));
            nums.insert(val);
        }
    }
    cout << nums.size() << endl;
}