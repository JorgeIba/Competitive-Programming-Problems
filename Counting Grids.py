

n = int(input())

MOD = int(1e9+7)

half = n//2

r0 = n*n
r1 = n*half - half**2 + n%2 
r2 = 2*n*half - 2*(half - 1)*half - 2*half + n%2
r3 = r1

cycles = [r0, r1, r2, r3]

ans = 0

for cycle in cycles:
    ans += pow(2, cycle, MOD)

ans %= MOD
print(cycles)
print(ans * pow(4, MOD-2, MOD) % MOD)

