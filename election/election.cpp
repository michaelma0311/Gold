#include <bits/stdc++.h>
using namespace std;
int n, q;
vector<int> lis;
vector<int> treelis;
void build(long long treeind, long long curl, long long curr) {
    if (curl == curr) {
        treelis[treeind] = arr[curl];
    } else {
        long long mid = (curl + curr) / 2;
        build(2*treeind+1, curl, mid);
        build(2*treeind+2, mid + 1, curr);
        treelis[treeind] = max(treelis[2*treeind+1], treelis[2*treeind+2]);
    }
}

long long query(long long treeind, long long curl, long long curr, long long l, long long r) {
    //cout << treeind << ' ' << curl << ' ' << curr << endl;
    if (r < curl || curr < l) {
        return 0;
    }
    if (l <= curl && curr <= r) {
        return treelis[treeind];
    }
    long long mid = (curl + curr) / 2;
    long long ls = query(2*treeind+1, curl, mid, l, r);
    long long rs = query(2*treeind+2, mid + 1, curr, l, r);
    return max(ls, rs);
}

void update(long long treeind, long long curl, long long curr, long long ind, long long val) {
    if (curl == curr) {
        treelis[treeind] = val;
    } else {
        long long mid = (curl + curr) / 2;
        if (ind <= mid) {
            update(2*treeind+1, curl, mid, ind, val);
        } else {
            update(2*treeind+2, mid + 1, curr, ind, val);
        }
        treelis[treeind] = max(treelis[2*treeind+1], treelis[2*treeind+2]);
    }
}

int main()  {
    cin >> n >> q;
    lis.resize(n);
    treelis.resize(4*n);
    for (int i = 0; i < n; i++) {
        cin >> lis[i];
        lis[i] -= 1;
    }
    map<int, int> ma;
    for (int i =0 ; i < n; i++) {
        ma[i] = 0;
    }
    for (int i : lis)   {
        ma[i] += 1;
    }
    for (int _ = 0; _ < q; _++) {
        int x, y;
        cin >> x >>  y;
        x -= 1;
        y -= 1;
        ma[lis[x]] -= 1;
        ma[y] += 1;
        lis[x] = y;
        int curans = 0;
        vector<pair<int, int>> curlis;
        //get maxmimuim can optimize
        int maxnum = 0;
        for (const auto& i : ma) {
            if (i.second == 0)  {
                continue;
            }
            curlis.push_back({i.first, i.second});
            maxnum = max(maxnum, i.second);
        }
        sort(curlis.begin(), curlis.end(), cmp);
        int siz = curlis.size();
        vector<int> minvals(siz);
        
        int temp = INT_MAX;
        vector<int> curnums(siz);
        for (int i = siz-1; i >= 0; i--)    {
            temp = min(temp, curlis[i].first);
            minvals[i] = temp;
            curnums[i] = curlis[i].second;
        }
        for (int i = siz-1; i >= 0; i--)    {
            int a = maxnum - curnums[i];
            int dis = distance(curnums.begin(), lower_bound(curnums.begin(), curnums.end(), a));
            if (minvals[dis] >= curlis[i].first)    {
                break;
            }
            curans = max(curans, abs(minvals[dis]-curlis[i].first));
        }
        cout << curans << endl;
    }
}