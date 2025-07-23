#include <bits/stdc++.h>

using namespace std;

bool cmp(const pair<long long, long long>& a, const pair<long long, long long>& b) {
    return a.second > b.second; 
}

signed main()  {
    //freopen("trapped.in","r",stdin);
	//freopen("trapped.out","w",stdout);
    long long n;
    cin >> n;
    vector<pair<long long, long long>> lis(n);
    for (long long i = 0; i < n; i++) {
        cin >> lis[i].second >> lis[i].first;
    }
    sort(lis.begin(), lis.end(), cmp);
    set<pair<long long, long long>> cursiz;
    cursiz.insert(lis[0]);
    cursiz.insert(lis[1]);
    map<long long, bool> temp;
    auto fir = cursiz.begin();
    auto sec = next(fir, 1);
    long long difpos = (*sec).first - (*fir).first;
    //cout << difpos << ' ' << lis[0].second << endl;
    if (difpos > min(lis[1].second, lis[0].second)) {
        temp[lis[0].first] = true;
    } else  {
        //cout <<" HI" << endl;
        temp[lis[0].first] = false;
    }
    for (long long i = 2; i < n; i++) {
        pair<long long, long long> cur = lis[i];
        auto it = cursiz.lower_bound(cur);
        if (it == cursiz.begin())   {
            long long posdif = (*it).first - cur.first;
            if (posdif > cur.second)    {
                temp[cur.first] = true;
            } else  {
                temp[cur.second] = false;
            }
        } else if (it == cursiz.end())  {
            it = next(it, -1);
            long long posdif = cur.first - (*it).first;
            if (posdif > cur.second) {
                temp[(*it).first] = true;
            } else  {
                temp[(*it).second] = false;
            }
        } else  {
            it--;
            if (temp[(*it).first] == false)   {
                //cout <<" HI" << endl;
                temp[cur.first] = false;

            } else  {
                long long posdif = cur.first - (*it).first;
                if (posdif > (*it).second)    {
                    if (it == cursiz.begin())   {
                        temp[(*it).first] = true;
                    } else  {
                        auto tcur = next(it, -1);
                        if (temp[(*tcur).first] == true)  {
                            temp[(*it).first] = true;
                        } else  {
                            temp[(*it).first] = false;
                        }
                    }
                } else  {
                    temp[(*it).first] = false;
                }
                it++;
                posdif = (*it).first - cur.first;
                if (posdif > (*it).second)    {
                    if (next(it,1) == cursiz.end())  {
                        temp[cur.first] = true;
                    } else  {
                        if (temp[(*it).first] == true)    {
                            temp[cur.first] = true;
                        } else  {
                            temp[cur.first] = false;
                        }
                    }
                }
            }
        }
        cursiz.insert(cur);
    }
    sort(lis.begin(), lis.end());
    long long ans = 0;
    for (long long i = 0; i < n-1; i++)   {
        if (temp[lis[i].first] == false)  {
            cout << lis[i].first << endl;
            ans += lis[i+1].first - lis[i].first;
        }
    }
    cout << ans << endl;
}