#include <bits/stdc++.h>
using namespace std;

map<vector<long long>, long long> ma;
vector<vector<long long>> all;
void generateSubsets(const vector<long long>& vec) {
    long long n = vec.size();
    long long totalSubsets = 1 << n;

    for (long long mask = 1; mask < totalSubsets; ++mask) {
        vector<long long> subset;
        
        for (long long i = 0; i < n; ++i) {
            if (mask & (1 << i)) {
                subset.push_back(vec[i]);
            }
        }
        if (ma.find(subset) == ma.end())    {
            ma[subset] = 0;
            all.push_back(subset);
        }
        ma[subset] += 1;
        
    }
}

signed main()  {
    freopen("cowpatibility.in", "r", stdin);
    freopen("cowpatibility.out", "w", stdout);
    long long n;
    cin >> n;
    vector<vector<long long>> lis(n);
    for (long long i = 0; i < n; i++) {
        vector<long long> temp(5);
        for (long long j = 0; j < 5; j++) {
            cin >> temp[j];
        }
        sort(temp.begin(), temp.end());
        generateSubsets(temp);
    }
    vector<long long> direc = {1, -1, 1, -1, 1};
    long long tot = 0;
    for (auto i : all)  {
        long long num = ma[i];
        if (num == 1)   {
            continue;
        }
        //cout << "ADAD " << i.size() << ' ' << num << endl;
        //cout << endl;
        tot += direc[i.size()-1] * (num * (double)(num-1)/(double)2);
    }
    cout << n * (n-1)/2 - tot << endl;
}