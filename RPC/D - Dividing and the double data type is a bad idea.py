
def isNonPeriodic(n):
    pow_2, pow_5 = 0, 0

    while n % 5 == 0:
        n /= 5
        pow_5 += 1

    while n % 2 == 0:
        n /= 2
        pow_2 += 1

    if n == 1:
        if pow_2 < pow_5:
            return 5, pow_5
        else:
            return 2, pow_2
    else:
        return -1, -1



try:
    while(True):
        a, n = map(int, input().split())
        
        num, fr = isNonPeriodic(a)

        if num == -1:
            if n == 0:
                print(0, 1)
            else :
                print("Precision Error")
            continue
        else:

            m = fr*n

            num_base = 10**fr // a
            

            print(m, num_base**n)

except Exception:
    pass
