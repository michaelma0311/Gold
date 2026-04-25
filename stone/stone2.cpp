#include <bits/stdc++.h>

using namespace std;

#define int long long

signed main()  {
    int n;
    cin >> n;
    vector<int> lis(n);
    for (int i = 0; i < n; i++)  {
        cin >> lis[i];
    }
    if (n == 1)  {
        cout << (lis[0]+1)  /2 << endl;
    } else  {
        if (lis[0] == lis[1])  {
            cout << 0 << endl;
        } else  {
            cout << max(lis[0], lis[1]) - max(min(lis[0], lis[1]),((max(lis[0], lis[1])) /2 ))<< endl;
        }
    }
}