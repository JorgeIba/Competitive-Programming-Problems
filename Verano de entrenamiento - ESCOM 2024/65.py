from fractions import Fraction


def continued_fraction(idx, k, limit):
    if (idx == limit):
        return 0
    
    if idx % 3 == 0:
        return Fraction(1, 1 + continued_fraction(idx+1, k, limit))
    elif idx % 3 == 1:
        return Fraction(1, 2*k + continued_fraction(idx+1, k, limit))
    else:
        return Fraction(1, 1 + continued_fraction(idx+1, k+1, limit))



# k = int(input())
k = 100 - 1
den_ans = 2 + continued_fraction(0, 1, k)

ans = sum(int(d) for d in str(den_ans.numerator))


print(ans)