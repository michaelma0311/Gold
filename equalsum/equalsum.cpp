#include <bits/stdc++.h>
using namespace std;

vector<int> calc(vector<int> lis, int cur)  {
    vector<int> temp = lis;
    for (int i = 0; i < lis.size(); i++) {
        temp.push_back(lis[i] + cur);
    }
    temp.push_back(cur);
    sort(temp.begin(), temp.end());
    return temp;
}

int main()  {
    int n;
    cin >> n;
    vector<int> lis(n);
    for (int i = 0; i < n; i++) {
        cin >> lis[i];
    }
    vector<vector<int>> pref;
    vector<int> prev;
    prev.push_back(lis[0]);
    pref.push_back(prev);
    for (int i = 1; i < n; i++) {
        vector<int> cur = calc(prev, lis[i]);
        pref.push_back(cur);
        prev = cur;
    }
    vector<vector<int>> suff;
    prev.clear();
    prev.push_back(lis[n-1]);
    suff.push_back(prev);
    for (int i = n-2; i >= 0; i--)  {
        vector<int> cur = calc(prev, lis[i]);
        suff.push_back(cur);
        prev = cur;
    }
    vector<int> prefsum(n+1);
    pref[0] = 0;
    for (int i = 0; i < n; i++) {
        prefsum[i+1] = prefsum[i] + lis[i];
    }
    vector<int> ans(n);
    for (int i = 0; i < n; i++) {
        int curans = INT_MAX;
        for (int j = i; j >= 0; j--)  {
            for (int k = i; k < n; k++) {
                int curtot = prefsum[k+1] - prefsum[j];
                auto lit = lower_bound(pref[i].begin())
            }
        }
    }
}