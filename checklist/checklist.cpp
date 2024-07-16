#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

using ll = long long;

const ll MAX_D = 1e18;
struct Coord {
  public:
	int x, y;
};

ll solve(const Coord &a, const Coord &b) {
	int x = (a.x - b.x);
	int y = (a.y - b.y);

	return (x * x) + (y * y);
}

int main() {
	freopen("checklist.in", "r", stdin);
	freopen("checklist.out", "w", stdout);

	int h, g;
	cin >> h >> g;

	vector<Coord> hs(h), gs(g);

	for (int i = 0; i < h; i++) { cin >> hs[i].x >> hs[i].y; }

	for (int i = 0; i < g; i++) { cin >> gs[i].x >> gs[i].y; }

	vector<vector<vector<ll>>> lis(
	    h + 1, vector<vector<ll>>(g + 1, vector<ll>(2, MAX_D)));

	lis[1][0][0] = 0;

	for (int i = 0; i <= h; i++) {
		for (int j = 0; j <= g; j++) {
			if (i > 1) {
				lis[i][j][0] =
				    min(lis[i][j][0],
				        lis[i - 1][j][0] + solve(hs[i - 2], hs[i - 1]));
			}

			if (j > 1) {
				lis[i][j][1] =
				    min(lis[i][j][1],
				        lis[i][j - 1][1] + solve(gs[j - 2], gs[j - 1]));
			}

			if (i > 0 && j > 0) {
				lis[i][j][0] =
				    min(lis[i][j][0],
				        lis[i - 1][j][1] + solve(hs[i - 1], gs[j - 1]));
				lis[i][j][1] =
				    min(lis[i][j][1],
				        lis[i][j - 1][0] + solve(hs[i - 1], gs[j - 1]));
			}
		}
	}

	cout << lis[h][g][0] << endl;
}