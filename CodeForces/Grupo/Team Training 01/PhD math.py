t = int(input())


def calculate(s, p):

    dic = {}
    n = len(s)
    dic[0] = 1
    aux = 1
    before = 0
    ans = 0
    for i in range(n-1, -1, -1):
        digit = s[i]
        digit = digit%p
        num = (digit*aux + before)%p
        ans += dic[num]
        mp[num] += 1
        aux = (aux*10)%p
    print(ans)



while(t):
    a, b, n, p = map(int, input().split(' '))
    lista = []
    while(n):
        a *= 10
        fl = int(a/b)
        lista.append(fl)
        a -= fl*b
        n-=1

    calculate(lista,p)


    t-=1