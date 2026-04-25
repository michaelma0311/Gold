#include <bits/stdc++.h>
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
using namespace std;
#define int long long

int n;
vector<int> num;
vector<int> val;
inline int findm(int a, int b, int c)    {
    int mina = min(a, min(b,c));
    int maxa = max(a, max(b,c));
    return a+b+c-mina-maxa;
}
vector<vector<int>> dp;
vector<vector<int>> cost;
inline int calc(int m) {
    cost.resize(n);
    dp.resize(n);
    for (int i = 0; i < n; i++) {
        cost[i].resize(3);
        dp[i].resize(3);
        fill(dp[i].begin(), dp[i].end(), LLONG_MAX);
        if (num[i] == m)    {
            cost[i][1] = 0;
            cost[i][0] = val[i];
            cost[i][2] = val[i];
        } else if (num[i] > m) {
            cost[i][0] = val[i];
            cost[i][1] = val[i];
            cost[i][2] = 0;
        } else  {
            cost[i][0] = 0;
            cost[i][1] = val[i];
            cost[i][2] = val[i];
        }
    }
    for (int i = n-1; i >= 0; i--)  {
        if (i*2+2 >= n) {
            dp[i][0] = cost[i][0];
            dp[i][1] = cost[i][1];
            dp[i][2] = cost[i][2];
            continue;
        }
        for (int a = 0; a < 3; a++) {
            for (int b = 0; b < 3; b++) {
                for (int c = 0; c < 3; c++) {
                    int med = findm(a, b, c);
                    dp[i][med] = min(dp[i][med], dp[i*2+1][a] + dp[i*2+2][b] + cost[i][c]);
                }
            }
        }
    }
    return dp[0][1];
}
inline void changecost(int cur, int m) {
    if (num[cur] == m)  {
        cost[cur][0] = val[cur];
        cost[cur][1] = 0;
        cost[cur][2] = val[cur];
    } else if (num[cur] < m)    {
        cost[cur][0] = 0;
        cost[cur][1] = val[cur];
        cost[cur][2] = val[cur];
    } else  {
        cost[cur][0] = val[cur];
        cost[cur][1] = val[cur];
        cost[cur][2] = 0;
    }
}

inline void moddfs(int cur, int m) {
    if (cur*2+2 >= n)   {
        dp[cur][0] = cost[cur][0];
        dp[cur][1] = cost[cur][1];
        dp[cur][2] = cost[cur][2];
    } else  {
        dp[cur][0] = LLONG_MAX;
        dp[cur][1] = LLONG_MAX;
        dp[cur][2] = LLONG_MAX;
        for (int a =0; a < 3; a++)  {
            for (int b = 0; b < 3; b++) {
                for (int c= 0; c < 3; c++)  {
                    int med = findm(a, b, c);
                    dp[cur][med] = min(dp[cur][med], dp[cur*2+1][a] + dp[cur*2+2][b] + cost[cur][c]);
                }
            }
        }
    }
    if (cur == 0)    {
        return;
    } else  {
        if (cur%2 == 0) {
            moddfs((cur-2)/2, m);
        } else  {
            moddfs((cur-1)/2, m);
        }
    }
}

signed main()  {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);   
    cin >> n;
    num.resize(n);
    val.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> num[i] >> val[i];
    }
    int q;
    cin >> q;
    vector<pair<int,int>> quers;
    for (int i = 0; i < q; i++) {
        int x;
        cin >> x;
        quers.push_back({x, i});
    }
    sort(quers.begin(), quers.end());
    vector<int> ans(q);
    vector<pair<int,int>> curvals(n);
    for (int i = 0; i < n; i++) {
        curvals[i] = {num[i], i};
    }
    sort(curvals.begin(), curvals.end());
    int ind = 0;
    while (ind < n && curvals[ind].first <= quers[0].first) {
        //cout << "WUOGBUOEBGWBEUGB " << curvals[ind].first << ' ' << quers[0].first << endl;
        ind += 1;
    }
    ans[quers[0].second] = calc(quers[0].first);
    //cout << "HI " << quers[0].first << ' ' << ans[quers[0].second] << endl;
    ///cout << "IND " << ind << endl;
    for (int i = 1; i < q; i++) {
        int curq = quers[i].first;
        int indq = quers[i].second;
        int templef = ind;
        int temprig = ind;
        if (curq == quers[i-1].first)   {
            ans[indq] = dp[0][1];
            continue;
        }
        while (templef-1 >= 0 && curvals[templef-1].first == quers[i-1].first)    {
            templef -= 1;
        }
        while (temprig < n && curvals[temprig].first <= curq) {
            temprig += 1;
        }
        //cout << "inside " << curq << ' ' << indq << ' ' << templef << ' ' << temprig << endl;
        set<int> changed;
        for (int p = templef; p < temprig; p++) {
            changecost(curvals[p].second, curq);
            changed.insert(-(curvals[p].second));
        }
        //cout << "WGEWEG " << endl;
        for (const auto& i : changed)   {
            moddfs(-i, curq);
        }
        ans[indq] = dp[0][1];
        ind = temprig;
    }
    for (int i = 0; i < q; i++) {
        cout << ans[i] << "\n";
    }

}