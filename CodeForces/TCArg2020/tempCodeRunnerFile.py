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
        n /= 7
    lista.reverse()
    return lista


inverse2 = binPow(2, MOD-2)

powers = {}
def getPowers():
    powers[0] = 1
    for i in range(1, 40):
        powers[i] =  binPow(28, i) 


def Gauss(n):
    return (n*(n+1)*inverse2)%MOD

lista1 = []
def funcion(index):
    if(index == len(lista1) ):
        return 0

    digit = lista1[index]

    if(index == (len(lista1) - 1)):
         return Gauss(digit+1)

    lenFaltante = len(lista1) - (index+1)
    return ((Gauss(digit)*powers[lenFaltante])%MOD + (digit+1)*((funcion(index+1)))%MOD)%MOD

def solve(t):
    global lista1
    n = int(input())
    lista1 = convert(n)
    total = Gauss(n+1)%MOD
    no = funcion(0)%MOD
    res = (total-no)%MOD
    if res<0:
        res += MOD
    if(n==0):
        print("Case {}: {}".format(t, 0))    
    else:
        print("Case {}: {}".format(t, res))


def main():
    getPowers()

    t = int(input())

    for i in range(1,t+1):
        solve(i)
    
if __name__ == "__main__":
    sys.setrecursionlimit(10000)








