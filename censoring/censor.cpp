#include <bits/stdc++.h>
using namespace std;
string s;
vector<string> strs;

const long long HM = 1000000007;
const long long HA = 100000007;
const long long HB = 101;

/* Given the hash 'h' of string S, computes the hash of S + 'ch'. */
long long hext(long long h, long long ch) {
  return (1ll * h * HA + ch + HB) % HM;
}


signed main()   {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);   
    freopen("censor.in","r",stdin);
	freopen("censor.out","w",stdout);
    cin >> s;
    long long q;
    cin >> q;
    strs.resize(q);
    unordered_map<long long, unordered_map<long long, long long>> vals;
    for (long long i = 0; i < q; i++) {
        cin >> strs[i];
        long long a = 0;
        for (char j : strs[i])  {
            a = hext(a, j-'a');
        }
        vals[strs[i].size()][a] = i;
    }
    string cur;
    vector<long long> curhash;
    vector<long long> pows;
    pows.push_back(1);
    curhash.push_back(0);
    /*for (const auto& pair : vals)   {
        cout << "HI " << pair.first << endl;
        for (const auto& i : pair.second)   {
            cout << i.first << ' ' << i.second << endl;
        }
    }
    */
    for (long long i = 0; i < s.size(); i++)  {
        cur += s[i];
        pows.push_back((pows.back() * HA)%HM);
        curhash.push_back(hext(curhash.back(), s[i]-'a'));
        //cout << "I SFAD  " << i << ' ' << curhash.back() << endl;
        for (const auto& pair : vals)   {
            long long len = pair.first;
            if (len > cur.size())   {
                continue;
            }
            unordered_map<long long, long long> tempmap = pair.second;
            long long hpref = (curhash[curhash.size()-len-1] * pows[len])%HM;
            long long hsuff = curhash.back() - hpref;
            if (hsuff < 0)  {
                hsuff += HM;
            }
            hsuff %= HM;
            bool found = false;
            //cout << cur << ' ' << len << ' ' << hsuff << endl;
            if (tempmap.find(hsuff) != tempmap.end())   {
                if (strs[tempmap[hsuff]] == cur.substr(cur.length() - len))   {
                    found = true;
                    curhash.resize(curhash.size()-len);
                    cur.erase(cur.length()-len, len);
                    break;
                }
            }
            if (found)  {
                break;
            }
        }
    }
    cout << cur << endl;
}