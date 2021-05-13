def binPow(a, b):
    ans = 1
    while b:
        if b & 1:
            ans *= a;
        b>>=1
        a = a*a
    return ans

ans_max = 1

for a in range(2, 100):
    for b in range(2, 100):
        ans_max = max(ans_max, sum( [ int(digit) for digit in str(binPow(a,b)) ]  ))

print(ans_max)