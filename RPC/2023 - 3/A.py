import math

dp = {}
LIM = 2001

fac = [1 for _ in range(LIM)]

for i in range(2, LIM):
    fac[i] = i * fac[i - 1]

for i in range(0, LIM):
    for j in range(0, i + 1):
        # aux = math.comb(i, j)
        aux = fac[i] / (fac[j] * fac[i - j])
        if aux > 1_000_000_000:
            break
        if aux not in dp:
            dp[aux] = i + 1
        # print(aux, end=" ")
    # print("")

q = int(input())

for _ in range(q):
    n = int(input())
    if n in dp:
        print(dp[n])
    else:
        c = int(math.sqrt(2 * n))
        if c * (c + 1) == 2 * n:
            print(c + 2)
        else:
            print(n + 1)
