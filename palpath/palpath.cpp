#include <bits/stdc++.h>
using namespace std;

signed main()  {
    freopen("palpath.in", "r", stdin);
	freopen("palpath.out", "w", stdout);
    long long n;
    cin >> n;
    vector<vector<char>> grid(n);
    vector<vector<long long>> prev(n);
    const long long mod = 1e9+7;
    for (long long i = 0; i < n; i++) {
        grid[i].resize(n);
        prev[i].resize(n);
    }
    for (long long i = 0; i < n; i++) {
        string a;
        cin >> a;
        for (long long j = 0; j < n; j++) {
            grid[i][j] = a[j];
        }
    }
    for (long long i = 0; i < n; i++) {
        prev[i][i] = 1;
    }
    for (long long len = 1; len <= n-1; len++) {
        vector<vector<long long>> cur(n);
        for (long long i = 0; i < n; i++) {
            cur[i].resize(n);
        }
        for (long long i = 0; i < n; i++) {
            long long coli = n-i-len-1;
            //cout << "hi " <<len << ' ' << i << ' ' << coli << endl;
            if (coli < 0)   {
                continue;
            }
            for (long long j = i; j < n; j++) {
                long long colj = n-j+len-1;
                
                if (colj >= n)  {
                    continue;
                }
                
                if (grid[i][coli] != grid[j][colj]) {
                    continue;
                }
                //cout << len << ' ' << i << ' ' << coli << ' ' << j << ' ' << colj << endl;
                cur[i][j] = (prev[i][j] + prev[i+1][j-1])%mod + (prev[i+1][j] + prev[i][j-1])%mod;
                cur[i][j] %= mod;
            }
        }
        /*for (long long i = 0; i < n; i++) {
            for (long long j = 0; j < n; j++) {
                cout << cur[i][j] << ' ';
            }
            cout << endl;
        }*/
        prev = cur;
    }
    cout << prev[0][n-1] << endl;
}