import math

MAGIC = 22
ans = 0
for k in range(1, MAGIC):
    lower = 10 ** ((k-1)/k)
    upper = 10

    lower = math.ceil(lower)
    ans += (upper - lower)

print(ans)


