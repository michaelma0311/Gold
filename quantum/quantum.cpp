#include <bits/stdc++.h>
using namespace std;
vector<int> p;
vector<int> s;
vector<int> adjleft;
vector<int> adjright;
double calc(int x, int y) {
    //cout << p[x] << ' ' << p[y] << ' ' << s[x] << ' ' << s[y] << endl;
    return (double)abs(p[x]-p[y])/(double)abs(s[x]+s[y]);
}
void solve()    {
    int n;
    cin >> n;
    p.clear();
    s.clear();
    adjleft.clear();
    adjright.clear();
    p.resize(n);
    s.resize(n);
    adjleft.resize(n);
    adjright.resize(n);
    fill(adjleft.begin(), adjleft.end(), -1);
    fill(adjright.begin(), adjright.end(), n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        adjleft[i] = i-1;
        adjright[i] = i+1;
    }
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }
    priority_queue<pair<double, pair<int, int>>> q;
    vector<int> ans(n);
    for (int i = 0; i < n-1; i++) {
        if (i%2 == 0)   {
            q.push(make_pair(-calc(i, i+1), make_pair(i, 1)));
        } else  {
            q.push(make_pair(-calc(i, i+1), make_pair(i, -1)));
        }
    }
    vector<bool> visited(n);
    while (q.empty() == false)  {
        double cur = -q.top().first;
        int ind = q.top().second.first;
        int direc = q.top().second.second;
        q.pop();
        cout << "indies " << ind << endl;
        if (visited[ind] || visited[ind+1]) {
            continue;
        }
        int observ;
        if (direc == -1)    {
            observ = ceil(cur) * 2;
        }else    {
            observ = ceil(cur)*2 - 1;
        }
        ans[ind] = observ;
        cout << cur << ' ' << ind << ' ' << direc << ' ' << observ << endl;
    
        ans[ind+1] = observ;
        ans[ind] = observ;
        if (ind+1 < n && adjleft[ind] >= 0 && adjright[ind+1] < n)  {
            adjright[adjleft[ind]] = adjright[ind+1];
            adjleft[adjright[ind+1]] = adjleft[ind];
            visited[ind] = true;
            visited[ind+1] = true;
            cout << adjright[adjleft[ind]] << ' ' << adjleft[adjright[ind+1]] << endl;
            if (adjleft[ind]%2 == 0)    {
                q.push(make_pair(-calc(adjleft[ind], adjright[ind+1]), make_pair(adjleft[ind], 1)));
            } else  {
                q.push(make_pair(-calc(adjleft[ind], adjright[ind+1]), make_pair(adjleft[ind], -1)));
            }
        }
        
    }
    for (int i : ans)   {
        cout << i << ' ';
    }
    cout << endl;
}

int main()  {
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        solve();
    }
}