#include <bits/stdc++.h>

using namespace std;
#define int long long
const int mod = 1e9+7;
vector<int> cnt;

int get(int cur)    {
    if (cur == -1)  {
        return 0;
    }
    return cnt[cur];
}

signed main()   {
    int n, m, q;
    cin >> n >> m >> q;
    vector<int> lis(n);
    vector<int> diff(n+1);
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        x -= 1;
        y -= 1;
        diff[x] += 1;
        diff[y+1] -= 1;
    }
    int cur=  0;
    for (int i = 0; i < n; i++) {
        cur += diff[i];
        if (cur%2 == 0) {
            lis[i] = 0;
        } else  {
            lis[i] = 1;
        }
    }
    vector<int> pref(n+1);
    vector<int> pow2(n+1);
    pow2[0] = 1;
    for (int i = 0; i < n; i++) {
        pref[i+1] = pref[i] * 2 + lis[i];
        pref[i+1] %= mod;
        pow2[i+1] = pow2[i]*2;
        pow2[i+1] %= mod;
    }
    cnt.resize(n);
    cnt[0] = lis[0];
    for (int i= 1; i < n; i++)  {
        cnt[i] = cnt[i-1] + lis[i];
    }
    vector<int> ans(q);
    for (int i = 0; i < q; i++) {
        int l, r, k;
        cin >> l >> r >> k;
        l -= 1;
        r -= 1;
        int cur1 = get(r);
        cur1 -= get(l-1);
        //cout << "HI " << l << ' ' << r << ' ' << cur1 << endl;
        if (cur1 >= k)  {
            ans[i] = pow2[k]-1;
            continue;
        }
        int curl = l;
        int curr = r;
        int curans = 0;
        while (curl <= curr)    {
            int mid = (curl+curr)/2;
            //cout << "INSIDE " << mid << ' ' << get(mid-1) << ' ' << get(curl-1) << ' ' << (r-mid+1) << endl;
            if (get(mid-1)-get(l-1)+(r-mid+1) >= k)    {
                curl = mid+1;
                curans = mid;
            } else  {
                curr = mid-1;
            }
        }
        //cout << curans << endl;
        //cout << pref[r+1] << ' ' << pref[curans] << ' ' << ((pref[r+1] - (pref[curans]*pow2[r-curans+1])%mod)+mod)%mod << endl;
        /// cout << curans-l << endl;
        //cout << (pow2[(k-(r-curans+1))]-1) << endl;
        ans[i] = ((pow2[(k-(r-curans+1))]-1) * pow2[r-curans+1])%mod +((pref[r+1] - (pref[curans]*pow2[r-curans+1])%mod)+mod)%mod;
        ans[i] %= mod;
    }
    for (int i = 0; i < q; i++) {
        cout << ans[i] << endl;
    }
}