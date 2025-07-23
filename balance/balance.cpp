#include <bits/stdc++.h>

using namespace std;
#define int long long
int n;
vector<int> lis;
int am1 = 0;
int inve(int l, int r)  {
    int num0 = 0;
    int tot = 0;
    for (int i = r-1; i >= l; i--) {
        if (lis[i] == 0)    {
            num0 += 1;
        } else  {
            tot += num0;
        }
    }
    return tot;
}
signed main()  {
    freopen("balance.in","r",stdin);
	freopen("balance.out","w",stdout);
    cin >> n;
    lis.resize(2*n);
    for (int i = 0; i < 2*n; i++) {
        cin >> lis[i];
        if (lis[i] == 1)    {
            am1 += 1;
        }
    }
    int numchange = n-am1;
    int dif = inve(0, n) - inve(n, 2*n);
    int best = abs(dif);
    //cout << inve(0, n) << ' ' << inve(n, 2*n) << endl;
    int lef = n-1;
    int rig = n;
    
    while (lef >= 0)    {
        if (lis[lef] == 1) {
            break;
        }
        lef -= 1;
    }
    while (rig < 2*n)   {
        if (lis[rig] == 0)  {
            break;
        }
        rig += 1;
    }
    int cur = 0;
    //cout << dif << endl;
    while (lef >= 0 && rig < 2*n)   { //push 1 from left to right 
        //if moving 1 right, decrease by 1
        //switching from 1 0 -> 0 1 = dif - numchange
        int half1shift = (n-1) - lef;
        int half2shift = rig - n;
        cur += half1shift + half2shift + 1; 
        dif -= half1shift;
        dif += half2shift;
        dif -= numchange;
       // cout << cur << ' ' << half1shift << ' ' << half2shift << ' ' << dif << endl;
        best = min(best, cur + abs(dif));
        //cout << "B " << best << endl;
        while (lef >= 0)    {
            lef -= 1;
            if (lis[lef] == 1) {
                break;
            }
        }
        while (rig < 2*n)   {
            rig += 1;
            if (lis[rig] == 0)  {
                break;
            }
        }
    }
    //cout << best << endl;
    lef = n-1;
    rig = n;
    while (lef >= 0)    {
        if (lis[lef] == 0)  {
            break;
        }
        lef -= 1;
    }
    while (rig < 2*n)   {
        if (lis[rig] == 1)  {
            break;
        }
        rig += 1;
    }
    cur = 0;
    dif = inve(0, n) - inve(n, 2*n);
    //cout << dif << endl;
    while (lef >= 0 && rig < 2*n)   { //push 1 from right to left
        //if moving 1 left, increase by 1;
        //switching from 0 1 -> 1 0 = dif + numchange;
        int half1shift = (n-1) - lef;
        int half2shift = rig-n;
        cur += half1shift + half2shift + 1; 
        dif += half1shift;
        dif -= half2shift;
        dif += numchange;
        //cout << "HI " << cur << ' ' << half1shift << ' ' << half2shift << ' ' << dif << endl;
        best = min(best, cur + abs(dif));
        //cout << "A " << best << endl;
        while (lef >= 0)    {
            lef -= 1;
            if (lis[lef] == 0) {
                break;
            }
        }
        while (rig < 2*n)   {
            rig += 1;
            if (lis[rig] == 1)  {
                break;
            }
        }
    }
    cout << best << endl;
}