#include <bits/stdc++.h>

using namespace std;
#define int long long

signed main()  {
    int n, q;
    cin >> n >> q;
    vector<int> lis(n);
    map<int,int> ma;
    for (int i = 0; i < n; i++)  {
        cin >> lis[i];
        ma[lis[i]] += 1;
    }
    map<int,set<int>> inds;
    for (auto& i : ma) {
        inds[i.second].insert(i.first);
    }
    vector<int> ans;
    for (int i = 0; i < q; i++)  {
        int a, b;
        cin >> a >> b;
        a -= 1;
        int old_val = lis[a];
        inds[ma[old_val]].erase(old_val);
        if (inds[ma[old_val]].size() == 0) {
            inds.erase(ma[old_val]);
        }
        ma[old_val] -= 1;
        if (ma[old_val] == 0) {
            ma.erase(old_val);
        } else {
            inds[ma[old_val]].insert(old_val);
        }
        if (old_val != b && ma.count(b) > 0) {
            inds[ma[b]].erase(b);
            if (inds[ma[b]].size() == 0) {
                inds.erase(ma[b]);
            }
        }

        lis[a] = b;
        ma[b] += 1;
        inds[ma[b]].insert(b);
        int manum = inds.rbegin()->first;
        int curans = 0;
        vector<pair<int,int>> maxv;
        for (auto& j : inds) {
            maxv.push_back({j.first, *j.second.rbegin()});
        }
        //cout << "HI " << endl;
        for (auto i : maxv) {
            //cout << i.first << ' ' << i.second << endl;
        }
        int hi = maxv.size() - 1;
        int curmx = 0;
        for (auto& j : inds)  {
            int curmi = *j.second.begin();
            while (hi >= 0 && maxv[hi].first >= manum-j.first) {
                curmx = max(curmx, maxv[hi].second);
                hi -= 1;
            }
            curans = max(curans, curmx - curmi);
        }
        ans.push_back(curans);
    }
    for (int i : ans) {
        cout << i << endl;
    }
}