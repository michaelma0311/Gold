#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
using namespace std;

int check(const vector<int>& lis, int x, int n)   {
    int fir = *(lis.begin());
    int ind = 0;
    int ans= 0;
    while(ind < n)  {
        int lim = lis[ind] + x;
        auto it = upper_bound(lis.begin()+ind, lis.end(), lim);
        ind = it-lis.begin();
        ans += 1;
    }
    return ans;
} 

int main()  {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);   
    int n;
    cin >> n;
    map<int, int> cnt;
    map<int, vector<int>> ma;
    vector<int> blank;
    for (int i = 1; i <= n; i++)    {
        ma[i] = blank;
        cnt[i] = 0;
    }
    vector<int> lis(n);
    for (int i =0 ; i < n; i++) {
        cin >> lis[i];
        cnt[lis[i]] += 1;
        ma[lis[i]].push_back(i);
    }
    vector<int> less;
    vector<int> more;
    int p = sqrt(n);
    for (int i =0 ; i <=n; i++) {
        if (cnt[i] == 0)    {
            continue;
        }
        if (cnt[i] <= p)    {
            less.push_back(i);
        } else  {
            more.push_back(i);
        }
    }
    vector<int> diff(n+1);
    vector<int> ansnum(n+1);
    for (int i = 0; i < less.size(); i++)   {
        int cur = less[i];
        vector<int> temp = ma[cur];
        vector<pair<int,int>> curans;
        for (int num = 1; num <= cnt[cur]; num++)   {
            int lo = 1;
            int hi = n;
            int ans = 0;
            while (lo <= hi)    {
                int mid = (lo+hi)/2;
                if (check(temp, mid, cnt[cur]) <= num)   {
                    ans = mid;
                    hi = mid-1;
                } else  {
                    lo = mid+1;
                }
            }
            curans.push_back({num, ans});
        }
        int last = curans[0].second;
        diff[curans[0].second] += curans[0].first;
        for (int j = 1; j < cnt[cur]; j++)  {
            diff[curans[j].second] += curans[j].first;
            diff[last] -= curans[j].first;
            last = curans[j].second;
        }
    }
    for (int i = 0; i < more.size(); i++)   {
        int cur = more[i];
        vector<int> temp = ma[cur];
        for (int x = 1; x <= n; x++)    {
            int curans = check(temp, x, cnt[cur]);
            ansnum[x] += curans;
        }
    }
    int cur = 0;
    for (int i = 1; i <= n; i++)    {
        cur += diff[i];
        ansnum[i] += cur;
    }
    for (int i = 1; i <= n; i++)    {
        cout << ansnum[i] << endl;
    }
}