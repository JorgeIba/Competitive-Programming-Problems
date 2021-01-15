import math

LIMIT = 1e6

ans = 0

for n in range(1, 101):
    for r in range(0, n):
        if math.comb(n,r) > LIMIT:
            ans += 1

print(ans)