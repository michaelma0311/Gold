#include <bits/stdc++.h>
using namespace std;
int n;
vector<int> lis;

bool check(int mid) {
    //cout << "ADAD " << mid << endl;
    vector<int> curlis;
    vector<int> templis;
    for (int i = 0; i < mid; i++)   {
        curlis.push_back(lis[i]);
        templis.push_back(lis[i]);
    }
    sort(templis.begin(), templis.end());
    reverse(templis.begin(), templis.end());
    vector<stack<int>> counters;
    vector<int> fronts;
    //cout << "HERE" << endl;
    for (int i : curlis)    {
        //cout << "INSIDE " << i <<' ' << templis.back() << endl;
        auto it = lower_bound(fronts.begin(), fronts.end(), i);
        if (it == fronts.end()) {
            fronts.push_back(i);
            stack<int> temp;
            temp.push(-1);
            temp.push(i);
            counters.push_back(temp);
        } else  {
            int ind = it - fronts.begin();
            //cout << "SECOND " << ind << ' ' << fronts.size() << endl;
            fronts[ind] = i;
            counters[ind].push(i);
        }
        bool tof = false;
        for (int j = 0; j < counters.size(); j++)   {
            if (tof)    {
                break;
            }
            //cout << counters[j].top() << ' ' << templis.back() << endl;

            while (counters[j].top() != -1) {
                if (counters[j].top() == templis.back())    {
                    counters[j].pop();
                    fronts[j] = counters[j].top();
                    templis.pop_back();
                } else  {
                    tof = true;
                    break;
                }
            }
        }
    }
    //cout << "DONE" << endl;
    int i = 0;
    vector<int> sol;
    while (i < counters.size()) {
        if (counters[i].empty() == true || counters[i].top() == -1)    {
            i += 1;
        } else  {
            sol.push_back(counters[i].top());
            counters[i].pop();
        }
    }
    vector<int> sortedsol = sol;
    sort(sortedsol.begin(), sortedsol.end());
    if (sortedsol == sol) {
        return true;
    } else  {
        return false;
    }

}

int main()  {
    freopen("dishes.in","r",stdin);
	freopen("dishes.out","w",stdout);
    cin >> n;
    lis.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> lis[i];
    }
    int lo = 0;
    int hi = n;
    int ans = 0;
    while (lo <= hi)    {
        int mid = (lo+hi)/2;
        if (check(mid)) {
            ans = mid;
            lo = mid + 1;
        } else  {
            hi = mid-1;
        }
    }
    cout << ans << endl;
}