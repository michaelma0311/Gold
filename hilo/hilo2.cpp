#include <bits/stdc++.h>
using namespace std;
int main()  {
    freopen("a.in", "r", stdin);
    //freopen("a.out", "w", stdout);
    int n;
    cin >> n;
    vector<int> lis(n);
    for (int i = 0; i < n; i++) {
        cin >> lis[i];
    }
    map<int, int> incs;
    int lo = 0;
    while (lo < n)  {
        int hi = lo;
        while (lis[hi+1] >= lis[hi] && hi+1 < n)   {
            hi += 1;
        }
        //cout << lo << ' ' << hi << endl;
        while (lo <= hi)    {
            incs[lis[lo]] = hi;
            lo += 1;
        }
    }
    //cout << incs[1] << ' ' << incs[3] << ' ' << incs[2] << endl;
    set<int> nums;
    vector<int> ans(n+1);
    nums.insert(lis[0]);
    for (int i = 1; i < n; i++) {
        auto it = nums.lower_bound(lis[i]);
        if (it != nums.end())   {
            int a = *it;
            cout << a << ' ' << incs[a] << endl;
            if (incs[a] >= i-1) {
                ans[lis[i]] += 1;
                ans[a] -= 1;
            }
        }
        nums.insert(lis[i]);
    }
    int tot = 0;
    for (int i = 0; i <= n; i++)    {
        tot += ans[i];
        cout << tot << endl;
    }
    
}