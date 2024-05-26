import math

n = int(input())


ans = int(1e18)

for i in range(n):
    year, x, y = map(int, input().split())

    lcm = math.lcm(x, y)
    ans = min(ans, year + lcm)

print(ans)

