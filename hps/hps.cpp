#include <bits/stdc++.h> 
using namespace std;


const int MX = 1e5 + 5;

int dp[MX][25][3];  
                    
int A[MX];          

int main() {
	freopen("hps.in", 'r', stdin);
    freopen("hps.out", 'w', stdout);

	int N, K;

	cin >> N >> K;

	for (int i = 0; i < N; i++) {
		char a;
		cin >> a;
		if (a == 'H') A[i] = 0;
		if (a == 'P') A[i] = 1;
		if (a == 'S') A[i] = 2;
	}


	for (int i = 0; i < N; i++) {
		for (int j = 0; j <= K; j++) {
			for (int k = 0; k < 3; k++) {
				if (k == A[i]) dp[i][j][k]++;
				dp[i + 1][j + 1][0] = max(dp[i + 1][j + 1][0],
				                          dp[i][j][k]);  
				dp[i + 1][j + 1][1] = max(dp[i + 1][j + 1][1],
				                          dp[i][j][k]);  
				dp[i + 1][j + 1][2] = max(dp[i + 1][j + 1][2],
				                          dp[i][j][k]);  
				dp[i + 1][j][k] = max(dp[i + 1][j][k], dp[i][j][k]);  
			}
		}
	}

	int ans = 0;

	for (int i = 0; i < 3; i++) {
         ans = max(ans, dp[N - 1][K][i]); 
    }

	cout << ans << endl;
}