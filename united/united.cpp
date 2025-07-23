#include <bits/stdc++.h>
using namespace std;
#define int long long
int n;
vector<int> bitlis;
 
void update(int i, int ad) {
    while (i < n) {
        bitlis[i] += ad;
        i = i | (i + 1);
    }
}
 
int query(int i) {
    int sum = 0;
    while (i >= 0) {
        sum += bitlis[i];
        i = (i & (i + 1)) - 1;
    }
    return sum;
}
signed main()  {
    cin >> n;
    vector<int> lis(n);
    bitlis.resize(n);
    map<int, int> ma;
    for (int i = 0; i < n; i++) {
        cin >> lis[i];
        ma[lis[i]] = -1;
    }
    int ans = 0;
    ma[lis[0]] = 0;
    for (int i = 1; i < n; i++) {
        if (ma[lis[i]] == -1)   {
            ans += i-query(i);
        } else  {
            //cout << lis[i] << ' ' << ma[lis[i]] << ' ' << query(i) << ' ' << query(ma[lis[i]]) << ' ' << query(n-1) << endl;
            ans += i-ma[lis[i]]-1-(query(i) - query(ma[lis[i]]));
            update(ma[lis[i]], 1);
        }
        //cout << i << ' ' << ans << endl;
        ma[lis[i]] = i;
    }
    cout << ans << endl;
}