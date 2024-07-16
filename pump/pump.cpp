#include <bits/stdc++.h>
using namespace std;

struct Edge {
	int v, c, fl;
};

int n, m;
const int PRECISION = 1e6;
vector<vector<Edge>> adj;

int dijkstra(int minf) {
	priority_queue<pair<int, int>> pq;
	vector<int> cost(n, INT32_MAX);
	vector<bool> visited(n, false);

	cost[0] = 0;
	pq.push({0, 0});

	while (!pq.empty()) {
		pair<int, int> nxt = pq.top();
		pq.pop();

		if (nxt.second != cost[nxt.first] || visited[nxt.first]) { continue; }

		for (Edge u : adj[nxt.first]) {
			int ct = u.c + nxt.second;

			/*
			 * if the path has a flow value less
			 * than our minimum, we can't consider it
			 */
			if (u.fl < minf || visited[u.v]) { continue; }

			// path more optimal
			if (cost[u.v] > ct) {
				cost[u.v] = ct;
				pq.push({u.v, ct});
			}
		}
	}
	return cost[n - 1] == INT32_MAX ? -1 : cost[n - 1];
}

int main() {
	freopen("pump.in", "r", stdin);
	freopen("pump.out", "w", stdout);

	cin >> n >> m;

	adj.resize(n);
	vector<int> flows;
	for (int i = 0; i < m; i++) {
		int u, v, c, fl;
		cin >> u >> v >> c >> fl;

		flows.push_back(fl);
		adj[--u].push_back({--v, c, fl});
		adj[v].push_back({u, c, fl});
	}

	int ans = -1;
	// we only have to consider the flow values given to us
	for (int flow : flows) {
		int cur = dijkstra(flow);

		// can't complete this path
		if (cur == -1) { continue; }
		double ratio = double(flow) / double(cur);
		ans = max(ans, (int)(ratio * PRECISION));
	}
	cout << ans << '\n';
}