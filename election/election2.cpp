#include <bits/stdc++.h>
using namespace std;
int n, q;
vector<int> lis;

bool cmp(const pair<int, int>& a, const pair<int, int>& b) {
    return a.second < b.second;  
}

int main()  {
    cin >> n >> q;
    lis.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> lis[i];
        lis[i] -= 1;
    }
    map<int, int> ma;
    for (int i =0 ; i < n; i++) {
        ma[i] = 0;
    }
    for (int i : lis)   {
        ma[i] += 1;
    }
    for (int _ = 0; _ < q; _++) {
        int x, y;
        cin >> x >>  y;
        x -= 1;
        y -= 1;
        ma[lis[x]] -= 1;
        ma[y] += 1;
        lis[x] = y;
        int curans = 0;
        vector<pair<int, int>> curlis;
        //get maxmimuim can optimize
        int maxnum = 0;
        for (const auto& i : ma) {
            if (i.second == 0)  {
                continue;
            }
            curlis.push_back({i.first, i.second});
            maxnum = max(maxnum, i.second);
        }
        sort(curlis.begin(), curlis.end(), cmp);
        int siz = curlis.size();
        vector<int> minvals(siz);
        
        int temp = INT_MAX;
        vector<int> curnums(siz);
        for (int i = siz-1; i >= 0; i--)    {
            temp = min(temp, curlis[i].first);
            minvals[i] = temp;
            curnums[i] = curlis[i].second;
        }
        for (int i = siz-1; i >= 0; i--)    {
            int a = maxnum - curnums[i];
            int dis = distance(curnums.begin(), lower_bound(curnums.begin(), curnums.end(), a));
            curans = max(curans, abs(minvals[dis]-curlis[i].first));
        }
        cout << curans << endl;
    }
}