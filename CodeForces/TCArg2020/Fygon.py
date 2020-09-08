import os
import sys
from fractions import Fraction as Frac

class Polynomio:
    def __init__(self, values):
        self.coeff = []
        self.coeff[:] = values

    def __add__(self, A):
        coeffi = []
        if len(A.coeff) > len(self.coeff):
            coeffi[:] = A.coeff
            for i in range(len(self.coeff)):
                coeffi[i] += Frac(self.coeff[i])
        else:
            coeffi[:] = self.coeff
            for i in range(len(A.coeff)):
                coeffi[i] += Frac(A.coeff[i])

        return Polynomio(coeffi)
        
    def __mul__(self, A):
        n = len(self.coeff) - 1
        t = len(A.coeff) - 1

        coeff = [Frac(0) for i in range(n+t+1)]
        for i in range(n+1):
            for j in range(t+1):
                coeff[j+i] += Frac(self.coeff[i]*A.coeff[j])
        return Polynomio(coeff)

    def __str__(self):
        res = ""
        for co in self.coeff:
            res += str(co) + " "
        return res
   

def interpolation(xs, ys):
    n = len(xs)
    PolyAns = Polynomio([])
    for i in range(n):
        xi = xs[i]
        denomi = Frac(1)
        A = Polynomio([Frac(1)])

        for j in range(n):
            xj = Frac(xs[j])
            if i != j:
                denomi = Frac(denomi) * Frac(xi - xj)
                A = A * Polynomio([-xj,1])

        aux = Frac(ys[i]) / Frac(denomi)
        PolyAns = PolyAns + A*Polynomio([ aux ])
        
    return PolyAns

    
#A = Polynomio([1, 2, 3])
#B = Polynomio([2, 3, 4])

#code = code=open('fygon.in','r').read().replace('lag','ans+=1')

with open(os.path.join(sys.path[0], "Fygon.in"), "r") as f:
    code = f.read().replace("lag", "ans+=1")

xs = []
ys = []

for aux in range(1, 8):
    ans = 0
    n = aux
    exec(code)
    #print(ans)
    xs.append(aux)
    ys.append(ans)
    #listValues.append((i, ans))

PolyAns = interpolation(xs, ys)
#print(PolyAns)

n = len(PolyAns.coeff)

Ans = [0 for i in range(n)]

for i in range(n):
    if(PolyAns.coeff[i] < 0):
        Ans[i] = "-"+str(abs(PolyAns.coeff[i]))
    elif(PolyAns.coeff[i] > 0):
        Ans[i] = "+"+str(abs(PolyAns.coeff[i]))
    else:
        Ans[i] = "0"

#print(Ans)

stringAns = ""
last = True

for degree in range(n):
    if Ans[degree] == "0":
        continue
    if last != True:
        stringAns += Ans[degree][0] + " " + Ans[degree][1:] + " "
    else:
        if Ans[degree][0] == "+":
            stringAns += Ans[degree][1:] + " "
        else:
            stringAns += Ans[degree] + " "
        last = False

    for j in range(degree):
        stringAns += "* n "


print(stringAns)
for i in range(len(xs)):
    print(f"{xs[i]} {ys[i]}")
#open('fygon.out','w').write(stringAns)