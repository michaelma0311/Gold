#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;               // for policy-based data structures
using namespace std;

typedef tree<int, null_type, less<int>, rb_tree_tag,
             tree_order_statistics_node_update>
    indexed_set; 

int main()  {
    freopen("sleepy.in","r",stdin);
	freopen("sleepy.out","w",stdout);
    int n;
    cin >> n;
    indexed_set lis;
    vector<int> nums(n);
    int le = 1;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        nums[i] = x;
        if (i != 0) {
            if (nums[i-1] > nums[i])    {
                //cout << "ADAD" << endl;
                lis.clear();
            } 
        }
        lis.insert(x);
    }
    le = lis.size();
    cout << n-le << endl;
    for (int i = 0; i < n-le; i++)  {
        if (i != 0) {
            cout << ' ';
        }
        int cur = nums[i];
        int x = lis.order_of_key(cur);
        cout << n-le-i+x-1;
        lis.insert(cur);
    }
    cout << endl;
    
}