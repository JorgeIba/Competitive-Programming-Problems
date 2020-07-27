import math
import random

print (1000)

def test():
    a, b, c = 0, 0, 0
    while True:
        auxA = random.randint(1, 101) 
        auxB = random.randint(1, 101) 
        auxC = random.randint(1, 101) 
        if auxA % auxB != 0:
            a, b, c = auxA, auxB, auxC
            break

    print("{} {} {}".format(a, b, b))

for i in range(1000):
    test()