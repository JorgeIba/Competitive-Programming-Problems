import math


def calc():        
    a, b, n = map(int, input().split(" "))

    gcd = math.gcd(a,b)

    a /= gcd
    b /= gcd

    if a > b:
        a -= (int(a/b))*b

    MOD = 999999937


    res = 1
    lista = []
    for i in range(n):
        a = a*10
        aux = int( a / b  )
        lista.append( aux  )
        a -= aux*b

    for dec in lista:
        if dec == 0:
            dec = 7
        res = (res*dec)%MOD

    print(res)


t = int(input())

for i in range(t):
    calc()
