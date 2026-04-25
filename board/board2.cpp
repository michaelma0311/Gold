#include <bits/stdc++.h>
using namespace std;
#define int long long
vector<int> treelis;
long long query(long long treeind, long long curl, long long curr, long long l, long long r) {
    if (r < curl || curr < l) {
        return 0;
    }
    if (l <= curl && curr <= r) {
        return treelis[treeind];
    }
    long long mid = (curl + curr) / 2;
    long long ls = query(2*treeind+1, curl, mid, l, r);
    long long rs = query(2*treeind+2, mid + 1, curr, l, r);
    return max(ls, rs);
}

void update(long long treeind, long long curl, long long curr, long long ind, long long val) {
    if (curl == curr) {
        treelis[treeind] = max((long long)treelis[treeind], val);
    } else {
        long long mid = (curl + curr) / 2;
        if (ind <= mid) {
            update(2*treeind+1, curl, mid, ind, val);
        } else {
            update(2*treeind+2, mid + 1, curr, ind, val);
        }
        treelis[treeind] = max(treelis[2*treeind+1], treelis[2*treeind+2]);
    }
}
signed main()  {
    freopen("boards.in", "r", stdin);
    freopen("boards.out", "w", stdout);
    int n, p;
    cin >> n >> p;
    set<int> distincty;
    vector<int> yvals;
    vector<array<int,3>> board;
    map<pair<int,int>,pair<int,int>> mainds;
    for (int i = 0; i < p; i++)  {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        if (c > n || d > n)  {
            continue;
        }
        if (distincty.find(b) == distincty.end()) {
            yvals.push_back(b);
            distincty.insert(b);
        }
        if (distincty.find(d) == distincty.end()) {
            yvals.push_back(d);
            distincty.insert(d);
        }
        mainds[{a,b}] = {c,d};
        board.push_back({c, d, 0});
        board.push_back({a, b, 1});
    }
    map<pair<int,int>,int> vals;
    sort(board.begin(), board.end());
    sort(yvals.begin(), yvals.end());
    map<int,int> toinds;
    for (int i = 0; i < yvals.size(); i++)  {
        toinds[yvals[i]] = i;
    }
    int k = yvals.size();
    treelis.resize(4*k);
    for (int i = 0; i < 2*p; i++)  {
        int curx, cury, typ;
        curx = board[i][0];
        cury = board[i][1];
        typ = board[i][2];
        if (typ == 0) { // end value
            //cout << "HJERE " << cury << ' ' << vals[{curx,cury}]<< endl;
            update(0, 0, k-1, toinds[cury], vals[{curx,cury}]);
        } else {
            int ind = lower_bound(yvals.begin(), yvals.end(), cury) - yvals.begin();
            int p = query(0, 0, k-1, 0, ind);
            //cout << "WEGEW " << p << ' ' << mainds[{curx,cury}].first-curx + mainds[{curx,cury}].second-cury << endl;
            vals[mainds[{curx,cury}]] = p + mainds[{curx,cury}].first-curx + mainds[{curx,cury}].second-cury;
        }
    }
    cout << n + n - query(0, 0, k-1, 0, k-1) << endl;
}