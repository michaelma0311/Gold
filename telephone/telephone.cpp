#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, k;
struct gra  {
    int curscore;
    int curnum;
    int prevnum;
    int curclass;
    vector<int> curvis;
    gra(int score, int num, int prev, int clazz, std::vector<int> vis)
        : curscore(score), curnum(num), prevnum(prev), curclass(clazz), curvis(vis) {}
};
signed main()  {
    //freopen("a.in", "r", stdin);
    cin >> n >> k;
    vector<int> lis(n);
    map<int, set<int>> ma;
    vector<bool> visited(k);
    set<int> b;
    for (int i = 0; i < k; i++) {
        ma[i] = b;
    }
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        lis[i] = x-1;
        ma[lis[i]].insert(i);
    }
    vector<vector<int>> adj(k);
    vector<vector<int>> matr(k);
    for (int i = 0; i < k; i++) {
        string a;
        cin >> a;
        vector<int> temp(k);
        for (int j = 0; j < k; j++) {
            temp[j] = a[j];
            if (temp[j] == '1')   {
                adj[i].push_back(j);
            }
        }
        matr[i]=temp;
    }
    int star = lis[0];
    int end = lis[n-1];
    if (star == end)    {
        if (matr[star][star] == 1)  {
            cout << n-1 << endl;
            return 0;
        } 
    }
    bool tof = false;
    vector<int> blank(k);
    queue<gra> pq;
    //priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;
    /*int curscore;
    int curnum;
    int prevnum;
    int curclass;
    vector<int> curvis(k);*/
    int ans = INT_MAX;
    pq.push(gra(0, 0, -1, star, blank));
    //cout << star << ' ' << end << endl;
    while (!pq.empty()) {
        gra a = pq.front();
        pq.pop();
        int curscore = a.curscore;
        int prevnum = a.prevnum;
        int curnum = a.curnum;
        int curclass = a.curclass;
        cout << curscore << ' '<< curnum << ' ' << prevnum << ' ' << curclass<< endl;
        vector<int> curvis = a.curvis;
        for (int i : adj[curclass])   {
            //cout << "HI " << endl;
            vector<int> tempvis = curvis;
            //cout << i << endl;
            if (i == curnum)    {
                continue;
            }
            if (curvis[i] == true)  {
                continue;
            }
            set<int> tempcur = ma[i];
            if (tempcur.empty())    {
                continue;
            }
            if (i == end)   {
                ans = min(ans, curscore + n-1-curnum);
                tof = true;
                continue;
            }
            auto it = tempcur.upper_bound(curnum);
            if (it == tempcur.end())    {
                it--;
            }
            if (prevnum != -1)  {
                tempvis[curclass] = true;
            }
            pq.push(gra(curscore + abs((*it) - curnum), (*it), curnum, i, tempvis));
        }
    }
    if (!tof)    {
        cout << -1 << endl;
        return 0;
    } 
    cout << ans << endl;
}