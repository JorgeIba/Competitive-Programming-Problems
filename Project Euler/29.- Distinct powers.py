def binPow(a, b):
    res = 1
    while(b):
        if (b&1):
            res = res * a
        b>>=1
        a *= a
    return res


dicti = {}

for i in range(2,101):
    for j in range(2,101):
        dicti[ binPow(i,j)  ] = 1

print (len(dicti))
