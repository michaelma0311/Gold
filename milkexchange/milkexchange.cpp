#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); 
    int n;
    cin >> n;

    vector<int> A(n); 
    ll sum = 0;

    for (int &i : A){   
        cin >> i;
        sum += i;
    }
    rotate(A.begin(), next(min_element(A.begin(), A.end())), A.end());

    vector<int> stk;
    vector<ll> reduce(n + 5, 0);

    for (int i = n - 1; i >= 0; i--){
        while (stk.size() and A[stk.back()] >= A[i]){
            if (stk.size() > 1){
                // i < t1 < t2
                int t1 = stk.back();
                int t2 = stk[stk.size() - 2];

                // Milk lost from going from t1 to t2
                int delta = A[t1] - A[t2];
                
                // When does the pair begin applying delta
                int st = t2 - t1;

                // For how long does the pair apply delta
                int sz = t1 - i;

                reduce[st] += delta;
                reduce[st + sz] -= delta;
            }
            stk.pop_back();
        }
        stk.push_back(i);
    }

    // Finish proccessing rest of stack
    while (stk.size() > 1){
        int t1 = stk.back();
        int t2 = stk[stk.size() - 2];

        int delta = A[t1] - A[t2];
        int st = t2 - t1;
        int sz = t1 + 1;

        reduce[st] += delta;
        reduce[st + sz] -= delta;

        stk.pop_back();
    }

    // Get answer
    for (int i = 1; i <= n; i++){
        reduce[i] += reduce[i - 1];
        sum -= reduce[i];

        cout<<sum<<"\n";
    }
}