#include <bits/stdc++.h>
using namespace std;

int main()  {
    freopen("piepie.out","r",stdin);
    vector<int> lis;
    for (int i = 0; i < 99998; i++) {
        int x;
        cin >> x;
        lis.push_back(x);
    }
    freopen("piepie1.out","r",stdin);
    for (int i = 0; i < 99998; i++) {
        int x;
        cin >> x;
        if (x != lis[i])    {
            cout << i << ' '<< x << ' ' << lis[i] << endl;
        }
    }
}