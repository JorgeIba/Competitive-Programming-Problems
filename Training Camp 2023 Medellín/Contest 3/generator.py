import random

N = int(1e5)
M = random.randint(1, int(1e9))

lista = [random.randint(1, M-1) for _ in range(N)]

print(N, M)
print(" ".join(str(num) for num in lista))
