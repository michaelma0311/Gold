#include <bits/stdc++.h>
using namespace std;

signed main()  {
    freopen("angry.in","r",stdin);
    freopen("angry.out","w",stdout);
    long long n;
    cin >> n;
    vector<long long> lis(n);
    for (long long i = 0; i < n; i++) {
        cin >> lis[i];
    }
    sort(lis.begin(), lis.end());
    vector<long long> dleft(n);
    dleft[0] = 0;
    unordered_map<long long, long long> curma;
    curma[0] = lis[0];
    for (long long i = 1; i < n; i++) {
        long long prevnum = dleft[i-1];
        if (dleft[i-1] < 2)    {
            dleft[i] = max(dleft[i-1] + 1, lis[i]-lis[i-1]);
        } else  {
            if (curma.find(prevnum-1) != curma.end())  {
                if (lis[i] - curma[prevnum-1] <= prevnum) {
                    dleft[i] = prevnum;
                } else  {
                    dleft[i] = max(dleft[i-1] + 1, lis[i]-lis[i-1]);
                }
            } else  {
                dleft[i] = max(dleft[i-1] + 1, lis[i]-lis[i-1]);
            }
        }
        curma[dleft[i]] = lis[i];
    }
    reverse(lis.begin(), lis.end());
    vector<long long> dright(n);
    dright[0] = 0;
    curma.clear();
    curma[0] = lis[0];
    for (long long i = 1; i < n; i++) {
        long long prevnum = dright[i-1];
        if (dright[i-1] < 2)    {
            dright[i] = max(dright[i-1] + 1, lis[i-1]-lis[i]);
        } else  {
            if (curma.find(prevnum-1) != curma.end())  {
                if (curma[prevnum-1] - lis[i] <= prevnum)   {
                    dright[i] = prevnum;
                } else  {
                    dright[i] = max(dright[i-1] + 1, lis[i-1]-lis[i]);
                }
            } else  {
                dright[i] = max(dright[i-1] + 1, lis[i-1] - lis[i]);
            }
        }
        curma[dright[i]] = lis[i];
    }
    reverse(lis.begin(), lis.end());
    reverse(dright.begin(), dright.end());
    double ans = LLONG_MAX;
    ans = min(ans, (double)(min(dright[0], dleft[n-1])));
    for (long long i = 0; i < n; i++) {
        //cout << dleft[i] << ' ' << dright[i] << endl;
    }
    for (long long i = 1; i < n; i++)   {
        if ((lis[i]-lis[i-1])/2 < 30000)    {
            //cout << dleft[i-1] + 1 << ' ' << dright[i] + 1 << endl;
        }
        ans = min(ans, max((double)(lis[i]-lis[i-1])/(double)2, (double)(max(dleft[i-1]+1, dright[i]+1))));
        ans = min(ans, (double)max(dleft[i], dright[i]));
        //cout << i << ' ' << ans << endl;
    }
    //cout << "ADAD " << endl;
    //cout << ans << endl;
    cout << fixed << setprecision(1) << ans << endl;
    //cout << ans << endl;
}