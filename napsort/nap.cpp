#include <bits/stdc++.h>
using namespace std;
#define int long long
int n;
int ansval = 0;
int maxnum = 0;
bool check(vector<int> lis, map<int,int> ma, int cur)   {
    int curind = -1;
    for (int i = 0; i < cur; i++) {
        int th = cur * (i+1)  - (i+1)*(i)/2;
        int num = distance(lis.begin(), upper_bound(lis.begin(), lis.end(), th));
        //cout << cur << ' ' << th << ' ' << curind << endl;
        if (ma.find(th) != ma.end())    {
            num -= 1;
        }
        if (num <= curind)   {
            curind += 1; 
        } else  {
            curind = num;
        }
    }
    //cout << curind << endl;
    if (curind != n-1)  {
        ansval = maxnum;
    } else  {
        ansval = cur*(cur+1)/2;
    }
    return curind < n;

}

signed main()  {
    //freopen("a.out", "w", stdout);
    int t;
    cin >> t;
    while (t--) {
        maxnum = 0;
        cin >> n;
        vector<int> lis(n);
        map<int, int> ma;
        for (int i = 0; i < n; i++) {
            cin >> lis[i];
            maxnum = max(maxnum, lis[i]);
            if (ma.find(lis[i]) == ma.end())    {
                ma[lis[i]] = 0;
            }
            ma[lis[i]] += 1;
        }
        //cout << maxnum << endl;
        sort(lis.begin(), lis.end());
        for (int i = 0; i < n; i++) {
            //cout << lis[i] << ' ';
        }
        //cout << endl;
        int lo = 0;
        int hi = n;
        int ans = 0;
        while (lo <= hi)    {
            int mid = (lo+hi)/2;
            if (check(lis, ma, mid))    {
                //cout << "VALID " << mid << endl;
                ans = min(ansval, (mid+1) * (mid+2)/2);
                lo = mid+1;
            } else  {
                hi = mid-1;
            }
        }
        cout << min(maxnum, min(ans, n*(n+1)/2)) << endl;
    }
}