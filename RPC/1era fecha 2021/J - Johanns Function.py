t = int(input())

for i in range(t):
    n = int(input())

    part1 = n
    part2 = n+1
    if part1 % 2 == 0:
        part1 //= 2
    else:
        part2 //= 2

    part1 = part1*part2

    part21 = n
    part22 = n+1
    part23 = 2*n+1

    if(part21 % 2 == 0):
        part21 //= 2
    else:
        part22 //= 2


    if(part21 % 3 == 0):
        part21 //= 3
    elif(part22 % 3 == 0):
        part22 //= 3
    else:
        part23 //= 3

    part3 = part21 * part22 * part23

    ans = (part1 + part3) // 2

    print(ans)