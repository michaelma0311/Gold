#include <bits/stdc++.h>

using namespace std;
bool cmp(const pair<int, int>& a, const pair<int, int>& b) {
    return a.second < b.second || (a.second == b.second && a.first < b.first);
}
int n;
int ans;
void solve(vector<pair<int, int>> lis, int p) {
    for (int i = 0; i < n; i++) {
        vector<int> betw;
        set<int> vis;
        for (int j = i+1; j < n; j++)   {
            sort(betw.begin(), betw.end());
            int x1 = lis[i].first;
            int x2 = lis[j].first;
            int y1 = lis[i].second;
            int y2 = lis[j].second;
            int maxy = max(y1, y2);
            int miny = min(y1, y2);
            if (abs(x1-x2) < abs(y2-y1))    {
                if (vis.find(y2) == vis.end())  {
                    vis.insert(y2);
                    betw.push_back(y2);
                }
                continue;
            }
            cout << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2 << ' ' << ans << endl;
            int curbtw = abs(x2-x1);
            int mincls = distance(betw.begin(), upper_bound(betw.begin(), betw.end(), miny));
            int maxcls = distance(betw.begin(), lower_bound(betw.begin(), betw.end(), maxy));
            int siz = betw.size();
            int tempcls = maxcls;
            cout << "ADA D " << betw.size() << endl;
            if (maxcls == siz || mincls == siz || (betw[maxcls] - betw[mincls] > curbtw))   {
                ans += 1;
            }
            while (tempcls < siz)    {
                if (tempcls == siz-1)    {
                    if ((betw[tempcls]-miny) <= curbtw)   {
                        if ((betw[tempcls]-miny) == curbtw && p == 1) {
                            ans += 1;
                        } else if ((betw[tempcls]-miny) < curbtw)   {
                            ans += 1;
                        }
                    }
                } else  {
                    if ((betw[tempcls] - betw[mincls]) > curbtw)    {
                        if ((betw[tempcls]-miny) <= curbtw)   {
                            if ((betw[tempcls]-miny) == curbtw && p == 1) {
                                ans += 1;
                            } else if ((betw[tempcls]-miny) < curbtw)   {
                                ans += 1;
                            }
                        }
                    }
                }
                tempcls += 1;
            }
            tempcls = mincls;
            while (tempcls >= 0 && maxcls < siz) {
                if (tempcls == 0)   {
                    if (maxy - betw[tempcls] <= curbtw) {
                        if ((maxy - betw[tempcls]) == curbtw && p == 1) {
                            ans += 1;
                        } else if ((maxy - betw[tempcls]) < curbtw) {
                            ans += 1;
                        }
                    }
                } else  {
                    if (betw[maxcls] - betw[tempcls-1] > curbtw)   {
                        if ((maxy - betw[tempcls]) <= curbtw) {
                            if ((maxy - betw[tempcls]) == curbtw && p == 1) {
                                ans += 1;
                            } else if ((maxy - betw[tempcls]) < curbtw) {
                                ans += 1;
                            }
                        }
                    }
                }
                tempcls -= 1;
            }
            cout << "A" << endl;
            while (maxcls < siz)  {
                int tempcls = mincls;
                while (tempcls >= 0) {
                    if (betw[maxcls] - betw[tempcls] > curbtw)    {
                        break;
                    } 

                    if (tempcls == 0)   {
                        cout << "HI" << endl;
                        if (betw[maxcls] - betw[tempcls] == curbtw) {
                            if (p == 1) {
                                ans += 1;
                            }
                        } else  {
                            ans += 1;
                        }
                    } else if (maxcls == siz-1)   {
                        if (betw[maxcls] - betw[tempcls] == curbtw) {
                            if (p == 1) {
                                ans += 1;
                            }
                        } else  {
                            ans += 1;
                        }
                    } else  {
                        if (betw[maxcls + 1] - betw[tempcls - 1] > curbtw)    {
                            if (betw[maxcls] - betw[tempcls] == curbtw) {
                                if (p == 1) {
                                    ans += 1;
                                }
                            } else  {
                                ans += 1;
                            }
                        }
                    }
                    tempcls -= 1;
                }
                maxcls += 1;
            }
            if (vis.find(y2) == vis.end())  {
                vis.insert(y2);
                betw.push_back(y2);
            }
        }
    }
}
int main()  {
    cin >> n;
    vector<pair<int, int>> lis(n);
    vector<pair<int, int>> inv(n);
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        lis[i] = {x, y};
        inv[i] = {y, x};
    }
    sort(lis.begin(), lis.end());
    sort(inv.begin(), inv.end());
    ans = n;
    //cout << "IWUEBG A " << ans << endl;
    solve(lis, 1);
    cout << "end " << ans  << endl;
    solve(inv, -1);
    cout << ans+1 << endl;
    
}