#include <bits/stdc++.h>
using namespace std;

long long calc(long long x) {
    return x*(x+1)*(2*x+1)/6;
}

signed main()  {
    freopen("cbarn.in","r",stdin);
	freopen("cbarn.out","w",stdout);

    long long n;
    cin >> n;
    vector<long long> lis(n);
    bool allones = true;
    for (long long i = 0; i < n; i++) {
        cin >> lis[i];
        if (lis[i] != 1)    {
            allones = false;
        }
    }
    if (allones == true)    {
        cout << 0 << endl;
        return 0;
    }
    long long cursu = 0;
    long long curnums = 0;
    long long ans = 0;
    map<long long, long long> temp;
    for (long long j = 0; j < 3*n; j++) {
        long long i = j%n;
        long long move = cursu - curnums;
        //cout << j << ' ' << i << ' ' <<lis[i] << ' ' << cursu << ' ' << curnums << endl;
        if (lis[i] >= 1) {
            temp[i] = calc(lis[i]-1+move) - calc(move-1);
            //ans += calc(lis[i]-1+move) - calc(move-1);
        }
        //cout << "HI " << ans << endl;
        cursu += lis[i];
        curnums += 1;
        if (curnums >= cursu)   {
            curnums = 0;
            cursu = 0;
        }
    }
    for (long long i = 0; i < n; i++) {
        ans += temp[i];
    }
    cout << ans << endl;

}