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
    vector<priority_queue<int, vector<int>, greater<int>>> temp(n);
    map<int, int> ma;
    for (int i= 0; i < n; i++)  {
        ma[i] = 0;
    }
    for (int i =0 ;i  < n; i++) {
        cin >> lis[i];
        ma[i] += 1;
    }
    for (const auto& i : ma)    {
        temp[i.second].push(i.first);
    }
    for (int i = 0; i < q; i++) {
        int a, b;
        cin >> a >> b;
        a -= 1;
        lis[]
    }


}