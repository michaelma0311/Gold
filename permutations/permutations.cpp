#include <bits/stdc++.h>
using namespace std;
#define int long long
struct tri {
    pair<int,int> a, b, c;
    tri(pair<int,int> p1, pair<int,int> p2, pair<int,int> p3) {
        vector<pair<int,int>> pts = {p1, p2, p3};
        sort(pts.begin(), pts.end()); 
        a = pts[0]; b = pts[1]; c = pts[2];
    }
    
    long long area2() const {
        return abs((b.first - a.first) * (c.second - a.second) 
                 - (c.first - a.first) * (b.second - a.second));
    }
    
    bool operator<(const tri& other) const {
        return tie(a, b, c) < tie(other.a, other.b, other.c);
    }
    bool operator==(const tri& other) const {
        return tie(a, b, c) == tie(other.a, other.b, other.c);
    }
};
long long cross(pair<int,int> a, pair<int,int> b, pair<int,int> c) { 
    return (b.first - a.first)*(c.second - a.second) - (b.second - a.second)*(c.first - a.first);
}

bool insid(pair<int,int> A, pair<int,int> B, pair<int,int> C, pair<int,int> P) {
    long long s1 = cross(A, B, P);
    long long s2 = cross(B, C, P);
    long long s3 = cross(C, A, P);
    return ((s1 > 0) && (s2 > 0) && (s3 > 0)) || ((s1 < 0) && (s2 < 0) && (s3 < 0));
}

int can1(const pair<int,int>& a, const pair<int,int>& b, const pair<int,int>& c) {
    long long val = cross(a, b, c);
    if (val > 0) return 1;
    if (val < 0) return -1;
    return 0;
}

bool can(pair<int,int> A, pair<int,int> B, pair<int,int> C, pair<int,int> D) {
    int o1 = can1(A, B, C);
    int o2 = can1(A, B, D);
    int o3 = can1(C, D, A);
    int o4 = can1(C, D, B);

    return (o1 != o2) && (o3 != o4);
}

bool canall(pair<int,int> A, pair<int,int> B, pair<int,int> C, pair<int,int> W) {
    if (can(W, A, B, C)) return false; 
    if (can(W, B, C, A)) return false; 
    if (can(W, C, A, B)) return false; 
    return true;
}

double dist(pair<int,int> a, pair<int,int> b) {
    return sqrt((a.first - b.first)*(a.first - b.first) + (a.second - b.second)*(a.second - b.second));
}

signed main()  {
    int n;
    cin >> n;
    const int mod = 1e9+7;
    vector<pair<int,int>> lis(n);
    for (int i = 0; i < n; i++) {
        cin >> lis[i].first >> lis[i].second;
    }
    vector<tri> triangles;
    map<tri,int> insidepoints;
    map<tri,vector<int>> outsidepoints;
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            for (int k = j+1; k < n; k++) {
                tri t = {lis[i], lis[j], lis[k]};
                triangles.push_back(t);
                for (int w = 0; w < n; w++) {
                    if (i == w || j == w || k == w) {
                        continue;
                    }
                    if (insid(t.a, t.b, t.c, lis[w])) {
                        insidepoints[t] += 1;
                    } else {
                        if (canall(t.a, t.b, t.c, lis[w])) {
                            outsidepoints[t].push_back(w);
                        }
                    }
                }
                //cout << i << ' ' << j<< ' ' << k << ' '<< insidepoints[t] << ' ' << outsidepoints[t].size() << endl;
            }
        }
    }
    sort(triangles.begin(), triangles.end(), [](const tri& a, const tri& b) {
        return a.area2() < b.area2();
    });
    
    map<tri, int> triIndex;
    for (int i = 0; i < (int)triangles.size(); i++) {
        triIndex[triangles[i]] = i;
    }
    
    int maxNum = n + 1; 
    vector<vector<int>> dp(triangles.size(), vector<int>(maxNum, 0));

    for (int i = 0; i < triangles.size(); i++) {
        dp[i][3] += 1;
        for (int k = 3; k < n; k++) {
            dp[i][k+1] += dp[i][k] * (insidepoints[triangles[i]] - (k-3));
            dp[i][k+1] %= mod;
            for (int w : outsidepoints[triangles[i]]) {
                pair<int,int> a = triangles[i].a;
                pair<int,int> b = triangles[i].b;
                pair<int,int> c = triangles[i].c;
                pair<int,int> d = lis[w];
                tri newtri = {a, b, c};
                if (insid(a, b, d, c)) {
                    newtri = {a, b, d};
                } else if (insid(a, d, c, b)) {
                    newtri = {a, d, c};
                } else if (insid(d, b, c, a)) {
                    newtri = {d, b, c};
                }
                dp[triIndex[newtri]][k+1] += dp[i][k];
                dp[triIndex[newtri]][k+1] %= mod;
            }
        }
    }
    
    int ans = 0;
    for (int i = 0; i < triangles.size(); i++) {
        ans += dp[i][n];
        ans %= mod;
    }
    ans *= 6;
    ans %= mod;
    cout << ans << endl;
    
}