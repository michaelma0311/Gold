#include <bits/stdc++.h>
using namespace std;
pair<int, int> mini(const pair<int, int>& p1, const pair<int, int>& p2) {
    if (p1.first < p2.first) return p1;
    if (p1.first > p2.first) return p2;
    if (p1.second < p2.second) return p1;
    return p2;
}
pair<int, int> maxi(const pair<int, int>& p1, const pair<int, int>& p2) {
    if (p1.first > p2.first) return p1;
    if (p1.first < p2.first) return p2;
    if (p1.second > p2.second) return p1;
    return p2;
}
void solve()    {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> lines(m);
    vector<vector<vector<int>>> grids(m);
    vector<map<int, pair<int, int>>> malis(m);
    vector<int> counts(n);
    vector<int> star(n);
    vector<int> end(n);
    fill(star.begin(), star.end(),-1);
    fill(end.begin(), end.end(),-1);
    for (int i = 0; i < m; i++) {
        grids[i].resize(n);
        for (int j = 0; j < n; j++) {
            grids[i][j].resize(n);
            fill(grids[i][j].begin(), grids[i][j].end(), -2);
        }
    }
    for (int i = 0; i < m; i++) {
        int a;
        cin >> a;
        vector<int> temp(a);
        map<int, pair<int, int>> tempmap;
        for (int j = 0; j < a; j++) {
            cin >> temp[j];
            temp[j] -= 1;
            counts[temp[j]] += 1;
            if (star[temp[j]] == -1)    {
                star[temp[j]] = i;
            }
            end[temp[j]] = i;
            if (tempmap.find(temp[j]) == tempmap.end()) {
                tempmap[temp[j]] = {j, -1};
            } else  {
                tempmap[temp[j]].second = j;
            }
        }
        malis[i] = tempmap;
        lines[i] = temp;
    }
    vector<int> states(n);  
    for (int i = 0; i < n; i++) {

    }
    bool tof = true;
    for (int i = 0; i < m; i++) {
        vector<bool> on(n);
        vector<int> cur;
        vector<int> curinds;
        for (const auto& pair : malis[i])   {
            curinds.push_back(pair.first);
        }
        //cout << "BREAK " << endl;
        for (int k = 0; k < curinds.size(); k++)    {
            for (int j = k+1; j < curinds.size(); j++)    {

                //cout << "HI " << malis[i][k].first << ' ' << malis[i][k].second << ' ' << malis[i][j].first << ' ' << malis[i][j].second << endl;
                pair<int,int> pair1 = malis[i][curinds[j]];
                pair<int, int> pair2 = malis[i][curinds[k]];
                int s1 = pair1.first;
                int e1 = pair1.second;
                int s2 = pair2.first;
                int e2 = pair2.second;
                int a = -1;
                if (s1 < s2 && e1 < s2)    {
                    a = 0;
                    grids[i][curinds[j]][curinds[k]] = a;
                } else if (s1 < s2 && e2 < e1)   {
                    a = 1;
                    grids[i][curinds[j]][curinds[k]] = a;
                } else if (s2 < s1 && e1 < e2)  {
                    a = 2;
                    grids[i][curinds[k]][curinds[j]] = a;
                } else if  (s2 < s1 && e2 < s1){
                    a = 3;
                    grids[i][curinds[k]][curinds[j]] = a;
                }
                if (a == -1)    {
                    //cout << curinds[k]+1 << ' ' << curinds[j]+1 << ' ' << s1 << ' ' << e1 << ' ' << s2 << ' ' << e2 << endl;
                    tof = false;
                }
                //grids[i][curinds[k]][curinds[j]] = a;
                //grids[i][curinds[j]][curinds[k]] = a;
            }
        }
    }
    if (tof)    {
        for (int i = 0; i < n; i++) {
            if (!tof)   {
                break;
            }
            for (int j = i+1; j < n; j++) {
                set<int> tempnums;
                for (int k = 0; k < m; k++) {
                    //cout << grids[k][i][j] << ' ' << grids[k][j][i] << endl;
                    if (grids[k][i][j] != -2)   {
                        tempnums.insert(grids[k][i][j]);
                    } 
                    if (grids[k][j][i] != -2)   {
                        tempnums.insert(grids[k][j][i]);
                    }
                    
                }
                if (tempnums.size() > 1)    {
                    tof = false;
                    break;
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        counts[i] /= 2;
        if (counts[i] != end[i] - star[i]+1) {
            tof = false;
            break;
        }
    }
    if (tof)    {
        cout << "YES" << endl;
    } else  {
        cout << "NO" << endl;
    }

}

int main()  {
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}