#include <bits/stdc++.h>

using namespace std;

int main()  {
    freopen("hayfeast.in","r",stdin);
	freopen("hayfeast.out","w",stdout);

    long long n, m;
    cin >> n >> m;
    vector<pair<long long, long long>> lis(n);
    for (long long i = 0; i < n; i++) {
        long long x, y;
        cin >> x >> y;
        lis[i] = make_pair(x, y);
    }
    long long lo = 0;
    long long hi = 0;
    long long cur = 0;
    long long ans= INT_MAX;
    long long spc = 0;
    bool tof = true;
    multiset<long long> nums;
    nums.insert(-1*(lis[0].second));
    cur += lis[0].first;
    while (tof) {
        //cout << "ADAD" << endl;
        while (cur >= m && nums.empty() == false)    {
            ans = min(ans, -1*(*nums.begin()));
            //cout << "ERASE " << *nums.begin() << endl;
            //cout << lis[lo].second << endl;
            nums.erase(nums.find(-1 * lis[lo].second));
            cur -= lis[lo].first;
            lo += 1;
            //cout << cur << ' ' << ans << endl;
        }
        if (hi + 1 >= n) {
            //cout << "LO " << lo << endl;
            tof = false;
            break;
        } 
        hi += 1;
        nums.insert(-1*lis[hi].second);
        cur += lis[hi].first;
        //cout << cur << ' ' << ans<< endl;
    }
    cout << ans << endl;
}