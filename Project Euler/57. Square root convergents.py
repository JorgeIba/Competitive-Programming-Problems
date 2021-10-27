import fractions as fraction

limit = int(1e3)

ans = 0
F = fraction.Fraction(1, 2)

for i in range(2, limit+1):
    F = fraction.Fraction(1, 2 + F)
    #print(F + 1)
    if len(str((F+1).numerator)) > len(str((F+1).denominator)):
        ans += 1


print(ans)

"""
    import sys

    sys.setrecursionlimit(1500)


    def square_iteration(n):
        if n == 1:
            return fraction.Fraction(2)

        return 2 + fraction.Fraction(1, square_iteration(n-1))
        

    def f(n):
        return 1 + fraction.Fraction(1, square_iteration(n))

    ans = 0

    for i in range(1, limit+1):
        fract = f(i)
        if len(str(fract.numerator)) > len(str(fract.denominator)):
            ans += 1

    print(ans)
"""
