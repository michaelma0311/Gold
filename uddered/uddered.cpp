#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main() {
	string s;
	cin >> s;
	vector<vector<int>> nums(26);
	bool fir = true;
	for (int i = 0; i < s.length(); i++)	{
		if (s[i] == 'm' || s[i] == 'i' || s[i]=='l' || s[i] == 'd' || s[i] == 'r' || s[i] == 'e')	{
			fir = false;
			break;
		}
	}
	string a = "abcfghjknopqstuvwxyz";
	if (!fir)	{
		a = "mildrebs";
	}
	for (int i = 0; i < 26; i++)	{
		nums[i].resize(26);
	}
	vector<vector<int>> prefsu(21);
	
	map<char, int> ma;
	int siz = a.size();
	for (int i = 0; i < a.size(); i++) {
		ma[a[i]] = i;
	}
	for (int i =0; i < s.length()-1; i++)	{
		//cout << s[i] << ' ' << ma[s[i]] << endl;
		nums[ma[s[i]]][ma[s[i+1]]] += 1;
	}
	for (int i = 0; i < siz; i++)	{
		prefsu[i].resize(1<<siz);
	}
	//cout <<"ADF " << endl;
	/*for (int i = 0; i < siz; i++)	{
		cout << i << endl;
		for (int j = 1; j < (1 << siz); j++)	{
			for (int k = 0; k < siz; k++)	{
				//cout << i << ' ' << k << endl;
				if ((1 << k) > j)	{
					break;
				}
				if (j & (1 << k))	{
					//cout << "WGWEG " << endl;
					prefsu[i][j] += nums[ma[a[i]]][ma[a[k]]];
				}
			}
		}
	}*/
	//cout << "ADD" << endl;
	int ans = INT_MAX;
	vector<int> dp((1<<siz), INT_MAX);
	dp[0] = 0;
	for (int i = 1; i < (1<<siz); i++)	{
		for (int k = 0; k < siz; k++)	{
			if (i & (1 << k))	{
				int su = 0;
				for (int j = 0; j < siz; j++)	{
					if (i & (1 << j))	{
						su += nums[k][j];
					}
				}
				//cout << su << endl;
				dp[i] = min(dp[i], dp[i^(1<<k)] + su);
			}
		}
	}
	cout << dp[(1 << siz)-1]+1 << endl;
	
}