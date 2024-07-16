#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> 
using namespace __gnu_pbds;               
using namespace std;

typedef tree<int, null_type, less<int>, rb_tree_tag,
             tree_order_statistics_node_update>
    indexed_set; 
int N, h, ans;
vector<int> height;
indexed_set cow;  
indexed_set woc;
int main() {
	FILE *in, *out;
	in = fopen("bphoto.in", "r");
	out = fopen("bphoto.out", "w");
	fscanf(in, "%d", &N);
	for (int i = 0; i < N; i++) {
		fscanf(in, "%d", &h);
		cow.insert(h);
		height.push_back(h);
	}
	for (int i : height) {
		cow.erase(i); 
		int le =
		    woc.size() -
		    woc.order_of_key(i); 
		                         
		int ri =
		    cow.size() - cow.order_of_key(i); 
		                                       
		woc.insert(i);                         
		if (max(le, ri) > 2 * min(le, ri)) ans++;
	}
	fprintf(out, "%d\n", ans);
}