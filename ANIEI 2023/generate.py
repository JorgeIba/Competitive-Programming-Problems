N = int(1e5)
# N = 10
K = int(1e9)


import random


print(N, K)
MAX = int(1e9)
for _ in range(N):
    l= random.randint(1, MAX)
    r = random.randint(1, MAX)

    if l > r:
        t = l
        l = r
        r = t

    x = random.randint(500, 1000)
    print(l, r, x)