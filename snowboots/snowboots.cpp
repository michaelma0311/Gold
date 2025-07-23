#include <bits/stdc++.h>

using namespace std;

int main()  {
    freopen("snowboots.in","r",stdin);
	freopen("snowboots.out","w",stdout);
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> snow(n);
    vector<int> am(n);
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        am[i] = x;
        snow[i] = make_pair(x, i);
    }
    vector<pair<int, int>> boots(m);
    vector<pair<int, int>> unsorb(m);
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        boots[i] = make_pair(x, y);
        unsorb[i] = make_pair(x, y);
    }
    sort(boots.begin(), boots.end());
    sort(snow.begin(), snow.end());
    sort(am.begin(), am.end());
    map<int, int> ma;
    int maind = n-1;
    set<int> ad;
    ad.insert(0);
    ad.insert(n-1);
    ma[0] = n-1;
    set<int> curdiff;
    map<int, int> cnt;
    cnt[n-1] = 1;
    curdiff.insert(n-1);
    for (int i = 0; i < n; i++) {
        int ind = snow[i].second;
        if (ind == 0 || ind == n-1) {
            continue;
        }
        //cout << i << endl;
        auto it1 = ad.lower_bound(ind);
        auto it = it1;
        it--;
        //cout << distance(ad.begin(), it) << ' ' << distance(ad.begin(), it1) << endl;
        //cout << "CURRENT " << *it1 << ' ' << *it << endl;
        cnt[(*it1)-((*it))] -= 1;
        if (cnt[(*it1)-((*it))] == 0)   {   
            curdiff.erase(curdiff.find(((*it1))-((*it))));
        }
        //cout <<" HERE " << endl;
        curdiff.insert(((*it1))-ind);
        if (cnt.find(((*it1))-ind) == cnt.end())    {
            cnt[((*it1))-ind] = 0;
        }
        cnt[((*it1))-ind] += 1;
        if (cnt.find(ind-((*it))) == cnt.end()) {
            cnt[ind-((*it))] = 0;
        }
        curdiff.insert(ind-((*it)));
        cnt[ind-((*it))] += 1;
        ad.insert(ind);
        ma[snow[i].first] = *curdiff.rbegin();
    }
    vector<int> ans(m);
    //cout << "HI " << endl;
    for (int i = 0; i < m; i++) {
        int dep, len;
        dep = unsorb[i].first;
        len = unsorb[i].second;
        //cout << "HI " << dep << endl;
        auto it = upper_bound(am.begin(), am.end(), dep);
        it--;
        //cout << "HIWEGW " << *it << endl;
        if (len >= ma[*it]) {
            ans[i] = 1;
        } else  {
            ans[i] = 0;
        }
    }
    for (int i = 0; i < m; i++) {
        cout << ans[i] << endl;
    }

}