#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int MOD = 1000000007;

class BIT {
public:
    vector<int> tree;
    vector<int> indices;

    BIT(const vector<int>& set) {
        indices.resize(set.size() + 2);
        tree.resize(indices.size());
        indices[0] = -1;

        int index = 1;
        for (int val : set) {
            indices[index++] = val;
        }
        indices[indices.size() - 1] = INT_MAX;
    }

    void update(int index, int val) {
        int actual = lower_bound(indices.begin(), indices.end(), index) - indices.begin();
        while (actual < indices.size()) {
            tree[actual] += val;
            if (tree[actual] >= MOD) tree[actual] -= MOD;
            actual += actual & -actual;
        }
    }

    int query(int index) {
        int left = 0;
        int right = indices.size() - 1;
        while (left != right) {
            int mid = (left + right + 1) / 2;
            if (indices[mid] > index) {
                right = mid - 1;
            } else {
                left = mid;
            }
        }

        int ret = 0;
        while (left > 0) {
            ret += tree[left];
            if (ret >= MOD) ret -= MOD;
            left -= left & -left;
        }
        return ret;
    }
};

int main() {

    int r, c, colors;
    cin >> r >> c >> colors;

    vector<vector<int>> grid(r, vector<int>(c));
    vector<vector<int>> columns(colors + 1);

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cin >> grid[i][j];
        }
    }

    for (int j = 0; j < c; j++) {
        for (int i = 0; i < r; i++) {
            int color = grid[i][j];
            if (!columns[color].empty() && columns[color].back() == j) continue;
            columns[color].push_back(j);
        }
    }

    vector<BIT*> bits(colors + 1, nullptr);
    for (int i = 1; i <= colors; i++) {
        if (!columns[i].empty()) {
            bits[i] = new BIT(columns[i]);
        }
    }

    vector<int> gen(c);
    fill    (gen.begin(), gen.end(), 0);
    BIT full(gen);
    full.update(0, 1);

    if (bits[grid[0][0]]) {
        bits[grid[0][0]]->update(0, 1);
    }

    for (int i = 1; i < r - 1; i++) {
        for (int j = c - 2; j > 0; j--) {
            int val = full.query(j - 1);
            if (bits[grid[i][j]]) {
                val -= bits[grid[i][j]]->query(j - 1);
                if (val < 0) val += MOD;
            }

            full.update(j, val);
            if (bits[grid[i][j]]) {
                bits[grid[i][j]]->update(j, val);
            }
        }
    }

    int ret = full.query(c - 2);
    if (bits[grid[r - 1][c - 1]]) {
        ret -= bits[grid[r - 1][c - 1]]->query(c - 2);
        if (ret < 0) ret += MOD;
    }

    cout << ret << endl;

    // Cleanup allocated BIT objects
    for (int i = 1; i <= colors; i++) {
        if (bits[i]) {
            delete bits[i];
        }
    }

    return 0;
}
