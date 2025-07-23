#include <bits/stdc++.h>
using namespace std;
#define int long long
vector<int> par;
vector<int> rnk;
vector<int> ans;
vector<int> curact;
map<int, vector<int>> leads;
int find(int x) {
    if (par[x] != x) {
        par[x] = find(par[x]);  
    }
    return par[x];
}

void unite(int x, int y, int cur) {
    int curx = find(x);
    int cury = find(y);
    if (curx == cury)   {
        return;
    }
    
    if (rnk[curx] < rnk[cury])  {
        swap(curx, cury);
    }
    //cout << x << ' ' << curx << ' ' << y << ' ' << cury << ' ' << curact[curx] << ' ' << curact[cury] << endl;
    par[cury] = curx;
    
    if (rnk[curx] == rnk[cury]) {
        rnk[curx] += 1;
    }
    if (cur != -1 && (curact[curx] || curact[cury]))    {
        int inact = curact[curx] ? cury : curx;
        //cout << "HI " << inact << endl;
        for (int i : leads[inact])  {
            ans[i] = max(ans[i], cur);
        }
    }
    for (int i : leads[cury])   {
        leads[curx].push_back(i);
    }
    curact[curx] = curact[curx] || curact[cury];
    curact[cury] = curact[curx] || curact[cury];
}
signed main()  {
    //freopen("a.in", "r", stdin);
    //freopen("a.out", "w", stdout);
    int n, q;
    cin >> n >> q;
    par.resize(n);
    rnk.resize(n);
    ans.resize(n);
    curact.resize(n);
    vector<int> act(n);
    fill(act.begin(), act.end(), true);
    vector<pair<char, pair<int,int>>> quers(q);
    vector<pair<int, int>> roads;
    set<int> numsroads;
    for (int i = 0; i < q; i++) {
        char a;
        cin >> a;
        if (a == 'A')   {
            int x, y;
            cin >> x >> y;
            x -= 1;
            y -= 1;
            roads.push_back({x, y});
            quers[i] = {a, {x, y}};
        } else if (a == 'D')    {
            int x;
            cin >> x;
            x -= 1;
            act[x] = false;
            quers[i] = {a, {x, 0}};
        } else  {
            int x;
            cin >> x;
            x -= 1;
            quers[i] = {a, {x, 0}};
            numsroads.insert(x);
        }
    }
    //vector<int> ans(n);
    for (int i = 0; i < n; i++) {
        if (act[i]) {
            curact[i] = true;
        }
    }
    for (int i = 0; i < n; i++) {
        par[i] = i;
        vector<int> blank;
        blank.push_back(i);
        leads[i].push_back(i);
        rnk[i] = 0;
        if (act[i]) {
            ans[i] = q;
        } 
    }
    for (int i = 0; i < roads.size(); i++)  {
        if (numsroads.find(i) == numsroads.end())   {
            int x = roads[i].first;
            int y = roads[i].second;
            //cout << "ADAD " << x << ' ' << y << ' ' << find(x) << ' ' << find(y) << ' ' << act[find(x)] << ' ' << act[find(y)] << endl;
            if (curact[find(x)] == false && curact[find(y)] == false)    {
                unite(x, y, -1);
            } else if (curact[find(x)] == true && curact[find(y)] == false)   {
                unite(x, y, q);
                /*for (int i : leads[y])  {
                    ans[i] = max(ans[i], k);
                }*/
                
            } else if (curact[find(y)] == true && curact[find(x)] == false)   {
                unite(x, y, q);
                /*for (int i : leads[x])  {
                    ans[i] = max(ans[i], k);
                }*/
            } else  {
                unite(x, y, -1);
            }
            
        }
    }
    for (int k = q-1; k >= 0; k--)  {
        char a = quers[k].first;
        if (a == 'R')   {
            int cur = quers[k].second.first;
            int x = roads[cur].first;
            int y = roads[cur].second;
            if (curact[find(x)] == false && curact[find(y)] == false)    {
                unite(x, y, -1);
            } else if (curact[find(x)] == true && curact[find(y)] == false)   {
                unite(x, y, k);
                /*for (int i : leads[y])  {
                    ans[i] = max(ans[i], k);
                }*/
                
            } else if (curact[find(y)] == true && curact[find(x)] == false)   {
                unite(x, y, k);
                /*for (int i : leads[x])  {
                    ans[i] = max(ans[i], k);
                }*/
            } else  {
                unite(x, y, -1);
            }
        } else if (a == 'D')    {
            int x = quers[k].second.first;
            if (!curact[find(x)]) {
                for (int i : leads[find(x)])    {
                    ans[i] = k;
                }
                curact[find(x)] = true;
            }
            
        }
    }
    for (int i = 0; i < n; i++) {
        cout << ans[i] << endl;
    }
}