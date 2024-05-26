import math

N, K = map(int, input().split())

def Burnside(k):
    if N % 2 == 0:
        nothing = math.comb(N, k)
        mirror = 0
        if k % 2 == 0:
            mirror = math.comb(N//2, k // 2)
        
        return (nothing + mirror) // 2
    else:
        nothing = math.comb(N, k)
        mirror = 0

        if k % 2 == 0:
            mirror = math.comb(N//2, k // 2)
        else:
            mirror = math.comb(N//2, (k-1) // 2)

        return (nothing + mirror) // 2
    
ans = 0
for i in range(K//2 + 1):
    # print(i, Burnside(i), end =" ")
    # print(K-i, Burnside(K-i))
    # print(Burnside(k), Burnside(K-k))
    if Burnside(i) == 0 or Burnside(K-i) == 0:
        continue
    ans += Burnside(i) + Burnside(K - i)

print(ans)