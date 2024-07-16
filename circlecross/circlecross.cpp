#include <bits/stdc++.h>

using namespace std;

template <class T> struct Seg {
	int n;
	const T ID = 0;
	vector<T> seg;

	T comb(T a, T b) { return a + b; }

	void init(int _n) {
		n = _n;
		seg.assign(2 * n, ID);
	}

	void pull(int p) { seg[p] = comb(seg[2 * p], seg[2 * p + 1]); }

	// update the value at position p
	void upd(int p, T val) {
		seg[p += n] = val;

		for (p /= 2; p; p /= 2) { pull(p); }
	}

	// get the sum on the interval [l, r]
	T query(int l, int r) {
		T ra = ID, rb = ID;
		for (l += n, r += n + 1; l < r; l /= 2, r /= 2) {
			if (l & 1) ra = comb(ra, seg[l++]);
			if (r & 1) rb = comb(seg[--r], rb);
		}
		return comb(ra, rb);
	}
};

int main()  {
    freopen("circlecross.in","r",stdin);
	freopen("circlecross.out","w",stdout);
    int n;
    cin >> n;
    Seg<int> lis;
    lis.init(2*n);
    vector<int> starts(n);
    int ans = 0;
    for (int i = 0; i < 2*n; i++) {
        int x;
        cin >> x;
        x -= 1;
        if (starts[x] == 0)  {
            lis.upd(i, 1);
            starts[x] = i;
        } else  {
            //cout << i << ' ' << ans << endl;
            lis.upd(starts[x], 0);
            ans += lis.query(starts[x], i);
            //lis.upd(i, 0);
            //cout << "end " <<  ans << endl;
            starts[x] = 0;
        }
    }
    cout << ans << endl;
}