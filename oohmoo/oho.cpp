#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define ff first
#define ss second
const int MAX_N = 2e5+5;
const ll MOD = 1e9+7;
const ll INF = 1e18;

ll n, d, a, b, l, r;
ll c[MAX_N];

ll ceil(ll a, ll b){
    return (a+b-1)/b;
}

int main(int argc, const char * argv[]){
    freopen("a.in", "r", stdin);
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cin >> n >> d >> a >> b;
    for(int i = 0; i < n; i++) cin >> c[i];
    sort(c, c+n);
    l = n-a, r = n-b-1;
    ll ql = r, qr = r;
    while(ql > l && c[ql-1] == c[r]) ql--;
    while(qr+1 < n && c[qr+1] == c[r]) qr++;
    ll k = 0, p = 0, num = c[r];
    while(true){
        ll numx = qr+1 < n ? ceil((c[qr+1]-num)*(qr-ql+1)-p, r-ql+1) : INF;
        ll numy = ql > l && r != qr ? ((qr-ql+1)*(num-(c[ql-1]+k))+p)/(qr-r) : INF;
        if(k+min(numx, numy) > d) break;
        ll x = min(numx, numy)*(r-ql+1)+p;
        num += x/(qr-ql+1), p = x%(qr-ql+1), k += min(numx, numy);
        while(qr+1 < n && c[qr+1] == num) qr++;
        while(ql > l && c[ql-1]+k == num) ql--;
    }
    ll x = ((d-k)*(r-ql+1)+p)/(qr-ql+1), y = (d-k)*(r-ql+1)+p-x*(qr-ql+1);
    num += ((d-k)*(r-ql+1)+p)/(qr-ql+1), p = y, k = d;
    for(int i = l; i < ql; i++) c[i] += d;
    for(int i = ql; i <= qr; i++) c[i] = qr-i < p ? num+1 : num;
    ll ans = 0;
    for(int i = 0; i < n; i++)
        ans = (ans+(c[i]%MOD)*(c[i]%MOD))%MOD;
    cout << ans << '\n';
    return 0;
}