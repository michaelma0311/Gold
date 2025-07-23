#include <bits/stdc++.h>
using namespace std;
int n;
vector<vector<int>> adj;
vector<vector<int>> parit;
vector<vector<int>> nums;

void dfs(int i, int curj)   {
    for (int k = 0; k < n; k++) {
        //cout << "FEOWUGBUOEBGUO " << i+1 << ' ' <<  k+1 << ' ' << parit[i][k] << ' ' << parit[curj][k] << endl;
        if (parit[i][k] == -1 && parit[curj][k] == -1) {
            parit[i][k] = -1;
        } else if (parit[i][k] == 1 && parit[curj][k] == -1)    {
            parit[i][k] = 1;
        } else if (parit[i][k] == -1 && parit[curj][k] == 1)    {
            parit[i][k] = 1;
        } else      {
            parit[i][k] = -1;
        }
        //cout << "EOUWBGOWUBG " << parit[i][k] << endl;
    }
}

int main()  {
    cin >> n;
    adj.resize(n);
    parit.resize(n);
    nums.resize(n);
    for (int i = 0; i < n; i++) {
        nums[i].resize(n);
        parit[i].resize(n);
        fill(parit[i].begin(), parit[i].end(), -1); //-1 is even, 1 is odd
    }
    
    for (int i = 0; i < n-1; i++) {
        string a;
        cin >> a;
        for (int j = 0; j < n-i-1; j++)    {
            nums[i][i+j+1] = (a[j]=='1'?1:-1);
            nums[i+j+1][i] = (a[j]=='1'?1:-1);
        }
    }
    int ans = 0;
    for (int i = n-2; i >= 0; i--)  {
        for (int j = 0; j < n-i-1; j++) {
            int curj = i+j+1;
            //cout << i+1 << ' ' << curj+1 << ' ' << parit[i][curj] << endl;
            if (parit[i][curj] != nums[i][curj])  {
                parit[i][curj] *= -1;
                //cout << "INSDIE " << i+1 << ' ' << curj +1<< endl;
                ans += 1;
                adj[i].push_back(curj);
                dfs(i, curj);
            }
        }
    }
    cout << ans << endl;

}