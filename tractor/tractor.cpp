#include <bits/stdc++.h>

using namespace std;
const int MAX_N = 500;
int parent[MAX_N * MAX_N];
int comp_size[MAX_N * MAX_N];  // size of each component
int n;
void init() {
    for (int i = 0; i < n * n; i++) {
        parent[i] = i;
        comp_size[i] = 1;
    }
}

int find(int a) {
    if (a == parent[a]) { return a; }
    return parent[a] = find(parent[a]);
}

bool unite(int a, int b) {
    int root_a = find(a), root_b = find(b);
    if (root_a == root_b) { return false; }
    if (comp_size[root_a] > comp_size[root_b]) { swap(root_a, root_b); }
    parent[root_a] = root_b;
    comp_size[root_b] += comp_size[root_a];
    return comp_size[root_b] >= (n * n + 1) / 2;
}

struct Cell {
    int i, j;
};
struct Edge {
    Cell from, to;
    int cost;
};



int main()  {
    freopen("tractor.in","r",stdin);
	freopen("tractor.out","w",stdout);
    cin >> n;
    int field[MAX_N][MAX_N];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> field[i][j];
        }
    }
    init();
    vector<Edge> edges;
    int di[]{-1, 0, 1, 0}, dj[]{0, 1, 0, -1};
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            for (int k = 0; k < 4; k++) {
                Cell cur = {r+di[k], c+dj[k]};
                if (cur.i >= 0 && cur.i < n && cur.j >= 0 && cur.j < n && field[r][c] >= field[cur.i][cur.j]) {
                    edges.push_back({{r, c}, cur, field[r][c] - field[cur.i][cur.j]});
                }
            }
        }
    }
    sort(edges.begin(), edges.end(),
	     [](Edge a, Edge b) { return a.cost < b.cost; });
    for (Edge edge : edges) {
        if (unite(edge.from.i * n + edge.from.j, edge.to.i * n + edge.to.j))    {
            cout << edge.cost << endl;
            break;
        }
    }
}