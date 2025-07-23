#include <bits/stdc++.h>

using namespace std;

#define int long long

int n, m;
string s;
vector<vector<int>> adj;
map<int, vector<int>> toadd;
int parent[1000005];
int rnk[1000005];
int siz[1000005];
int finda(int x) {
    if (parent[x] != x) {
        parent[x] = finda(parent[x]);  
    }
    return parent[x];
}

void unite(int x, int y) {
    int curx = finda(x);
    int cury = finda(y);

    if (curx != cury) {
        if (rnk[curx] > rnk[cury]) {
            parent[cury] = curx;
            siz[curx] += siz[cury];
        } else if (rnk[curx] < rnk[cury]) {
            parent[curx] = cury;
            siz[cury] += siz[curx];
        } else {
            parent[cury] = curx;
            rnk[curx]++;
            siz[curx] += siz[cury];
        }
    }
}

int getsiz(int x)    {
    return siz[finda(x)];
}
void incsiz(int x) {
    siz[finda(x)] += 1;
}
signed main()  {   
    //freopen("a.in", "r", stdin);
    cin >> n >> m;
    cin >> s;
    vector<int> blank;
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        siz[i] = 0;
        rnk[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        toadd[i] = blank;
    }
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        x -= 1;
        y -= 1;
        if (s[x] == '0' && s[y] == '0') {
            toadd[min(x, y)].push_back(max(x, y));
        } else if (s[x] == '0')   {
            toadd[x].push_back(y);
        } else if (s[y] == '0')   {
            toadd[y].push_back(x);
        } else  {
            unite(x, y);
        }
    }
    //cout << "IE " << endl;
    int ans = 0;
    vector<int> sol(n);
    for (int i = n-1; i >= 0; i--)  {
        int num = getsiz(i);
        int sub = 0;
        sub += (num*(num-1))/2;
        map<int, int> cont;
        cont[finda(i)] = 1;
        if (s[i] == '1')  {
            ans -= sub;
            incsiz(i);
            ans += (num*(num+1))/2;
        } else  {
            for (int j : toadd[i])  {
                int a = getsiz(j);
                int par = finda(j);
                if (cont.find(par) == cont.end())   {
                    sub += a*(a-1)/2;
                    cont[par] = 1;
                }
                unite(i, j);
            }
            ans -= sub;
            incsiz(i);
            int curs = getsiz(i);
            ans += (curs*(curs-1))/2;
        }
        sol[i] = ans;
    }
    for (int i : sol)   {
        cout << i << endl;
    }

}