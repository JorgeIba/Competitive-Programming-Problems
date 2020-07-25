import sys,threading


MOD = 1000000007

def binPow(a, b):
    res = 1
    while(b > 0):
        if b&1:
            res = (res*a)%MOD
        b >>= 1
        a = (a*a)%MOD
    return res


def convert(n):
    lista = []
    while(n > 0):
        lista.append( n%7 )
        n //= 7
    lista.reverse()
    return lista


inverse2 = binPow(2, MOD-2)

powers = [0 for i in range(41)]
def getPowers():
    powers[0] = 1
    for i in range(1, 40):
        powers[i] =  binPow(28, i) 


def Gauss(n):
    return (n*(n+1)*inverse2)%MOD

lista1 = []
def funcion():
    global powers
    aux = 1
    suma = 0
    for i in range(len(lista1)-1):
        digit = lista1[i]
        long = len(lista1) - (i+1)
        powA = binPow(28, long)
        suma = (suma + (aux*(Gauss(digit)*powA)))%MOD
        aux *= digit+1
    return (suma + aux*Gauss(lista1[-1] + 1))%MOD
    

def solve(t):
    global lista1
    n = int(input())
    if(n==0):
        print("Case {}: {}".format(t, 0))  
        return
    
    lista1 = convert(n)
    total = Gauss(n+1)%MOD
    no = funcion()%MOD
    res = (total-no)%MOD
    if res<0:
        res += MOD
    print("{} - {}".format(total, no)) 
    #print("Case {}: {}".format(t, res))


getPowers()

t = int(input())

for i in range(1,t+1):
    solve(i)
    

