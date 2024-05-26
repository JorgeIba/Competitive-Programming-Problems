import math

def gcdExtended(a, b):
    if a == 0 :
        return b,0,1
             
    gcd,x1,y1 = gcdExtended(b%a, a)
    x = y1 - (b//a) * x1
    y = x1
    return gcd,x,y

def solve_crt_2(a_0, n_0, a_1, n_1):
    g, x, y = gcdExtended(n_0, n_1)
    if (a_1 - a_0) % g:
        return -1, -1
    
    k_0 = x * (a_1 - a_0) // g
    lcm = n_0 // g * n_1
    ans = k_0 * n_0 + a_0

    ans %= lcm
    if ans < 0:
        ans += lcm

    return ans, lcm

def crt(a, m, limit):
    x = a[0]
    mod = m[0]

    for i in range(1, len(a)):
        x, mod = solve_crt_2(x, mod, a[i], m[i])
        if x == -1:
            return -1, -1
        
        if mod > limit:
            return -1, -1
        
    return x, mod


n, m, k = map(int, input().split())
nums = list( map(int, input().split() ) )

def module(x, a):
    x %= a
    return x if x >= 0 else x + a

a = [ module(-i, nums[i]) for i in range(k) ]

j, i = crt(a, nums, n)

if i == 0:
    i += i

if j == 0:
    j += i

if i > n or j + k - 1 > m or i <= 0 or j <= 0:
    print("NO")
else:
    for l in range(k):
        g = math.gcd(i, j + l)
        if nums[l] != g:
            print("NO")
            exit(0)

    print("YES")