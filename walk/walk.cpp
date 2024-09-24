#include <bits/stdc++.h>

using namespace std;
int main()  {
    freopen("walk.in","r",stdin);
	freopen("walk.out","w",stdout);
    long long n, k;
    cin >> n >> k;
    cout << (long long)2019201997 - ((long long)48*n) - ((long long)84*(k-1)) << endl;
}