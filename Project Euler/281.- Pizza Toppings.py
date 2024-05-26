def phiSieve(n):
    Phi = [i for i in range(n+1)]

    for i in range(2, n+1):
        if Phi[i] == i:
            for j in range(i, n+1, i):
                Phi[j] -= Phi[j] // i
    
    return Phi


def getDivs(n):
    divs = []
    for i in range(1, n+1):
        if i*i > n:
            break

        if n % i == 0:
            divs.append(i)

            if i*i != n:
                divs.append(n//i)

    return divs

def f(m, n, phi):
    divs = getDivs(n)

    ans = 0
    for d in divs:
        den = fact[d] ** m
        fixed_points = phi[n//d] * fact[m*d] // den
        ans += fixed_points
    return ans // (n*m)

N = 50
M = 20
phi = phiSieve(N)

fact = [1 for _ in range(N*M)]

for i in range(2, N*M):
    fact[i] = fact[i-1] * i


ans_total = 0
for m in range(2, M):
    for n in range(1, N):
        ans_mn = f(m, n, phi)
        if ans_mn <= int(1e15):
            ans_total += ans_mn

print(ans_total)

