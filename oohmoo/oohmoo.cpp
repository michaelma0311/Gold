#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, d;
int a, b;
vector<int> lis;
vector<int> top;
const int mod = 1e9+7;
int c = 0;
bool check(int cur) {
    int am = 0;
    for (int i = 0; i < a; i++) {
        am += (int)min(d, max((int)0, ((int)cur)-top[i]));
    }
    c = (((a-b)*d)) - am;
    //cout << am << ' ' <<  (((a-b) * d))<< endl;
    return am <= (((a-b) * d));
}

signed main()  {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); 
    //freopen("a.in", "r", stdin);
    cin >> n >> d;
    cin >> a >> b;
    lis.resize(n);

    for (int i= 0; i < n; i++)  {
        cin >> lis[i];
    }
    sort(lis.begin(), lis.end());
    for (int i = n-1; i >= n-a; i--)    {
        top.push_back((int)lis[i]);
    }
    reverse(top.begin(), top.end());
    vector<int> org = top;
    int lo = 0;
    int hi = 1e14;
    int ans = 0;
    int p = 0;
    while (lo <= hi)    {
        int mid = (lo+hi)/2;
        //cout << lo << ' ' << hi << ' ' << mid << endl;
        if (check(mid)) {
            //cout << "BFUWEOBG " << endl;
            ans = mid;
            lo = mid+1;
            p = c;
        } else  {
            //cout << "GUOWEB " << endl;
            hi = mid-1;
        }
        //cout << lo << ' ' << hi << ' ' << mid << endl;
    }
    //cout << ans << ' ' << p << endl;
    vector<bool> valid(a);
    fill(valid.begin(), valid.end(), false);
    for (int i = 0; i < a; i++) {
        if (ans - top[i] >= d)  {
            top[i] += d;
            valid[i] = true;
        } else  {
            if (top[i] < ans)   {
                top[i] = ans;
            }
        }
    }
    while (p != 0)  {
        
        for (int i = 0; i < a; i++) {
            if (valid[i])   {
                continue;
            }
            if (p == (int)0) {
                break;
            }
            p -= 1;
            top[i] += 1;
            if (top[i] == org[i] + d)   {
                valid[i] = true;
            }
        }
    }
    int fin = 0;
    for (int i = 0; i < n-a; i++)   {
        fin += lis[i] * lis[i];
        fin %= mod;
    }
    for (int i : top)   {
        fin += i * i;
        fin %= mod;
    }
    cout << fin << endl;

}