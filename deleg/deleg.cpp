#include <bits/stdc++.h>
using namespace std;
#define int long long
int n;
vector<vector<int>> adj;
vector<int> depth;
vector<int> parent;

void dfs(int cur, int prev, int cnt) {
    depth[cur] = cnt;
    parent[cur] = prev;
    for (int i : adj[cur])  {
        if (i == prev)  {
            continue;
        }
        dfs(i, cur, cnt+1);
    }
}

signed main()  {
    freopen("deleg.in","r",stdin);
	freopen("deleg.out","w",stdout);
    cin >> n;
    adj.resize(n);
    depth.resize(n);
    parent.resize(n);
    vector<int> ans(n);
    vector<multiset<int>> cont(n);
    for (int i = 0; i < n-1; i++) {
        int a, b;
        cin >> a >> b;
        a -= 1;
        b -= 1;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    //cout << "HI " << endl;
    dfs(0, -1, 0);
    //cout << "HI " << endl;
    vector<int> firs;
    vector<bool> visited(n);
    bool fir = false;
    for (int i = 0; i < n; i++) {
        if (adj[i].size() == 1) {
            if (fir == true)    {
                fir = false;
            } else  {
                firs.push_back(i);
            }
        }
    }
    //cout << "HI " << endl;
    for (int k = 1; k < 5; k++) {
        //cout << "AFIWRBHGOB FSD " << k << endl; 
        if ((n-1)%k != 0)   {
            continue;
        }
        priority_queue<pair<int, int>> star;
        fill(visited.begin(), visited.end(), false);
        for (int i = 0; i < n; i++) {
            cont[i].clear();
        }
        for (int i : firs)  {
            //cout << i+1 << endl;
            if (i != 0) {
                cont[i].insert(0);
                star.push({depth[i], i});
            }
        }
        bool tof = true;
        while (star.empty() == false && tof == true)   {
            int cur = star.top().second;
            star.pop();
            if (visited[cur])   {
                continue;
            }
            visited[cur] = true;
            int siz = cont[cur].size();
            //scout << "HI " << cur+1 << ' ' << parent[cur] + 1 << endl;
            if (parent[cur] == -1)  {
                cout << "AGE:BGU " << siz << endl;
                //cout << "NGER " << endl;
                if (cont[cur].size() != 0)  {
                    auto l = cont[cur].begin();
                    auto r = prev(cont[cur].end());
                    int skip = 0;
                    int skipval = 0;
                    while (true)   {
                        int cursum = (*l) + (*r);
                        if (cursum == k)   {
                            l++;
                            r--;
                        } else if (cursum < k) {
                            l++;
                            skip += 1;
                            skipval = (*l);
                        } else  {
                            r--;
                            skip += 1;
                            skipval = (*l);
                        }
                        if (l == r) {
                            skip += 1;
                            skipval = (*l);
                            break;
                        } if (r == prev(l)) {
                            break;
                        }
                    }
                    if (skip != 0)  {
                        tof = false;
                        break;
                    }
                }
                
            } else if (siz == 1)   {
                if ((*cont[cur].begin()) + 1 != k)   {
                    if (parent[cur] == -1)  {
                        break;
                    }
                    cont[parent[cur]].insert((*cont[cur].begin()) + 1);
                }
            } else if (siz >= 1)   {
                //cout << "ADAD " << endl;
                auto l = cont[cur].begin();
                auto r = prev(cont[cur].end());
                int skip = 0;
                int skipval = 0;
                while (true)   {
                    int cursum = (*l) + (*r);
                    if (cursum == k)   {
                        l++;
                        r--;
                    } else if (cursum < k) {
                        l++;
                        skip += 1;
                        skipval = (*l);
                    } else  {
                        r--;
                        skip += 1;
                        skipval = (*l);
                    }
                    if (l == r) {
                        skip += 1;
                        skipval = (*l);
                        break;
                    } if (r == prev(l)) {
                        break;
                    }
                }
                if (siz%2 == 0) {
                    if (skip >= 1)   {
                        tof = false;
                        break;
                    }
                } else  {
                    if (skip > 1)   {
                        tof = false;
                        break;
                    }
                    if (skip == 1)  {
                        if (skipval + 1 != k)   {
                            if (parent[cur] == -1)  {
                                break;
                            }
                            cont[parent[cur]].insert(skipval+1);
                        }
                    }
                }
            }
            if (parent[cur] != -1)  {
                star.push({depth[parent[cur]], parent[cur]});
            }
        }
        //cout << tof << ' ' << "TOF " << endl;
        if (tof == true)    {
            ans[k-1] = 1;
        } else  {
            ans[k-1] = 0;
        }
    }
    for (int i = 0; i < n-1; i++) {
        cout << ans[i];
    }
    cout << endl;

}