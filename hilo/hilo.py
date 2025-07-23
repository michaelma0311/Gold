import sys
import threading

def compute_sum(N, x, MOD=10**9+7):
    # Precompute inverses up to N+1
    inv = [0] * (N+2)
    inv[1] = 1
    for i in range(2, N+2):
        inv[i] = MOD - (MOD // i) * inv[MOD % i] % MOD
    a0 = N - x
    b0 = x
    # S_f1[b] = sum over a'<current a of f1[a'][b]
    S_f1 = [0] * (b0+1)
    # f0 at state
    f0_val = 0
    # factorial
    fact = 1
    for i in range(1, N+1):
        fact = fact * i % MOD
    # DP
    for a in range(0, a0+1):
        # prefix sum of f0 for row a: S_f0_row[b] = sum_{k=0..b-1} f0[a][k]
        S_f0_row = [0] * (b0+2)
        for b in range(0, b0+1):
            if a == 0 and b == 0:
                f0 = 0
                f1 = 0
            else:
                T = a + b + 1
                if b > 0:
                    FLO = S_f0_row[b] * inv[b] % MOD
                else:
                    FLO = 0
                if a > 0:
                    FH1 = S_f1[b] * inv[a] % MOD
                else:
                    FH1 = 0
                f0 = (b * FLO + a * FH1) * inv[T] % MOD
                f1 = (f0 + b * inv[T] % MOD) % MOD
            # update prefix sums
            S_f0_row[b+1] = (S_f0_row[b] + f0) % MOD
            S_f1[b] = (S_f1[b] + f1) % MOD
            if a == a0 and b == b0:
                f0_val = f0
    total = fact * f0_val % MOD
    return total

# Test sample
print(compute_sum(4, 2))  # expect 17
print(compute_sum(60, 10))  # expect 508859913