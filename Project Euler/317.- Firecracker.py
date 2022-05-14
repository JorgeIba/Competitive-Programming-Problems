
import math


v = 20
g = 9.81

x_max = v**2/g
y_max = v**2/(2*g)

## 0 = a*x_max^2 +- b * x_max + c
## y_max = a(0)^2 + b(0) + c = c

## c = y_max
## b = 0
## a = -g / (2 v^2)
## y = a*x^2 + c
## x^2 = (v^2/2*g - y) * (2v^2 / g)
## x^2 = (c1 - y) * (c2)
## x^2 = c1*c2 - c2*y
## integral from -100 to y_max: pi * x^2 * dy

c1, c2 = v**2/(2*g), 2*v**2/g
f_integral = lambda y: c1*c2*y - c2*y**2/2

ans = abs(math.pi*(f_integral(-100) - f_integral(y_max)))

print(round(ans, 4))







