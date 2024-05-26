import random

N = random.randint(1, 30)
M = 45

print(N, M)

for i in range(N):
    print(random.randint(0, 2**M - 1), end=" ")


