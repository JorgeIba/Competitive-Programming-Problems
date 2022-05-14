def gauss(x):
  return (x * (x + 1)) // 2

def sq(x):
  return (x * (x + 1) * (2*x + 1)) // 6

def tot(x):
  return 4 * x * x * (x * gauss(x - 1) - sq(x - 1))

def s1(x):
  return 2 * (x * gauss(x - 1) - sq(x - 1)) 

def s2(x):
  return  sq(x)

def s3(x):
  return (x**2)*(x-1) - sq(x-1)

def fx(n):
  return s2(n) + s3(n)

def s4(x):
  return x * gauss(x) + sq(x)

def s5(x):
  return (2 * (x**2)*(x-1)  - x * gauss(x - 1) - sq(x - 1))

def f2x(n):
  return s4(n) + s5(n)
  
  
def inside(n):
  return 2*s1(n)*n

def linea(n): ## (i, j) -- (k, l)
  ans = 0
  for i in range(0,n):
    for j in range(0,n):
      for k in range(2*n, 3*n):
        for l in range(0, n):
          ans += abs(i-k)  + abs(j-l) 
  return ans//2

def adyacentes(n): ## (i, j) -- (k, l)
  ans = 0
  for i in range(0,n):
    for j in range(0,n):
      for k in range(n, 2*n):
        for l in range(0, n):
          ans += abs(i-k)  + abs(j-l) 
  return ans//2
  
def centro(n): ## (i, j) -- (k, l)
  ans = 0
  for i in range(0,n):
    for j in range(0,n):
      for k in range(n, 2*n):
        for l in range(n, 2*n):
          ans += abs(i-k)  + abs(j-l) 
  return ans//2

def dentro(n):
  ans = 0
  for i in range(0,n):
    for j in range(0,n):
      for k in range(0, n):
        for l in range(0, n):
          ans += abs(i-k)  + abs(j-l) 
  return ans//2

def suma(n):
  return 5*dentro(n)+4*adyacentes(n)+4*centro(n)+2*linea(n)


def valid(i, j):
  if  n <= i < 2*n:
    return True
  if (n <= j < 2*n):
    return True
  return False


def total(n): ## (i, j) -- (k, l)
  ans = 0
  for i in range(0, 3*n):
    for j in range(0, 3*n):
      for k in range(0, 3*n):
        for l in range(0, 3*n):
          if valid(i, j) and valid(k, l):
            ans += abs(i-k)+abs(j-l)
  return ans // 2

  
# t = int(input())
mod = 1000000007
#for i in range(t):
while True:
  try:
    n = int(input())
    #### Extremo a Centro
    ans = fx(n) * n
    ans += s1(n) * n ##Chance se multiplica
    ans *= 4*n
    

    #### Extremos a Extremos misma linea

    aux1 = f2x(n) * n
    aux1 += s1(n) * n
    aux1 *= 2*n
    

    #### Extremos adyacentes
    aux2 = fx(n)*n
    aux2 += fx(n)*n
    aux2 *= 4*n

    

    aux3 = inside(n)
    aux3 *= 5*n

    ans += aux1 + aux2 + (aux3 // 2)
    
    #print(inside(n))
    #print(dentro(n))
    
    print(ans % mod)
  except EOFError:
    break