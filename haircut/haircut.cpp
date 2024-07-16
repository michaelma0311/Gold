#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/** @return the sum between a and b. */
int sum(vector<ll> &segtree, int a, int b) {
	int c = segtree.size() / 2;
	a += c;
	b += c;
	int s = 0;
	while (a <= b) {
		if (a % 2) s += segtree[a++];
		if (!(b % 2)) s += segtree[b--];
		a /= 2;
		b /= 2;
	}
	return s;
}

/** Increase the element at k by x in the segment tree. */
void add(vector<ll> &segtree, int k, ll x) {
	int c = segtree.size() / 2;
	k += c;
	segtree[k] += x;
	for (k /= 2; k >= 1; k /= 2) {
		segtree[k] = segtree[2 * k] + segtree[2 * k + 1];
	}
}

int main() {
	ifstream fin("haircut.in");

	int n;
	fin >> n;

	int c = 0;
	while ((1 << c) <= n + 1) { c++; }
	c = 1 << c;

	vector<ll> segtree(2 * c);
	vector<ll> ans(n + 2);
	for (int i = 1; i <= n; i++) {
		int a;
		fin >> a;
		ans[a + 1] += sum(segtree, a + 1, n + 1);
		add(segtree, a, 1);
	}

	ofstream fout("haircut.out");
	ll total = 0;
	for (int i = 0; i < n; i++) {
		total += ans[i];
		fout << total << "\n";
	}
}