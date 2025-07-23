#include <bits/stdc++.h>
using namespace std;

long long n, a, b;
vector<long long> papers;
string lisa, lisb;
long long dpa[301][301];
long long dpb[301][301];
const long long mod = 1e9+7;

void solve(long long (&curlis)[301][301], vector<long long> curstr)  {
    long long len = curstr.size();
    for (long long i = 0; i < n; i++) {
        long long dp[len+1][len+1][3];
        for (long long j = 0; j < len+1; j++) {
            for (long long k = 0; k < len+1; k++) {
                for (long long x = 0; x < 3; x++) {
                    dp[j][k][x] = 0;
                }
            }
        }
        // 0 = less, 1 = equal, 2 = more
        
        for (long long j = i; j < n; j++) {
            for (long long l = 0; l < len; l++)   {
                for (long long r = len-1; r > l; r--) {
                    //top
                    //cout << "INEWIG" << papers[j] << ' ' << curstr[l] << endl;
                    //cout << "WRBEGWBEGE" << l << ' ' << r << endl;
                    if (papers[j] == curstr[l]) {
                        dp[l][r][0] += dp[l+1][r][0];
                        dp[l][r][1] += dp[l+1][r][1];
                        dp[l][r][2] += dp[l+1][r][2];
                    } else if (papers[j] < curstr[l])   {
                        dp[l][r][0] += (dp[l+1][r][0] + dp[l+1][r][1] + dp[l+1][r][2]);
                        dp[l][r][0]+= mod;
                        dp[l][r][0] %= mod;
                        //dp[l][r][1] += dp[l+1][r][1];
                        //dp[l][r][2] += dp[l+1][r][2];
                    } else  {
                        dp[l][r][2] += (dp[l+1][r][0] + dp[l+1][r][1] + dp[l+1][r][2]);
                        dp[l][r][2]+= mod;
                        dp[l][r][2] %= mod;
                        //dp[l][r][0] += dp[l+1][r][0];
                        //dp[l][r][1] += dp[l+1][r][1];
                    }
                    //bottom
                    if (papers[j] == curstr[r]) {
                        dp[l][r][0] += dp[l][r-1][0];
                        dp[l][r][1] += dp[l][r-1][1];
                        dp[l][r][2] += dp[l][r-1][2];
                    } else if (papers[j] < curstr[r])   {
                        dp[l][r][2] += dp[l][r-1][2];
                        dp[l][r][0] += dp[l][r-1][1];
                        dp[l][r][0] += dp[l][r-1][0];
                        //dp[l][r][1] += dp[l][r-1][1];
                    } else  {
                        dp[l][r][2] += dp[l][r-1][1];
                        dp[l][r][2] += dp[l][r-1][2];
                        dp[l][r][0] += dp[l][r-1][0];
                        //dp[l][r][1] += dp[l][r-1][1];
                    }
                    dp[l][r][0]+= mod;
                    dp[l][r][1]+= mod;
                    dp[l][r][2]+= mod;
                    dp[l][r][0] %= mod;
                    dp[l][r][1] %= mod;
                    dp[l][r][2] %= mod;
                }
            }
            for (long long x = 0; x < len; x++)   {
                //cout << "IMHERE " << x << ' '  << papers[j] << ' ' << curstr[x] << endl;
                if (papers[j] == curstr[x]) {
                    dp[x][x][1] += 2;
                } else if (papers[j] < curstr[x])   {
                    dp[x][x][0] += 2; 
                } else  {
                    dp[x][x][2] += 2;
                }
            }
            for (long long x = 0; x < len; x++)   {
                cout << "FINALOOP " << i << ' ' << j << ' ' << x << ' ' << dp[x][len-1][0] << ' ' << dp[x][len-1][1] << ' ' << dp[x][len-1][2] << endl; 
                curlis[i][j] += dp[x][len-1][0];
                curlis[i][j] %= mod;
                curlis[i][j] += dp[x][len-1][1];
                curlis[i][j] %= mod;
                if (x != 0) {
                    curlis[i][j] += dp[x][len-1][2];
                }
                curlis[i][j] += mod;
                curlis[i][j] %= mod;
            }
        }
        
    }
    
}

signed main()  {
    //freopen("papers.in","r",stdin);
    //freopen("papers.out","w",stdout);
    cin >> n >> a >> b;
    papers.resize(n);
    for (long long i = 0; i < n; i++) {
        cin >> papers[i];
    }
    a -= 1;
    string ta = to_string(a);
    string tb = to_string(b);
    vector<long long> lisa;
    vector<long long> lisb;
    for (char i : ta)   {
        lisa.push_back(i-'0');
    } 
    for (char i : tb)   {
        lisb.push_back(i-'0');
    }
    solve(dpa, lisa);
    //cout <<" BREAK" << endl;
    solve(dpb, lisb);
    long long q;
    cin >> q;
    /*for (long long i = 0; i < n; i++) {
        for (long long j = 0; j < n; j++) {
            cout << i << ' ' << j << ' ' << dpa[i][j] << endl;
        }
    }
    */
    for (long long i = 0; i < q; i++) {
        long long x, y;
        cin >> x >> y;
        x -= 1;
        y -= 1;
        //cout <<  "INHERE " << dpb[x][y] << ' ' << dpa[x][y] << endl;
        long long ans1 = (dpb[x][y] + mod)%mod;
        long long ans2 = (dpa[x][y] + mod)%mod;
        long long ans3 = (ans1-ans2 + mod)%mod;
        cout << ans3 << endl;
    }
}