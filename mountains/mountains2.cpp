#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template<typename T>
using ost = tree<
  T,
  null_type,
  less<T>,
  rb_tree_tag,
  tree_order_statistics_node_update
>;
#define int long long
int n;
int solve(vector<int>& lis)  {
    int ans = 0;
    
    return ans;
}

signed main()   {
    cin >> n;
    vector<int> lis(n);
    for (int i = 0; i < n; i++) {
        cin >> lis[i];
    }
    int q;
    cin >> q;
    int ans =0;
    vector<ost<pair<int,double>>> peaks(n);
    vector<ost<pair<double,int>>>peaks2(n);
    for (int i = 0; i < n; i++) {
        double curmax = -INT_MAX;
        for (int j = i+1; j < n; j++)   {
            double sl = (double)(lis[j]-lis[i])/(double)(j-i);
            if (sl >= curmax)    {
                curmax = sl;
                //cout << "WEGWE  " << i << ' ' << j << endl;
                peaks[i].insert({j, sl});
                peaks2[i].insert({sl,  j});
                ans += 1;
            }
        }
    }
    //cout << "HI" << solve(lis) << endl;
    for (int _ = 0; _ < q; _++) {
        int x, y;
        cin >> x >> y;
        x -= 1;
        lis[x] += y;
        ans -= peaks[x].size();
        peaks[x].clear();
        peaks2[x].clear();
        double curmax = -INT_MAX;
        for (int j = x+1; j < n; j++)   {
            double sl = (double)(lis[j]-lis[x])/(double)(j-x);
            if (sl >= curmax)    {
                curmax = sl;
                //cout << "WEGWE  " << x << ' ' << j << ' ' << sl<< endl;
                peaks[x].insert({j, sl});
                peaks2[x].insert({sl, j});
                ans += 1;
            }
        }
        //cout << "CUR " << ans << endl;
        for (int i = 0; i < x; i++) {
            //cout << "CUR " << ans << endl;
            //cout << "LIS{X} " << lis[x] << ' ' << "LIS{I} " << lis[i] << " X I " << x << ' ' << i << endl;
            double slp = (double)(lis[x]-lis[i])/(double)(x-i);
            auto it = peaks[i].upper_bound({x, -DBL_MAX});
            if (it != peaks[i].begin()) {
                it--;
            }
            
            int p = peaks[i].order_of_key({x, -DBL_MAX});
            //cout << "NEW " << i << ' ' << slp << ' ' << it->first << ' ' << it->second << endl;
            if ((it)->second > slp) {
                continue;
            }
            //cout << "SIZ " << peaks2[i].size() << endl;
            //for (auto p : peaks2[i]) {
                //cout << "PEAKS2 " << p.first << ' ' << p.second << endl;
            //}
            auto it2 = peaks2[i].lower_bound({slp, x});
            it2--;
            int p2 = peaks2[i].order_of_key({slp, x});
            p2 -= 1;
            //cout << "REM " << i << ' ' << slp << ' '<<p << ' ' << p2 << endl;
            ans -= (p2-p+1);
            int curlef = p2-p+1;
            if (it->first == x)  {
                it--;
            }
            it++;
            while (curlef != 0) {
                //cout << "ERSAED " << it->first << ' ' << it->second << endl;
                auto [a,b] = *it;

                peaks2[i].erase({b,a});
                //cout << "A" << endl;
                it = peaks[i].erase(it);
                //cout << "WGEG " << endl;
                curlef -= 1;
            }
            peaks[i].insert({x, slp});
            peaks2[i].insert({slp, x});
            ans += 1;
        }
        cout << ans << endl;
    }
}
