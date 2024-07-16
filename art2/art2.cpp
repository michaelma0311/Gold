#include <bits/stdc++.h>

using namespace std;

int main()  {
    freopen("art2.in","r",stdin);
	freopen("art2.out","w",stdout);
    int n;
    cin >> n;
    vector<int> lis(n);
    vector<int> start(n+1);
    vector<int> end(n+1);
    fill(start.begin(), start.end(), INT_MAX);
    for (int i = 0; i < n; i++) {
        cin >> lis[i];
        //cout << lis[i] << ' ' << n << endl;
        start[lis[i]] = min(start[lis[i]], i);
        end[lis[i]] = max(end[lis[i]], i); 
    }
    //cout << "ADAD " << endl;
    start[0] = 0;
    end[0] = n-1;
    stack<int> cur;
    bool contan0 = false;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (start[lis[i]] == i) {
            //cout << lis[i] << endl;
            if (lis[i] == 0)    {
                contan0 = true;
            }
            cur.push(lis[i]);
            ans = max(ans, (int)cur.size());
        }
        if (!cur.empty())   {
            if (cur.top() != lis[i])    {
                cout << -1 << endl;
                return 0;
            }
        }
        
        if (end[lis[i]] == i)   {
            cur.pop();
        }
    }
    if (contan0)    {
        cout << ans-1 << endl;
    } else  {
        cout << ans << endl;
    }

}