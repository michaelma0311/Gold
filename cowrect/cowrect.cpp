#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <string>
using namespace std;

struct State {
    int x, y;
    bool red;

    State(int a, int b, bool c) : x(a), y(b), red(c) {}

    bool operator<(const State& other) const {
        return x < other.x;
    }
};

int main() {
    freopen("cowrect.in","r",stdin);
	freopen("cowrect.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<State> list;
    set<int> ys;

    for (int i = 0; i < n; ++i) {
        int x, y;
        string color;
        cin >> x >> y >> color;
        list.emplace_back(x, y, color == "H");
        ys.insert(y);
    }

    sort(list.begin(), list.end());

    vector<int> ysArray(ys.begin(), ys.end());

    int most = 0;
    int area = 0;

    for (size_t i = 0; i < ysArray.size(); ++i) {
        for (size_t j = i + 1; j < ysArray.size(); ++j) {
            bool valid = false;
            int lastX = -1;
            int now = 0;

            for (size_t a = 0; a < list.size(); ) {
                size_t b = a;
                int red = 0;
                int blue = 0;

                while (b < list.size() && list[a].x == list[b].x) {
                    if (list[b].y >= ysArray[i] && list[b].y <= ysArray[j]) {
                        if (list[b].red) {
                            ++red;
                        } else {
                            ++blue;
                        }
                    }
                    ++b;
                }

                if (blue > 0) {
                    valid = false;
                    now = 0;
                } else if (red + blue > 0) {
                    if (!valid) {
                        valid = true;
                        lastX = list[a].x;
                    }
                    now += red;
                    int currArea = (ysArray[j] - ysArray[i]) * (list[a].x - lastX);
                    if (now > most || (now == most && currArea < area)) {
                        most = now;
                        area = currArea;
                    }
                }

                a = b;
            }
        }
    }

    cout << most << "\n" << area << "\n";

    return 0;
}
