
def powers(n):
    cnt2, cnt5 = 0,0
    while n%2 == 0:
        cnt2+=1
        n>>=1
    while n%5 == 0:
        cnt5+=1
        n/=5
    
    if n != 1:
        return -1, -1

    return cnt2, cnt5



while True:
    try:
        a, n = map(int, input().split())

        if n == 0:
            print(0, 1)
            continue

        cnt2, cnt5 = powers(a)
        if cnt2 == -1:
            print("Precision Error")
            continue
    
        m = max(cnt2*n, cnt5*n)
        
        choose = 5 if cnt2 > cnt5 else 2

        print(m, pow(choose, n*abs(cnt5-cnt2)))

        



    except:
        exit(0)



