import math

t = int(input())
for i in range(t):
    I, L, H = map(int, input().split())
    x = I*L / (H+L)
    x1, x2 = int(math.floor(x)), int(math.ceil(x))
    x2 = min(I, x2)
    if x1*H > (I - x2)*L:
        print(x1)
    else:
        print(x2)
