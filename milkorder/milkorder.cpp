#include <bits/stdc++.h>

using namespace std;

#define pii pair<int, int>
#define f first
#define s second
#define vi vector<int>
#define vb vector<bool>
#define vvi vector<vector<int>>
#define vii vector<pair<int, int>>
#define vvb vector<vector<bool>>
#define piii pair<int, pair<int, int>>
#define vvpii vector<vector<pair<int, int>>>
#define inf 987654321
#define pb push_back
#define p push
#define ll long long
#define ull unsigned long long
#define g get
#define dbl double
#define mn int(1e5+5)
int N, M;
vi adj[mn];
int indegree[mn];
int inp[200000];
vi ans;

bool buildtopo (int x)
{
    ans.clear();
    priority_queue<int, vi, greater<int>> pq;
    for (auto & i : adj)
        i.clear();
    for (auto & i : indegree)
        i = 0;
    int loc = 0;
    for (int i = 0; i < x; i++)
    {
        int n = inp[loc];
        loc++;
        int arr[n];
        for (int j = 0; j < n; j++)
        {
            arr[j] = inp[loc], loc++;
            if (j)
            {
                adj[arr[j-1]].pb(arr[j]);
                indegree[arr[j]]++;
            }
        }
    }
    for (int i = 1; i <= N; i++)
        if (indegree[i] == 0)
            pq.p(i);
    while (!pq.empty())
    {
        int loc = pq.top();
        pq.pop();
        ans.pb(loc);
        for (auto i : adj[loc])
            if (--indegree[i] == 0)
                pq.p(i);
    }
    return ans.size() == N;
}

int main() {
    freopen("milkorder.in", "r", stdin);
    freopen("milkorder.out", "w", stdout);
    cin >> N >> M;
    int loc = 0;
    for (int i = 0; i < M; i++)
    {
        int n;
        cin >> n;
        inp[loc] = n;
        loc++;
        for (int j = 0; j < n; j++)
            cin >> inp[loc], loc++;
    }
    int bloc = 0;
    for (int am = M / 2; am > 0; am /= 2)
        while (bloc+am <= M && buildtopo(bloc+am))
            bloc += am;
    buildtopo(bloc);
    for (int i = 0; i < N; i++)
    {
        cout << ans[i];
        if (i != N-1)
            cout << " ";
    }
    cout << endl;
}