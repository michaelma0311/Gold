#include <bits/stdc++.h>

using namespace std;
#define int long long

  

void solve()    {
    int n;
    cin >> n;
    vector<pair<int,int>> cows;
    vector<pair<int,int>> apples;
    priority_queue<pair<int,int>> pq;
    vector<pair<pair<int,int>,pair<int,int>>> lis; //t-x, t+x, typ, n,
    for (int i = 0; i < n; i++) {
        int typ, t, x, num;
        cin >> typ >> t >> x >> num;
        lis.push_back({{x-t, x+t},{typ, num}});
    }
    sort(lis.begin(), lis.end(),
     [](const auto& a, const auto& b){
        if (a.first.first == b.first.first) {
            return a.second.first > b.second.first;
        }
        return a.first.first < b.first.first;});
    multiset<pair<int,int>> cur;
    int ans =0;
    for (int i = 0; i < n; i++) {
        if (lis[i].second.first == 2)   {
            cur.insert({lis[i].first.second, lis[i].second.second});
            //cout << "INSERTED " << lis[i].first.second << ' ' << lis[i].second.second << endl;
        } else  {
            int num = lis[i].second.second;
            
            while (num != 0 && !cur.empty())    {
                //cout << "INSHDE " << lis[i].first.second << ' ' << num << endl;
                auto it = cur.lower_bound({lis[i].first.second, -LLONG_MAX});
                if (it == cur.end())  {
                    break;
                }
                int curval = (*it).first;
                int curnum = (*it).second;
                if (num >= curnum)  {
                    num -= curnum;
                    cur.erase(it);
                    ans += curnum;
                } else  {
                    ans += num;
                    cur.erase(it);
                    cur.insert({curval, curnum-num});
                    num = 0;
                }
            }
        }
    }
    cout << ans << endl;
    
}


signed main()   {
    int t;
    t = 1;
    for (int i = 0; i < t; i++) {
        solve();
    }
}