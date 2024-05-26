from random import randint, sample

T = 1

print(T)

LIMIT_A = int(1e9)
N = int(1e5)
Q = int(1e5)
K = int(1e6)

# LIMIT_A = 15
# N = 30
# Q = 20
# K = 50

colors = [ randint(1, N) for i in range(N)]
vals   = [ randint(1, LIMIT_A) for i in range(N)]

sizes  = []
while K > 0:
    k = randint(1, N)
    k = min(k, K)
    K -= k
    sizes.append(k) 

Q = len(sizes)


print(N, Q)
print(" ".join(str(color) for color in colors))
print(" ".join(str(val) for val in vals))

for size in sizes:
    x = randint(1, N)

    list_k = sample(range(1, N+1), size)
    if colors[x-1] not in list_k:
        list_k.pop()
        list_k.append(colors[x-1])

    print(3, x, size, " ".join(str(num) for num in list_k))


        