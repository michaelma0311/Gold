#include <bits/stdc++.h>
using namespace std;
#define int long long
bool cmp(const pair<int,int>& A, const pair<int,int>& B) {
    return (A.first + A.second) < (B.first + B.second);
}
void solve()    {
    
    int n;
    cin >> n;
    vector<pair<int, int>> lis(n);
    for (int i = 0; i < n; i++) {
        cin >> lis[i].first >> lis[i].second;
    }
    sort(lis.begin(), lis.end(), cmp);
    int cursum = 0;
    priority_queue<int> pq;
    for (int i = 0; i < n; i++) {
        cursum += lis[i].second;
        pq.push(lis[i].second);
        if (cursum > lis[i].first+lis[i].second)   {
            int a = pq.top();
            cursum -= a;
            pq.pop();
        }
    }
    cout << pq.size() << endl;
}

signed main()  {
    //sfreopen("a.in", "r", stdin);
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        solve();
    }
}