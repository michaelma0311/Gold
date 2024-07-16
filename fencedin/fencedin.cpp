#include <bits/stdc++.h>
using namespace std;

struct Edge {
	int cost;
	int i;
	int j;
};

struct DSU {
	vector<int> e;
	DSU(int N) { e = vector<int>(N, -1); }

	// get representive component (uses path compression)
	int get(int x) { return e[x] < 0 ? x : e[x] = get(e[x]); }

	bool same_set(int a, int b) { return get(a) == get(b); }

	int size(int x) { return -e[get(x)]; }

	bool unite(int x, int y) {  // union by size
		x = get(x), y = get(y);
		if (x == y) return false;
		if (e[x] > e[y]) swap(x, y);
		e[x] += e[y];
		e[y] = x;
		return true;
	}
};

int main() {
	freopen("fencedin.in", "r", stdin);
	freopen("fencedin.out", "w", stdout);

	int hdist, vdist, n, m;
	cin >> hdist >> vdist >> n >> m;

	vector<int> vx(n + 1), vy(m + 1);

	for (int i = 1; i <= n; i++) { cin >> vx[i]; }

	for (int i = 1; i <= m; i++) { cin >> vy[i]; }

	vx.push_back(hdist);
	vy.push_back(vdist);

	sort(vx.begin(), vx.end());
	sort(vy.begin(), vy.end());

	// add fences at borders to calculate edges at front/back
	n += 2;
	m += 2;

    
	vector<Edge> edges;

	int cur_sect = 0, row = 1;
	while (row < m) {
		for (int i = 0; i < n - 2; i++) {
			edges.push_back(
			    Edge{vy[row] - vy[row - 1], cur_sect, cur_sect + 1});
			cur_sect++;
		}

		cur_sect++;
		row++;
	}

	cur_sect = n - 1;
	int col = 1;
	while (col < n) {
		int init = cur_sect;
		for (int i = 0; i < m - 2; i++) {
			edges.push_back(
			    Edge{vx[col] - vx[col - 1], cur_sect - (n - 1), cur_sect});

			cur_sect += (n - 1);
		}
		cur_sect = init + 1;
		col++;
	}

	DSU dsu((n + 2) * (m + 2));

	sort(edges.begin(), edges.end(),
	     [](const Edge &t, const Edge &y) { return t.cost < y.cost; });

	long long ans = 0;
	for (Edge &i : edges) {
		if (dsu.unite(i.i, i.j)) { ans += i.cost; }
	}
	cout << ans << endl;
}