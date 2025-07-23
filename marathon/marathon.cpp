#include <bits/stdc++.h>
using namespace std;
long long n, q;
vector<pair<long long, long long>> lis;
vector<long long> treelis;
vector<long long> treelissum;
long long dist(pair<long long, long long> x, pair<long long, long long> y)    {
    return abs(x.first-y.first) + abs(x.second-y.second);
}
void buildsum(vector<pair<long long, long long>>& arr, long long treeind, long long curl, long long curr) {
    if (curl == curr) {
        if (curl == 0)  {
            return;
        }
        treelissum[treeind] = dist(arr[curl], arr[curl-1]);
    } else {
        long long mid = (curl + curr) / 2;
        buildsum(arr, 2*treeind+1, curl, mid);
        buildsum(arr, 2*treeind+2, mid + 1, curr);
        treelissum[treeind] = treelissum[2*treeind+1] + treelissum[2*treeind+2];
    }
}

long long querysum(long long treeind, long long curl, long long curr, long long l, long long r) {
    //cout << treeind << ' ' << curl << ' ' << curr << endl;
    if (r < curl || curr < l) {
        return 0;
    }
    if (l <= curl && curr <= r) {
        return treelissum[treeind];
    }
    long long mid = (curl + curr) / 2;
    long long ls = querysum(2*treeind+1, curl, mid, l, r);
    long long rs = querysum(2*treeind+2, mid + 1, curr, l, r);
    return ls + rs;
}

void updatesum(long long treeind, long long curl, long long curr, long long ind) {
    if (curl == curr) {
        if (curl == 0)  {
            return;
        }
        treelissum[treeind] = dist(lis[curl], lis[curl-1]);
    } else {
        long long mid = (curl + curr) / 2;
        if (ind <= mid) {
            updatesum(2*treeind+1, curl, mid, ind);
        } else {
            updatesum(2*treeind+2, mid + 1, curr, ind);
        }
        treelissum[treeind] = treelissum[2*treeind+1] + treelissum[2*treeind+2];
    }
}

void build(vector<pair<long long, long long>>& arr, long long treeind, long long curl, long long curr) {
    if (curl == curr) {
        if (curl == 0 || curl == n-1)   {
            return;
        }
        treelis[treeind] = dist(lis[curl-1], lis[curl+1]) - dist(lis[curl-1], lis[curl]) - dist(lis[curl], lis[curl+1]);
    } else {
        long long mid = (curl + curr) / 2;
        build(arr, 2*treeind+1, curl, mid);
        build(arr, 2*treeind+2, mid + 1, curr);
        treelis[treeind] = min(treelis[2*treeind+1], treelis[2*treeind+2]);
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
    return min(ls, rs);
}

void update(long long treeind, long long curl, long long curr, long long ind) {
    if (curl == curr) {
        if (curl == 0 || curl == n-1)   {
            return;
        }
        treelis[treeind] = dist(lis[curl-1], lis[curl+1]) - dist(lis[curl-1], lis[curl]) - dist(lis[curl], lis[curl+1]);
    } else {
        long long mid = (curl + curr) / 2;
        if (ind <= mid) {
            update(2*treeind+1, curl, mid, ind);
        } else {
            update(2*treeind+2, mid + 1, curr, ind);
        }
        treelis[treeind] = min(treelis[2*treeind+1], treelis[2*treeind+2]);
    }
}


signed main()  {
    freopen("marathon.in", "r", stdin);  
    freopen("marathon.out", "w", stdout);
    cin >> n >> q;
    lis.resize(n);
    for (long long i= 0; i < n; i++)  {
        long long x, y;
        cin >> x >> y;
        lis[i] = make_pair(x, y);
    } 
    treelissum.resize(4*n);
    treelis.resize(4*n);
    buildsum(lis, 0, 0, n);
    build(lis, 0, 0, n);
    for (long long i = 0; i < q; i++) {
        char typ;
        cin >> typ;
        if (typ == 'Q') {
            long long x, y;
            cin >> x >> y;
            x -= 1;
            y -= 1;
            if (y == x+1)   {
                cout << querysum(0, 0, n, x+1, y) << endl;
            } else  {
                cout << querysum(0, 0, n, x+1, y) + query(0, 0, n, x+1, y-1) << endl;
            }
        } else  {
            long long x, y, z;
            cin >> x >> y >> z;
            x -= 1;
            lis[x] = make_pair(y, z);
            update(0, 0, n, x);
            if (x != 0) {
                update(0, 0, n, x-1);
            }
            if (x != n-1)   {
                update(0, 0, n, x+1);
                updatesum(0, 0, n, x+1);
            }
            updatesum(0, 0, n, x);
        }
    }

}