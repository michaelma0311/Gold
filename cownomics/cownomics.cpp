#include <bits/stdc++.h>

using namespace std;
#define int long long
const int MOD = 1e9 + 7; 
const int BASE = 31;  
void hasha(vector<int>& a, const string& s) {
    int hashValue = 0;
    int power = 1; 
    int i = 0;
    for (char c : s) {
        hashValue = (hashValue + ((c - 'A') + 1) * power) % MOD; 
        power = (power * BASE) % MOD; 
        //cout << "WEGOWEBG " << hashValue << "\n";
        a[i] = hashValue;
        i += 1;
    }
}
signed main()  {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);   
    freopen("cownomics.in", "r", stdin);
    freopen("cownomics.out", "w", stdout);
    
    int n, m;
    cin >> n >> m;
    vector<vector<int>> spotty(n);
    for (int i = 0; i < n; i++) {
        spotty[i].resize(m);
        string s;
        cin >> s;
        hasha(spotty[i], s);
    }
    vector<vector<int>> plain(n);
    for (int i = 0; i < n; i++) {
        plain[i].resize(m);
        string s;
        cin >> s;
        hasha(plain[i], s);
    }
    int ans = -1;
    for (int len = 1; len <= m; len++) {
        if (ans != -1)  {
            break;
        }
        //cout << "Start " << start << "\n";
        for (int start = 0; start < m-len; start++)   {
            set<int> cur;
            for (int i = 0; i < n; i++) {
                cur.insert(((spotty[i][start+len] - spotty[i][start]) + MOD)%MOD);
                //cout << ((spotty[i][start+len] - spotty[i][start]) + MOD)%MOD << "\n";
            }
            bool tof = true;
            for (int i = 0; i < n; i++) {
                int num = ((plain[i][start+len] - plain[i][start]) + MOD)%MOD;
                
                //cout << "HI " << num << "\n";
                if (cur.find(num) != cur.end()) {
                    tof = false;
                    break;
                }
            }
            if (tof == true)    {
                ans = len;
                break;
            }
        }
    }
    cout << ans << "\n";
}