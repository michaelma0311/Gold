#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main()   {
    int n, t;
    cin >> n >> t;
    vector<pair<int,int>> inside;
    vector<int> sol;
    int ox, oy;
    cin >> ox >> oy;
    sol.push_back((sqrt(ox*ox+oy*oy)));
    vector<array<int,3>> lis(n);
    for (int i = 0; i < n; i++) {
        cin >> lis[i][0] >> lis[i][1] >> lis[i][2];
    }
    int ind = 0;
    for (int cur = 1; cur < t; cur++)   {
        while (ind < n && lis[ind][0] == cur)  {
            //cout << ind << endl;
            inside.push_back({lis[ind][1], lis[ind][2]});
            ind += 1;
        }
        if (inside.empty()) {
            sol.push_back(sqrt(ox*ox+oy*oy));
            continue;
        }
        int ans =INT_MAX;
        sort(inside.begin(), inside.end());
        /*for (auto i : inside)   {
            cout << i.first << ' ' << i.second << endl;
        }*/
        int p = lower_bound(inside.begin(), inside.end(), make_pair(ox,(int)0)) - inside.begin();
        int a = inside.size();
        vector<int> curmi;
        vector<int> curma;
        curmi.push_back(0);
        curma.push_back(INT_MAX);
        for (int i = 0; i < a; i++)  {
            curmi.push_back(max(curmi.back(), inside[i].second));
        }
        for (int i = a-1; i >=0; i--)   {
            curma.push_back(min(curma.back(), inside[i].second));
        }
        reverse(curma.begin(), curma.end());
        //for (int i = 0; i <= a; i++)    {
        //    cout << "OIENGIW " << curmi[i] << ' ' << curma[i] << endl;
        //}
        //cout << "WEGE " << p << endl;
        int acurmi = curmi[p];
        int acurma = curma[p];
        if (acurmi <= acurma) {
            if (acurmi <= oy && oy <= acurma)   {
                ans = sqrt(ox*ox+oy*oy);
            } else if (acurmi > oy)   {
                ans = sqrt(acurmi*acurmi+ox*ox) + acurmi-oy;
            } else  {
                ans = sqrt(acurma*acurma+ox*ox) + oy-acurma;
            }
        }
        //cout << "BEFANS "<<ans << endl;
        for (int i = 0; i < a; i++)    {
            acurmi = curmi[i];
            acurma = curma[i+1];
            //cout << i << ' ' << acurmi << ' ' << acurma << endl;
            if (acurmi <= acurma) {
                //cout << "OINSDE " << acurmi << ' ' << oy << ' ' << acurma << ' ' << ox << ' ' << inside[i].first << endl;
                if (acurmi <= oy && oy <= acurma)   {
                    ans = min(ans, (int)sqrt(inside[i].first*inside[i].first+oy*oy) + abs(ox-inside[i].first));
                } else if (acurmi > oy)   {
                    ans = min(ans, (int)sqrt(acurmi*acurmi+inside[i].first*inside[i].first) + acurmi-oy + abs(ox-inside[i].first));
                } else  {
                    //cout << "C" << endl;
                    ans = min(ans,(int)sqrt(acurma*acurma+inside[i].first*inside[i].first) + oy-acurma + abs(ox-inside[i].first));
                }
            }
            //cout << "ANS " << ans << endl;
        }
        sol.push_back(ans);
    }
    for (int i : sol)   {
        cout << i << endl;
    }
}