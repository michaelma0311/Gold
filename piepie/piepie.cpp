#include <bits/stdc++.h>
using namespace std;
bool cmp(const pair<pair<long long, long long>, long long>& a, const pair<pair<long long, long long>, long long>& b) {
    return a.first.second < b.first.second;
}
bool lcmp2(const pair<pair<long long, long long>, long long>& a, long long value) {
    return a.first.second < value;
}
bool lcmp1(const pair<pair<long long, long long>, long long>& a, long long value) {
    return a.first.first < value;
}
signed main()  {
    freopen("piepie.in","r",stdin);
    freopen("piepie.out","w",stdout);
    
    long long n, d;
    cin >> n >> d;
    queue<pair<long long, long long>> q;
    vector<pair<pair<long long, long long>, long long>> lis((long long)2*n);
    vector<pair<pair<long long, long long>, long long>> bess(n);
    vector<pair<pair<long long, long long>, long long>> els(n);
    vector<long long> ans((long long)2*n);
    fill(ans.begin(), ans.end(), (long long)-1);
    for (long long i = 0; i < (long long)2*n; i++)   {
        long long x, y;
        cin >> x >> y;
        if (i >= n) {
            els[i%n] = {{x, y}, i};
        } else  {
            bess[i] = {{x, y}, i};
        }
        lis[i] = {{x, y}, i};
        if (x == (long long)0 || y == (long long)0)   {
            //cout << "DADA " << i << endl;
            q.push({i, (long long)1});
            if (y == 0) {
                ans[i] = (long long)1;
            }
        }
    }
    sort(bess.begin(), bess.end(), cmp);
    sort(els.begin(), els.end());
    
    while (!q.empty())  {
        long long cur = q.front().first;
        long long scor = q.front().second;
        q.pop();
        pair<long long, long long> vals = lis[cur].first;
        long long ind = lis[cur].second;
        //cout << "UBSUDE " << ind << ' ' << scor << endl;
        if (ind >= n)   { //Elsie's turn
            auto it = lower_bound(bess.begin(), bess.end(), vals.second - d, [](const pair<pair<long long, long long>, long long>& a, long long value){
                return lcmp2(a, value);
            });
            while (it != bess.end() && (*it).first.second <= vals.second) {
                if (ans[(*it).second] != (long long)-1)    {
                    it++;
                    continue;
                }
                ans[(*it).second] = scor + (long long)1;
                q.push({((*it).second), scor+(long long)1});
                it++;
            }
        } else  {
            auto it = lower_bound(els.begin(), els.end(), vals.first - d, [](const pair<pair<long long, long long>, long long>& a, long long value){
                return lcmp1(a, value);
            });
            //cout << "HI " << vals.first-d << ' ' << (*it).second << endl;
            while (it != els.end() && (*it).first.first <= vals.first)  {
                //cout << "INSIDE " <<(*it).second << ' ' << ans[(*it).second]<< endl;
                if (ans[(*it).second] != (long long)-1)    {
                    it++;
                    continue;
                }
                //cout << "SFA " << endl;
                ans[(*it).second] = scor+(long long)1;
                q.push({((*it).second), scor+(long long)1});
                it++;
            }
        }
    }
    for (long long i = 0; i < n; i++) {
        cout << ans[i] << endl;
    }
}