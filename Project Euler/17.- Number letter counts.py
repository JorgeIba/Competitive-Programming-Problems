
units = ["one", "two", "three", "four", "five", "six", "seven", "eight", "nine"]
teen = ["ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"]
dec = ["twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"]


def translate(cents, decs, unit):
    global units, teens, dec
    ans = units[cents-1] + "hundred" if cents != 0 else ""
    if ans != "" and (decs > 0 or unit > 0):
        ans += "and"
    if decs == 1:
        ans += teen[unit]
        return ans
    elif decs > 1:
        ans += dec[decs-2]
    ans += units[unit-1] if unit != 0 else ""
    return ans
    
def decompose(num):
    return ((num//100) % 10 , (num//10) % 10, num % 10)

N = 999
ans = 0
for i in range(1, N+1):
    cents_n, decs_n, units_n = decompose(i)
    # print(f"{cents}{decs}{unit}", end=" ")
    print(translate( cents_n, decs_n, units_n ))
    ans += len( translate(cents_n, decs_n, units_n) )

print(ans + len("onethousand"))