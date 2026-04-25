#include <bits/stdc++.h>
using namespace std;

#define int long long
vector<vector<int>> adj;
vector<int> labels;
vector<int> siz;
vector<int> sum;
vector<int> dp;
vector<int> dp1;
int madep = 0;
vector<int> depth;
void dfs(int cur, int prev, int cnt) {
    if (adj[cur].size() == 1 && prev != -1)   {
        depth[cur] = 0;
    }
    madep = max(madep, cnt);
    siz[cur] = 1;
    sum[cur] = labels[cur];
    for (int i : adj[cur])  {
        if (i == prev)  {
            continue;
        }
        dfs(i, cur, cnt+1);
        siz[cur] += siz[i];
        sum[cur] += sum[i];
        depth[cur] = max(depth[cur], depth[i]+1);
    }
}

void dfs1(int cur, int prev, int cnt)    {
    //cout << "CURPEV " << cur << ' ' << prev << endl;
    for (int i : adj[cur])  {
        if (i == prev)  {
            continue;
        }
        dfs1(i, cur, cnt+1);
    }
    vector<pair<pair<int,int>,int>> temp;
    for (int i : adj[cur])  {
        if (i == prev)  {
            continue;
        }
        //cout << "INSHER " << cur << ' ' << i<< ' ' << sum[i] << ' ' << siz[i] << endl;
        temp.push_back({{sum[i], siz[i]}, i});
        dp[cur] += dp[i] + sum[i];
    }
    sort(temp.begin(), temp.end(), [](const pair<pair<int,int>,int>& a, const pair<pair<int,int>,int>& b) {
        return a.first.first * b.first.second >b.first.first * a.first.second;});
    int alr = 0;
    int p = temp.size();
    vector<int> prefsum(p);
    if (p != 0)  {
        //cout << "WGEWG " <<temp.size()<< endl;
        prefsum[p-1] = temp[p-1].first.first;
        //cout << "A" << endl;
        for (int j = temp.size()-2; j >= 0; j--)    {
            prefsum[j] = prefsum[j+1] + temp[j].first.first; 
        }
        //cout << "HI " << endl;
    }
    for (auto i : temp) {
        dp[cur] += 2 * i.first.first * alr;
        alr += i.first.second;
    }
    int ma = -LLONG_MAX;
    if (p == 0 && cnt == madep)   {
        dp1[cur] = dp[cur];
        return;
    }
    int curalr = 0;
    for (int i = 0; i < p; i++) {
        int curind = temp[i].second;
        //cout << curind << ' ' << depth[curind] << ' ' << cnt << endl;
        if (depth[curind] + cnt+1 != madep)    {
            curalr += temp[i].first.second;
            continue;
        }
        //cout << cur << ' ' << temp[i].second << ' ' << prefsum[i] << ' ' << temp[i].first.first << ' ' << temp[i].first.second << ' ' << dp[temp[i].second] << ' ' << dp1[temp[i].second] << endl;
        ma = max(ma, 2*(prefsum[i]-temp[i].first.first)*temp[i].first.second + 2*curalr*temp[i].first.first - 2 * (alr-temp[i].first.second)*temp[i].first.first + dp[temp[i].second] - dp1[temp[i].second]);
        //cout << "ma " << ma << endl; 
        curalr += temp[i].first.second;
    }
    if (ma == -LLONG_MAX)   {
        dp1[cur] = LLONG_MAX;
        return;
    }
    dp1[cur] = dp[cur] - ma;

}

signed main()   {
    //freopen("test.in", "r", stdin);
    int n, t;
    cin >> n >> t;
    adj.resize(n);
    labels.resize(n);
    siz.resize(n);
    sum.resize(n);
    depth.resize(n);
    dp.resize(n);
    dp1.resize(n);
    fill(dp1.begin(), dp1.end(), LLONG_MAX);
    for (int i = 1; i < n; i++)   {
        int x, y;
        cin >> x >> y;
        x -= 1;
        adj[x].push_back(i);
        adj[i].push_back(x);
        labels[i] = y;
    }
    dfs(0, -1, 0);
    //cout << "GQWEG" << endl;
    dfs1(0, -1, 0);
    if (t == 0) {
        cout <<(n-1)*2 << ' ' <<  dp[0] << endl;
    } else  {
        cout <<(n-1)*2-madep << ' ' <<  dp1[0] << endl;
    }
    
}