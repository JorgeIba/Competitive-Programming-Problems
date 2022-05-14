import math

def fEvaluate(x, k, r):
    integral_part1 = r**2 * math.asin( (x*k + 1)/r  )
    integral_part2 = r*(x*k+1)
    integral_part3 = math.sqrt(1 - (k*x+1)**2 / r**2)

    return ((integral_part1 + integral_part2*integral_part3) / (2*k) - x) / k


def getArea(k, r):
    if(r < 1):
        return 0
    x = (math.sqrt(r*r - 1) - 1) / k
    upper = fEvaluate(x, k, r)
    lower = fEvaluate(0, k, r)

    return upper - lower

def expectedValue(k):
    areaGreater = getArea(k, k + 0.5)
    areaLower = getArea(k, k - 0.5)

    totalArea = areaGreater - areaLower

    return k * totalArea


n = int(input())

ans = [ expectedValue(i) for i in range(1, n+1) ]

print(round(sum(ans), 5))

