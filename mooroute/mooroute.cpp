#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e6+5;

int fac[MAXN + 1];
int inv[MAXN + 1];
const int mod = 1e9+7;

int exp(int x, int n, int m) {
	x %= m;  
	int res = 1;
	while (n > 0) {
		if (n % 2 == 1) { res = res * x % m; }
		x = x * x % m;
		n /= 2;
	}
	return res;
}

void factorial(int p) {
	fac[0] = 1;
	for (int i = 1; i <= MAXN; i++) { fac[i] = fac[i - 1] * i % p; }
}


void inverses(int p) {
	inv[MAXN] = exp(fac[MAXN], p - 2, p);
	for (int i = MAXN; i >= 1; i--) { inv[i - 1] = inv[i] * i % p; }
}

int choose(int n, int r, int p) {
	int cur = 1;
    return fac[n] * inv[r]%mod * inv[n-r] % p;
}

signed main()  {
    int n;
    cin >> n;
    factorial(mod);
    inverses(mod);
    vector<int> lis(n);
    for (int i = 0; i < n; i++) {
        cin >> lis[i];
        lis[i] /= 2;
    }
    int ans = 1;
    for (int i =0 ; i < n-1; i++)   {
        if (lis[i] > lis[i+1])  {
            ans *= choose(lis[i], lis[i+1], mod);
            ans %= mod;
        } else  {
            ans *= choose(lis[i+1]-1, lis[i]-1, mod);
            ans %= mod;
        }
    }
    cout << ans << endl;
}