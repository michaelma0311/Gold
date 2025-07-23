#include <bits/stdc++.h>

using namespace std;

signed main()  {
    freopen("lightsout.in","r",stdin);
	freopen("lightsout.out","w",stdout);
    long long n;
    cin >> n;
    vector<pair<long long, long long>> lis(n+1);
    long long totsum = 0;
    for (long long i = 0; i < n; i++) {
        cin >> lis[i].first >> lis[i].second;
    }
    vector<char> direc(n);
    char a = 'L';
    
    lis[n] = lis[0];
    for (long long i = 0; i < n; i++) {
        char curd;
        if (lis[i+1].first == lis[i].first) {
            if (lis[i+1].second > lis[i].second)  {
                curd = 'U';
            } else  {
                curd = 'D';
            }
        } else  {
            if (lis[i+1].first > lis[i].first)  {
                curd = 'R';
            } else  {
                curd = 'D';
            }
        }
        if (a == 'L')   {
            if (curd == 'U')    {
                direc[i] = 'S';
            } else  {
                direc[i] = 'B';
            }
        } else if (a == 'R')    {
            if (curd == 'U')    {
                direc[i] = 'B';
            } else  {
                direc[i] = 'S';
            }
        } else if (a == 'U')    {
            if (curd == 'R')    {
                direc[i] = 'S';
            } else  {
                direc[i] = 'B';
            }
        } else  {
            if (curd == 'R')    {
                direc[i] = 'B';
            } else  {
                direc[i] = 'S';
            }
        }
        a = curd;
    }
    vector<long long> curdis(n);
    for (long long i = 1; i <= n; i++) {
        curdis[i-1] = abs(lis[i].first - lis[i-1].first) + abs(lis[i].second-lis[i-1].second);
        totsum += abs(lis[i].first - lis[i-1].first) + abs(lis[i].second-lis[i-1].second);
    }
    //curdis[n-1] = abs(lis[0].first - lis.back().first) + abs(lis[0].second - lis.back().second);
    totsum += abs(lis[0].first - lis.back().first) + abs(lis[0].second - lis.back().second);
    //cout << totsum << endl;
    long long cursum = 0;
    vector<long long> dist(n+1);
    for (long long i = 1; i <= n; i++) {
        cursum += curdis[i-1];
        dist[i] = min(cursum, totsum - cursum);
        
    }
    vector<long long> pref(n+1);
    pref[0] = 0;
    for (long long i = 1; i <= n; i++) {
        pref[i] = pref[i-1] + curdis[i-1];
    }
    unordered_map<string, long long> temp;
    temp[""] = 2;
    for (long long len = 1; len <= n-2; len++) {
        string curstr;
        for (long long i = 1; i < n-len; i++) {
            //string curstr;
            curstr = "";
            //cout << "HI " << endl;
            for (long long j = i; j < i+len; j++) {
                //cout << "HI MY NAME IS " << j << ' ' << curdis[j] << endl;
                curstr += to_string(curdis[j]);
                curstr += direc[j];
            }
            //cout << curstr << endl;
            if (temp.find(curstr) == temp.end())    {
                temp[curstr] = 0;
            }
            temp[curstr] += 1;
            //cout << curstr << ' ' << temp[curstr] << endl;
        }
        //cout << curstr << endl;
        //temp.insert(curstr);
    }
    for (long long i : dist)  {
        //cout << i << endl;
    }
    for (long long i : pref)  {
        //cout << "PREF " << i << endl;
    }
    long long ans = 0;
    for (long long i = 1; i < n; i++) {
        string curtemp = "";
        long long ind = i;
        long long lenned = 0;
        while (temp[curtemp] > 1 && ind < n)   {
            curtemp += to_string(curdis[ind]);
            curtemp += direc[ind];
            lenned += curdis[ind];
            ind += 1;
            //cout << "HI " << i << ' ' << curtemp << ' ' << temp[curtemp] << endl;
        }
        long long dis = dist[ind];
        //cout << i << ' ' << curtemp << ' ' << ind << ' ' << dis << ' ' << lenned << ' ' << dist[i] << endl;
        ans = max(ans, dis + lenned - dist[i]);
        
    }
    cout << ans << endl;

}