#include <bits/stdc++.h>
using namespace std;
#define int long long   
int n;
vector<int> bitlis;
 
void update(int i, int ad) {
    while(i <= n) {
        bitlis[i] += ad;
        i += i & -i;
    }
}
 
int query(int i) {
    int sum = 0;
    while(i > 0) {
        sum += bitlis[i];
        i -= i & -i;
    }
    return sum;
}
signed main()  {
    freopen("haircut.in", "r", stdin);
    freopen("haircut.out", "w", stdout);
    cin >> n;
    vector<int> lis(n+1);
    bitlis.resize(n+1);
    int ans = 0;
    vector<int> sol;
    map<int,vector<int>> nums;
    vector<int> bnk;
    for (int i = 1; i <= n; i++) {
        cin >> lis[i];
        if (nums.find(lis[i]) == nums.end())    {
            nums[lis[i]] = bnk;
        }
        nums[lis[i]].push_back(i);
    }
    vector<int> can(n+1);
    for (const auto& i : nums)  {
        for (int j : i.second)  {
            int p = query(n)-query(j);
            can[j] = p;
            ans += p;
        }
        for (int j : i.second)  {
            update(j, 1);
        }
    }
    if (nums.find(n) != nums.end()) {
        for (int j : nums[n])   {
            update(j, -1);
        }
    }
    for (int j = n-1; j >= 0; j--)  {
        if (nums.find(j) == nums.end()) {
            sol.push_back(ans);
            continue;
        }
        for (int i : nums[j])   {
            ans -= i-query(i);
        }
        for (int i : nums[j])   {
            update(i, -1);
        }
        sol.push_back(ans);
    }
    for (int i = n-1; i >= 0; i--)  {
        cout << sol[i] << endl;
    }

}