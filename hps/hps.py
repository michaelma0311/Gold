fin = open('hps.in')
n, k = map(int, fin.readline().split())
lis = [0 for i in range(n)]
for i in range(n):
    p = fin.readline().strip()
    if (p == 'P'):
        lis[i] = 0
    elif (p == 'H'):
        lis[i] = 1
    else:
        lis[i] = 2
dp = [[[0 for i in range(3)] for j in range(k+2)] for l in range(n+1)]

for i in range(n):
    for j in range(k+1):
        for l in range(3):
            if l == lis[i]:
                dp[i][j][l] += 1
            dp[i+1][j+1][0] = max(dp[i+1][j+1][0], dp[i][j][l])
            dp[i+1][j+1][1] = max(dp[i+1][j+1][1], dp[i][j][l])
            dp[i+1][j+1][2] = max(dp[i+1][j+1][2], dp[i][j][l])
            dp[i+1][j][l] = max(dp[i+1][j][l], dp[i][j][l])
ans = 0
#print(lis)
#for i in range(n):
    #print(dp[i])
for i in range(3):
    ans = max(ans, dp[n-1][k][i])
with open('hps.out', 'w') as f:
    f.write(str(ans) + '\n')
